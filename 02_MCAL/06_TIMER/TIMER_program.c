/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  TIMER_program.c  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/10/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"


/* We want timer tick = 1 ms */
#define TIMER_PRESCALER_VALUE   8000UL
#define TIMER_ARR_VALUE         1UL



static Timer_Callback_t g_timer_callbacks[TIMER_MAX] = {0};
static volatile u32 g_timer_remaining_ms[TIMER_MAX] = {0};
static volatile u8 g_timer_busy[TIMER_MAX] = {0};

static TIM_Type * const g_timer_registers[TIMER_MAX] =
{
    TIM2,
    TIM3,
    TIM4
};

static const IRQn_Type g_timer_irqn[TIMER_MAX] =
{
    TIM2_IRQn,
    TIM3_IRQn,
    TIM4_IRQn
};

u8 g_timer_vec_index [TIMER_MAX] = {28,29,30};
static TIM_Type *Timer_GetPeripheral(Timer_ID_t timer_id)
{
    TIM_Type *timer = 0;

    switch(timer_id)
    {
        case TIMER_2:
            timer = TIM2;
            break;

        case TIMER_3:
            timer = TIM3;
            break;

        case TIMER_4:
            timer = TIM4;
            break;

        default:
            timer = 0;
            break;
    }

    return timer;
}

void Timer_Init(Timer_ID_t timer_id)
{
    TIM_Type *timer = Timer_GetPeripheral(timer_id);

    if(timer == 0)
    {
        return;
    }

    /*    Enable RCC clock    */
    if(timer_id == TIMER_2)
    {
        RCC_voidEnablePeripheralClock( APB1_BUS , TIM2_RCC ); /* TIM2EN */

    }
    else if(timer_id == TIMER_3)
    {
        RCC_voidEnablePeripheralClock( APB1_BUS , TIM3_RCC );  /* TIM3EN */
    }
    else if(timer_id == TIMER_4)
    {
        RCC_voidEnablePeripheralClock( APB1_BUS , TIM4_RCC );   /* TIM4EN */
    }

    /* Stop timer */
    CLR_BIT(timer->CR1,TIM_CR1_CEN);

    /*
     * Timer clock = 8 MHz
     * PSC = 8000 - 1
     * إذن timer counter tick = 1 ms
     */
    timer->PSC = TIMER_PRESCALER_VALUE - 1;

    /*
     * TICKS = ARR + 1
     * يعني update event كل 1 ms
     */
    timer->ARR = TIMER_ARR_VALUE - 1;

    /* Clear counter */
    timer->CNT = 0;

    /* Force update to load PSC and ARR */
    CLR_BIT(timer->EGR ,TIM_EGR_UG);

    /* Clear update flag */
    CLR_BIT(timer->SR ,TIM_SR_UIF);

    /* Disable update interrupt initially */
    CLR_BIT(timer->DIER ,TIM_DIER_UIE);

}

void Timer_Start(Timer_ID_t timer_id)
{
    TIM_Type *timer = Timer_GetPeripheral(timer_id);

    if(timer == 0)
    {
        return;
    }

    timer->CNT = 0;
    CLR_BIT(timer->SR ,TIM_SR_UIF);

    SET_BIT(timer->CR1,TIM_CR1_CEN);
}

void Timer_Stop(Timer_ID_t timer_id)
{
    TIM_Type *timer = Timer_GetPeripheral(timer_id);

    if(timer == 0)
    {
        return;
    }

    CLR_BIT(timer->CR1,TIM_CR1_CEN);
}


void Timer_DelayMs_Sync(Timer_ID_t timer_id, u32 delay_ms)
{
    TIM_Type *timer = Timer_GetPeripheral(timer_id);

    if(timer == 0)
    {
        return;
    }

    Timer_Start(timer_id);

    while(delay_ms > 0)
    {
        while((timer->SR & (1 << TIM_SR_UIF)) == 0)
        {
            /* Busy wait */
        }
        CLR_BIT(timer->SR,TIM_SR_UIF);

        delay_ms--;
    }

    Timer_Stop(timer_id);
}

Timer_Status_t Timer_DelayMs_Async(
    Timer_ID_t timer_id,
    u32 delay_ms,
    Timer_Callback_t callback
)
{
    TIM_Type *timer;

    if((timer_id >= TIMER_MAX) || (delay_ms == 0) || (callback == 0))
    {
        return TIMER_ERROR;
    }

    if(g_timer_busy[timer_id] == 1)
    {
        return TIMER_BUSY;
    }

    timer = g_timer_registers[timer_id];

    g_timer_remaining_ms[timer_id] = delay_ms;
    g_timer_callbacks[timer_id] = callback;
    g_timer_busy[timer_id] = 1;

    timer->CNT = 0;

    CLR_BIT(timer->SR, TIM_SR_UIF);

    SET_BIT(timer->DIER, TIM_DIER_UIE); // interrupt enable 

    NVIC_voidEnableInterrupt(g_timer_irqn[timer_id]);

    SET_BIT(timer->CR1, TIM_CR1_CEN);

    return TIMER_OK;
}

void Timer_ChannelToggle(Timer_ID_t timer_id,Timer_Channel_t channel,u32 prescaler,u32 arr,u32 compare_value){
    TIM_Type *timer;

    if(timer_id >= TIMER_MAX)
    {
        return;
    }

    if((prescaler == 0) || (arr == 0) || (compare_value >= arr))
    {
        return;
    }

    timer = g_timer_registers[timer_id];

    timer->PSC = prescaler - 1;
    timer->ARR = arr - 1;
    timer->CNT = 0;

    switch(channel)
    {
        case TIMER_CHANNEL_1:
            timer->CCR1 = compare_value;

            /* CH1 as output */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_CC1S_MASK);
            SET_MASK(timer->CCMR1, (TIM_CC_OUTPUT << TIM_CCMR1_CC1S));

            /* CH1 toggle mode */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_OC1M_MASK);
            SET_MASK(timer->CCMR1, (TIM_OC_MODE_TOGGLE << TIM_CCMR1_OC1M));

            /* Enable CH1 output */
            SET_BIT(timer->CCER, TIM_CCER_CC1E);
            break;

        case TIMER_CHANNEL_2:
            timer->CCR2 = compare_value;

            /* CH2 as output */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_CC2S_MASK);
            SET_MASK(timer->CCMR1, (TIM_CC_OUTPUT << TIM_CCMR1_CC2S));

            /* CH2 toggle mode */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_OC2M_MASK);
            SET_MASK(timer->CCMR1, (TIM_OC_MODE_TOGGLE << TIM_CCMR1_OC2M));

            /* Enable CH2 output */
            SET_BIT(timer->CCER, TIM_CCER_CC2E);
            break;

        case TIMER_CHANNEL_3:
            timer->CCR3 = compare_value;

            /* CH3 as output */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_CC3S_MASK);
            SET_MASK(timer->CCMR2, (TIM_CC_OUTPUT << TIM_CCMR2_CC3S));

            /* CH3 toggle mode */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_OC3M_MASK);
            SET_MASK(timer->CCMR2, (TIM_OC_MODE_TOGGLE << TIM_CCMR2_OC3M));

            /* Enable CH3 output */
            SET_BIT(timer->CCER, TIM_CCER_CC3E);
            break;

        case TIMER_CHANNEL_4:
            timer->CCR4 = compare_value;

            /* CH4 as output */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_CC4S_MASK);
            SET_MASK(timer->CCMR2, (TIM_CC_OUTPUT << TIM_CCMR2_CC4S));

            /* CH4 toggle mode */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_OC4M_MASK);
            SET_MASK(timer->CCMR2, (TIM_OC_MODE_TOGGLE << TIM_CCMR2_OC4M));

            /* Enable CH4 output */
            SET_BIT(timer->CCER, TIM_CCER_CC4E);
            break;

        default:
            return;
    }

    

    CLR_BIT(timer->SR, TIM_SR_UIF);

    SET_BIT(timer->EGR, TIM_EGR_UG);

    SET_BIT(timer->CR1, TIM_CR1_CEN);
}

void Timer_PWMSetDuty(Timer_ID_t timer_id,
                      Timer_Channel_t channel,
                      u8 duty_cycle)
{
    TIM_Type *timer;          /* Pointer to selected timer registers */
    u32 arr_value;            /* Real ARR period value */
    u32 compare_value;        /* New CCR value */

    /* Check timer ID and duty cycle range */
    if((timer_id >= TIMER_MAX) || (duty_cycle > 100))
    {
        return;
    }

    /* Get selected timer registers */
    timer = g_timer_registers[timer_id];

    /*
     * ARR register stores arr - 1
     * So real period value = ARR + 1
     */
    arr_value = timer->ARR + 1U;

    /*
     * Calculate CCR value from duty cycle
     * duty = 0   -> CCR = 0
     * duty = 100 -> CCR = ARR + 1
     */
    compare_value = (arr_value * duty_cycle) / 100U;

    switch(channel)
    {
        case TIMER_CHANNEL_1:
            timer->CCR1 = compare_value;   /* Update CH1 duty cycle */
            break;

        case TIMER_CHANNEL_2:
            timer->CCR2 = compare_value;   /* Update CH2 duty cycle */
            break;

        case TIMER_CHANNEL_3:
            timer->CCR3 = compare_value;   /* Update CH3 duty cycle */
            break;

        case TIMER_CHANNEL_4:
            timer->CCR4 = compare_value;   /* Update CH4 duty cycle */
            break;

        default:
            break;
    }
}

void Timer_PWMStart(Timer_ID_t timer_id,Timer_Channel_t channel,u32 prescaler,u32 arr,u8 duty_cycle)
{
    TIM_Type *timer;
    u32 compare_value;

     /* Check if timer ID is valid */
    if(timer_id >= TIMER_MAX)
    {
        return;
    }

    /* Validate input parameters */
    if((prescaler == 0) || (arr == 0) || (duty_cycle > 100))
    {
        return;
    }

    /* Get timer register address from timer array */
    timer = g_timer_registers[timer_id];

    /*
     * Calculate compare value
     * CCR determines HIGH time in PWM
     */
    compare_value = (arr * duty_cycle) / 100U;

    /* Stop timer before reconfiguration */
    CLR_BIT(timer->CR1, TIM_CR1_CEN);

    /*
     * Configure prescaler
     * Timer clock = InputClock / (PSC + 1)
     */
    timer->PSC = prescaler - 1U;

    /*
     * Configure auto reload register
     * ARR determines PWM period
     */
    timer->ARR = arr - 1U;

    /* Reset counter value */
    timer->CNT = 0U;

    switch(channel)
    {

        case TIMER_CHANNEL_1:

            /* Set duty cycle compare value for CH1 */
            timer->CCR1 = compare_value;

            /*
             * Clear CC1S bits
             * Configure CH1 as output compare
             */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_CC1S_MASK);

            /*
             * Select output mode for CH1
             */
            SET_MASK(timer->CCMR1,(TIM_CC_OUTPUT << TIM_CCMR1_CC1S));

            /*
             * Clear previous output compare mode bits
             */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_OC1M_MASK);

            /*
             * Select PWM mode 1
             */
            SET_MASK(timer->CCMR1,(TIM_OC_MODE_PWM_MODE_1 << TIM_CCMR1_OC1M));

            /*
             * Enable preload register for CCR1
             * New CCR value updates safely on update event
             */
            SET_BIT(timer->CCMR1, TIM_CCMR1_OC1PE);

            /* Enable channel 1 output */
            SET_BIT(timer->CCER, TIM_CCER_CC1E);

            break;

        case TIMER_CHANNEL_2:

            /* Set duty cycle compare value for CH2 */
            timer->CCR2 = compare_value;

            /* Configure CH2 as output */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_CC2S_MASK);

            SET_MASK(timer->CCMR1,(TIM_CC_OUTPUT << TIM_CCMR1_CC2S));

            /* Select PWM mode for CH2 */
            CLR_MASK(timer->CCMR1, TIM_CCMR1_OC2M_MASK);

            SET_MASK(timer->CCMR1,(TIM_OC_MODE_PWM_MODE_1 << TIM_CCMR1_OC2M));

            /* Enable preload for CCR2 */
            SET_BIT(timer->CCMR1, TIM_CCMR1_OC2PE);

            /* Enable CH2 output */
            SET_BIT(timer->CCER, TIM_CCER_CC2E);

            break;

        case TIMER_CHANNEL_3:

            /* Set compare value for CH3 */
            timer->CCR3 = compare_value;

            /* Configure CH3 as output */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_CC3S_MASK);

            SET_MASK(timer->CCMR2,(TIM_CC_OUTPUT << TIM_CCMR2_CC3S));

            /* Select PWM mode for CH3 */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_OC3M_MASK);

            SET_MASK(timer->CCMR2,(TIM_OC_MODE_PWM_MODE_1 << TIM_CCMR2_OC3M));

            /* Enable preload for CCR3 */
            SET_BIT(timer->CCMR2, TIM_CCMR2_OC3PE);

            /* Enable CH3 output */
            SET_BIT(timer->CCER, TIM_CCER_CC3E);

            break;

        case TIMER_CHANNEL_4:

            /* Set compare value for CH4 */
            timer->CCR4 = compare_value;

            /* Configure CH4 as output */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_CC4S_MASK);

            SET_MASK(timer->CCMR2,(TIM_CC_OUTPUT << TIM_CCMR2_CC4S));

            /* Select PWM mode for CH4 */
            CLR_MASK(timer->CCMR2, TIM_CCMR2_OC4M_MASK);

            SET_MASK(timer->CCMR2,(TIM_OC_MODE_PWM_MODE_1 << TIM_CCMR2_OC4M));

            /* Enable preload for CCR4 */
            SET_BIT(timer->CCMR2, TIM_CCMR2_OC4PE);

            /* Enable CH4 output */
            SET_BIT(timer->CCER, TIM_CCER_CC4E);

            break;

        default:
            return;
    }

    /*
     * Enable ARR preload
     * ARR updates safely on update event
     */
    SET_BIT(timer->CR1, TIM_CR1_ARPE);

    /*
     * Generate update event
     * Load PSC and ARR immediately
     */
    SET_BIT(timer->EGR, TIM_EGR_UG);

    /* Clear update interrupt flag */
    CLR_BIT(timer->SR, TIM_SR_UIF);

    /* Start timer counter */
    SET_BIT(timer->CR1, TIM_CR1_CEN);
}

static void Timer_IRQHandler(Timer_ID_t timer_id)
{
    TIM_Type *timer = g_timer_registers[timer_id];

    if((timer->SR & (1 << TIM_SR_UIF)) != 0)
    {
        timer->SR &= ~(1 << TIM_SR_UIF);
        if(g_timer_remaining_ms[timer_id] > 0)
        {
            g_timer_remaining_ms[timer_id]--;
        }

        if(g_timer_remaining_ms[timer_id] == 0)
        {
            CLR_BIT(timer->CR1, TIM_CR1_CEN);
            CLR_BIT(timer->DIER, TIM_DIER_UIE);

            g_timer_busy[timer_id] = 0;

            if(g_timer_callbacks[timer_id] != 0)
            {   
                g_timer_callbacks[timer_id]();
                g_timer_callbacks[timer_id] = 0;
            }   
        }
    }
}

void TIM2_IRQHandler(void)
{
    Timer_IRQHandler(TIMER_2);
}

void TIM3_IRQHandler(void)
{
    Timer_IRQHandler(TIMER_3);
}

void TIM4_IRQHandler(void)
{
    Timer_IRQHandler(TIMER_4);
}

/*
    Example idea:
    CH1 = Rising edge  -> captures period
    CH2 = Falling edge -> captures high time

    PWM input mode:
    TI1 is connected to both IC1 and IC2.
*/

void TIM_InputCapture_PWM_Init(void)
{
    /* 1. Stop timer */
    TIM2->CR1 &= ~TIM_CR1_CEN;

    /* 2. Set prescaler and ARR */
    TIM2->PSC = 71;          // Example: 72 MHz / 72 = 1 MHz timer tick
    TIM2->ARR = 0xFFFF;      // Max counter range

    /* 3. Clear CCMR1 channel configuration */
    TIM2->CCMR1 = 0;

    /*
        CC1 mapped to TI1
        CC2 mapped to TI1
    */
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_TI1;
    TIM2->CCMR1 |= TIM_CCMR1_CC2S_TI1;

    /* 4. Configure edges */
    TIM2->CCER = 0;

    TIM2->CCER |= TIM_CCER_CC1E;       // Enable capture on CH1 rising edge
    TIM2->CCER &= ~TIM_CCER_CC1P;      // CC1 rising edge

    TIM2->CCER |= TIM_CCER_CC2E;       // Enable capture on CH2
    TIM2->CCER |= TIM_CCER_CC2P;       // CC2 falling edge

    /*
        5. Slave reset mode:
        Every rising edge on TI1 resets CNT.
        So:
        CCR1 = Period
        CCR2 = High time
    */
    TIM2->SMCR = 0;
    TIM2->SMCR |= TIM_SMCR_TS_TI1FP1;
    TIM2->SMCR |= TIM_SMCR_SMS_RESET_MODE;

    /* 6. Enable auto-reload preload */
    TIM2->CR1 |= TIM_CR1_ARPE;

    /* 7. Start timer */
    TIM2->CR1 |= TIM_CR1_CEN;
}

//timer_tick_hz = timer_input_clock_hz / (PSC + 1);

TIM_InputCaptureSignal_t TIM_InputCapture_MeasurePWM(u32 timer_tick_hz)
{
    TIM_InputCaptureSignal_t signal = {0};

    u32 period = 0;
    u32 high_time = 0;

    /* -------------------------------- */
    /* 1. Clear old flags               */
    /* -------------------------------- */

    TIM2->SR &= ~TIM_SR_CC1IF;
    TIM2->SR &= ~TIM_SR_CC2IF;

    /* -------------------------------- */
    /* 2. Wait for NEW rising edge      */
    /* -------------------------------- */

    while (!(TIM2->SR & TIM_SR_CC1IF));

    /* Clear flag */
    TIM2->SR &= ~TIM_SR_CC1IF;

    /*
        At this point:
        - Counter reset occurred
        - New PWM cycle started
    */

    /* -------------------------------- */
    /* 3. Wait for next rising edge     */
    /* -------------------------------- */

    while (!(TIM2->SR & TIM_SR_CC1IF));

    /*
        Now:
        CCR1 = Full period
        CCR2 = High time
        Both belong to SAME cycle
    */

    period = TIM2->CCR1;
    high_time = TIM2->CCR2;

    /* Clear flags */
    TIM2->SR &= ~TIM_SR_CC1IF;
    TIM2->SR &= ~TIM_SR_CC2IF;

    signal.period_ticks = period;
    signal.high_ticks = high_time;

    if(period != 0)
    {
        signal.frequency_hz = timer_tick_hz / period;

        signal.duty_cycle_percent =
            (high_time * 100U) / period;
    }

    return signal;
}


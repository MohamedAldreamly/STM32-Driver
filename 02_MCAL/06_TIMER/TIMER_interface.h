/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/10/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 

#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#include "TIMER_private.h"

/* Timer ID */
typedef enum
{
    // TO use it as index in array
    TIMER_2 = 0,
    TIMER_3,
    TIMER_4,

    TIMER_MAX

} Timer_ID_t;

typedef enum
{
    TIM2_IRQn = 28,
    TIM3_IRQn = 29,
    TIM4_IRQn = 30

} IRQn_Type;

/* Timer status */
typedef enum
{
    TIMER_OK,
    TIMER_BUSY,
    TIMER_ERROR
} Timer_Status_t; 

typedef enum
{
    TIMER_CHANNEL_1 = 0,
    TIMER_CHANNEL_2,
    TIMER_CHANNEL_3,
    TIMER_CHANNEL_4

} Timer_Channel_t;

/* ===================================================== */
/*                     Input Capture                    */
/* ===================================================== */


/* ================= TIMx_CR1 Bits ================= */

#define TIM_CR1_CEN              (1U << 0)   // Counter enable
#define TIM_CR1_ARPE             (1U << 7)   // Auto-reload preload enable


/* ================= TIMx_CCMR1 Input Bits ================= */

/* CC1S: Capture/Compare 1 selection */
#define TIM_CCMR1_CC1S_TI1       (1U << 0)   // CC1 channel is mapped to TI1 input
#define TIM_CCMR1_CC1S_TI2       (2U << 0)   // CC1 channel is mapped to TI2 input

/* IC1PSC: Input capture 1 prescaler */
#define TIM_CCMR1_IC1PSC_DIV1    (0U << 2)   // Capture each valid transition
#define TIM_CCMR1_IC1PSC_DIV2    (1U << 2)   // Capture once every 2 transitions
#define TIM_CCMR1_IC1PSC_DIV4    (2U << 2)   // Capture once every 4 transitions
#define TIM_CCMR1_IC1PSC_DIV8    (3U << 2)   // Capture once every 8 transitions

/* IC1F: Input capture 1 filter */
#define TIM_CCMR1_IC1F_NONE      (0U << 4)   // No input filter


/* CC2S: Capture/Compare 2 selection */
#define TIM_CCMR1_CC2S_TI2       (1U << 8)   // CC2 channel is mapped to TI2 input
#define TIM_CCMR1_CC2S_TI1       (2U << 8)   // CC2 channel is mapped to TI1 input

/* IC2PSC: Input capture 2 prescaler */
#define TIM_CCMR1_IC2PSC_DIV1    (0U << 10)  // Capture each valid transition

/* IC2F: Input capture 2 filter */
#define TIM_CCMR1_IC2F_NONE      (0U << 12)  // No input filter


/* ================= TIMx_CCER Bits ================= */

#define TIM_CCER_CC1E            (1U << 0)   // Capture/Compare 1 enable
#define TIM_CCER_CC1P            (1U << 1)   // CC1 capture on falling edge when set

#define TIM_CCER_CC2E            (1U << 4)   // Capture/Compare 2 enable
#define TIM_CCER_CC2P            (1U << 5)   // CC2 capture on falling edge when set


/* ================= TIMx_SMCR Bits ================= */

#define TIM_SMCR_SMS_RESET_MODE  (4U << 0)   // Reset mode: trigger resets the counter
#define TIM_SMCR_TS_TI1FP1       (5U << 4)   // Trigger source is filtered TI1 input


/* ================= TIMx_SR Bits ================= */

#define TIM_SR_CC1IF             (1U << 1)   // Capture/Compare 1 interrupt flag
#define TIM_SR_CC2IF             (1U << 2)   // Capture/Compare 2 interrupt flag


/* ================= API ================= */

typedef struct
{
    u32 frequency_hz;
    u32 duty_cycle_percent;
    u32 period_ticks;
    u32 high_ticks;
} TIM_InputCaptureSignal_t;

void TIM_InputCapture_PWM_Init(void);
TIM_InputCaptureSignal_t TIM_InputCapture_MeasurePWM(u32 timer_tick_hz);

/* ===================================================== */
/*              Output Compare Modes (OCxM)              */
/* ===================================================== */

#define TIM_OC_MODE_FROZEN             0x0U   /* No action on output compare match */
#define TIM_OC_MODE_ACTIVE_ON_MATCH    0x1U   /* Force output active when CNT == CCRx */
#define TIM_OC_MODE_INACTIVE_ON_MATCH  0x2U   /* Force output inactive when CNT == CCRx */
#define TIM_OC_MODE_TOGGLE             0x3U   /* Toggle output when CNT == CCRx */
#define TIM_OC_MODE_FORCE_INACTIVE     0x4U   /* Force output inactive regardless of compare */
#define TIM_OC_MODE_FORCE_ACTIVE       0x5U   /* Force output active regardless of compare */
#define TIM_OC_MODE_PWM_MODE_1         0x6U   /* PWM mode 1 */
#define TIM_OC_MODE_PWM_MODE_2         0x7U   /* PWM mode 2 */


/* ===================================================== */
/*          Capture Compare Selection (CCxS)             */
/* ===================================================== */

#define TIM_CC_OUTPUT                  0x0U   /* Channel configured as output */
#define TIM_CC_INPUT_TI1               0x1U   /* Channel input mapped to TI1/TIx */
#define TIM_CC_INPUT_TI2               0x2U   /* Channel input mapped to TI2/opposite TI */
#define TIM_CC_INPUT_TRC               0x3U   /* Channel input mapped to trigger controller */

/* ===================================================== */
/*                CCMR1 Bit Positions                    */
/*                  CH1 and CH2                          */
/* ===================================================== */

/* Channel 1 */
#define TIM_CCMR1_CC1S                 0U     /* CH1 selection: input or output */
#define TIM_CCMR1_OC1FE                2U     /* CH1 output compare fast enable */
#define TIM_CCMR1_OC1PE                3U     /* CH1 output compare preload enable */
#define TIM_CCMR1_OC1M                 4U     /* CH1 output compare mode start bit */

/* Channel 2 */
#define TIM_CCMR1_CC2S                 8U     /* CH2 selection: input or output */
#define TIM_CCMR1_OC2FE                10U    /* CH2 output compare fast enable */
#define TIM_CCMR1_OC2PE                11U    /* CH2 output compare preload enable */
#define TIM_CCMR1_OC2M                 12U    /* CH2 output compare mode start bit */

/* ===================================================== */
/*                CCMR2 Bit Positions                    */
/*                  CH3 and CH4                          */
/* ===================================================== */

/* Channel 3 */
#define TIM_CCMR2_CC3S                 0U     /* CH3 selection: input or output */
#define TIM_CCMR2_OC3FE                2U     /* CH3 output compare fast enable */
#define TIM_CCMR2_OC3PE                3U     /* CH3 output compare preload enable */
#define TIM_CCMR2_OC3M                 4U     /* CH3 output compare mode start bit */

/* Channel 4 */
#define TIM_CCMR2_CC4S                 8U     /* CH4 selection: input or output */
#define TIM_CCMR2_OC4FE                10U    /* CH4 output compare fast enable */
#define TIM_CCMR2_OC4PE                11U    /* CH4 output compare preload enable */
#define TIM_CCMR2_OC4M                 12U    /* CH4 output compare mode start bit */


/* ===================================================== */
/*                CCER Bit Positions                     */
/* ===================================================== */

#define TIM_CCER_CC1E                  0U     /* Enable CH1 output */
#define TIM_CCER_CC1P                  1U     /* CH1 output polarity */

#define TIM_CCER_CC2E                  4U     /* Enable CH2 output */
#define TIM_CCER_CC2P                  5U     /* CH2 output polarity */

#define TIM_CCER_CC3E                  8U     /* Enable CH3 output */
#define TIM_CCER_CC3P                  9U     /* CH3 output polarity */

#define TIM_CCER_CC4E                  12U    /* Enable CH4 output */
#define TIM_CCER_CC4P                  13U    /* CH4 output polarity */

/* Callback type for async delay */
typedef void (*Timer_Callback_t)(void);

/* ===================================================== */
/*                  Basic Timer APIs                     */
/* ===================================================== */

/* Initialize selected timer */
void Timer_Init(Timer_ID_t timer_id);

/* Start timer counter */
void Timer_Start(Timer_ID_t timer_id);

/* Stop timer counter */
void Timer_Stop(Timer_ID_t timer_id);


/* ===================================================== */
/*                    Delay APIs                         */
/* ===================================================== */

/* Blocking delay using timer */
void Timer_DelayMs_Sync(Timer_ID_t timer_id,
                        u32 delay_ms);

/* Non-blocking delay with callback */
Timer_Status_t Timer_DelayMs_Async(Timer_ID_t timer_id,
                                   u32 delay_ms,
                                   Timer_Callback_t callback);


/* ===================================================== */
/*                Output Compare APIs                    */
/* ===================================================== */

/* Generate toggle signal on timer channel */
void Timer_ChannelToggle(Timer_ID_t timer_id,
                         Timer_Channel_t channel,
                         u32 prescaler,
                         u32 arr,
                         u32 compare_value);


/* ===================================================== */
/*                     PWM APIs                          */
/* ===================================================== */

/* Start PWM generation on selected channel */
void Timer_PWMStart(Timer_ID_t timer_id,
                    Timer_Channel_t channel,
                    u32 prescaler,
                    u32 arr,
                    u8 duty_cycle);

/* Update PWM duty cycle */
void Timer_PWMSetDuty(Timer_ID_t timer_id,
                      Timer_Channel_t channel,
                      u8 duty_cycle);


#endif
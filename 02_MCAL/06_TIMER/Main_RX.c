#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* Your Drivers */
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "TIM_interface.h"

#define IC_TIMER          TIM2
#define IC_INPUT_CHANNEL  TIM_CHANNEL_1

#define TIMER2_CLK_HZ     72000000UL
#define TIMER2_PSC        71UL
#define TIMER2_TICK_HZ    (TIMER2_CLK_HZ / (TIMER2_PSC + 1UL))

int main(void)
{
    TIM_InputCaptureSignal_t pwm_signal;

    /* ================= Clock Init ================= */

    MRCC_voidInitSystemClock();

    MRCC_voidEnablePeripheralClock(RCC_APB2, RCC_IOPA);
    MRCC_voidEnablePeripheralClock(RCC_APB1, RCC_TIM2);

    /* ================= Input Capture Pin ================= */

    /*
        PA0 = TIM2_CH1
        Configure it as input floating or input pull-up حسب الدرايفر تبعك
    */
    MGPIO_voidSetPinDirection(GPIOA, PIN0, GPIO_INPUT_FLOATING);

    /* ================= Input Capture Init ================= */

    /*
        TIM2_CH1 captures rising edge.
        TIM2_CH2 captures falling edge.
        Reset mode resets CNT at every rising edge.

        Result:
        CCR1 = Period ticks
        CCR2 = High time ticks
    */

    MTIM_voidInputCapturePWMInit(IC_TIMER);

    MTIM_voidSetPrescaler(IC_TIMER, TIMER2_PSC);
    MTIM_voidSetAutoReload(IC_TIMER, 0xFFFF);

    MTIM_voidStart(IC_TIMER);

    while (1)
    {
        pwm_signal = MTIM_udtMeasurePWM(IC_TIMER, TIMER2_TICK_HZ);

        /*
            pwm_signal.frequency_hz
            pwm_signal.duty_cycle_percent
            pwm_signal.period_ticks
            pwm_signal.high_ticks
        */
    }
}
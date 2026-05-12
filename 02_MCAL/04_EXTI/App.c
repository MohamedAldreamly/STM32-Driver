#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"

#include "LED_interface.h"
#include "SW_interface.h"

SW_PinConfig SW_1 = {GPIOA, GPIO_PIN1, SW_ACTIVE_HIGH};
LED_Type LED_1 = {GPIOA, GPIO_PIN0, LED_ACTIVE_HIGH};


void LED_Toggle_Callback(void)
{
    LED_voidToggle(LED_1);
}



int main(void)
{
    RCC_voidInitSysClock();

    // RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
    // RCC_voidEnableAFIOClock();
    
    SW_voidInit(SW_1);
    LED_voidInit(LED_1);
    
    EXTI_voidInit(EXTI_LINE1, EXTI_PORTA, FALLING_EDGE, LED_Toggle_Callback);

    while (1)
    {
    }
}
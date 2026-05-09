/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SW_config.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : HAL
 *
 */  

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "STK_interface.h"   // util/delay


#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"


void SW_voidInit(SW_PinConfig Copy_Config)
{
    if (Copy_Config.Port == GPIOA)
    {
        RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
    }
    else if (Copy_Config.Port == GPIOB)
    {
        RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
    }
    else if (Copy_Config.Port == GPIOC)
    {
        RCC_voidEnablePeripheralClock(APB2_BUS, DIOC_RCC);
    }

    GPIO_voidSetPinDirection(Copy_Config.Port, Copy_Config.Pin, INPUT_PULLUP_PULLDOWN);
}

u8 SW_u8GetState(SW_PinConfig Copy_Config)
{
    u8 Local_u8State = SW_RELEASED;
    u8 Local_u8PinState ; 
    GPIO_u8GetPinValue(Copy_Config.Port, Copy_Config.Pin, &Local_u8PinState);
    
    
    if (Copy_Config.SW_Type == SW_ACTIVE_HIGH)
    {
        if (Local_u8PinState == GPIO_HIGH)
        {
            STK_voidDelayMs(20); // Debounce delay
            GPIO_u8GetPinValue(Copy_Config.Port, Copy_Config.Pin, &Local_u8PinState);

            if (Local_u8PinState == GPIO_HIGH)
            {
                Local_u8State = SW_PRESSED;// Return the actual state for active high
                while (Local_u8PinState == GPIO_HIGH); // Wait until the switch is released
            }
        }
        return Local_u8State;
    }
    
    else if (Copy_Config.SW_Type == SW_ACTIVE_LOW)
    {
        if (Local_u8PinState == GPIO_LOW)
        {
            STK_voidDelayMs(20); // Debounce delay
            GPIO_u8GetPinValue(Copy_Config.Port, Copy_Config.Pin, &Local_u8PinState);
    

            if (Local_u8PinState == GPIO_LOW)
            {
                Local_u8State = SW_PRESSED;// Return the actual state for active low
                while (Local_u8PinState == GPIO_LOW); // Wait until the switch is released
            }
        }
        return Local_u8State;
    }
    
    return 0; // Default return value (should not reach here)
}


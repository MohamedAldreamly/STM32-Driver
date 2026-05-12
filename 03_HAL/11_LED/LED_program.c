/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/8/2026
 *  Vertion : V01
 *  Layer   : HAL
 *
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

void LED_voidInit(LED_Type Copy_Config)
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

    GPIO_voidSetPinDirection(Copy_Config.Port, Copy_Config.Pin, OUTPUT_SPEED_2MHZ_PP);
    LED_voidTurnOff(Copy_Config);

}

void LED_voidTurnOn(LED_Type Copy_Config)
{
    if (Copy_Config.ActiveStatus == LED_ACTIVE_HIGH)
    {
        GPIO_voidSetPinValue(Copy_Config.Port, Copy_Config.Pin, GPIO_HIGH);
    }
    else if (Copy_Config.ActiveStatus == LED_ACTIVE_LOW)
    {
        GPIO_voidSetPinValue(Copy_Config.Port, Copy_Config.Pin, GPIO_LOW);
    }
}

void LED_voidTurnOff(LED_Type Copy_Config)
{
    if (Copy_Config.ActiveStatus == LED_ACTIVE_HIGH)
    {
        GPIO_voidSetPinValue(Copy_Config.Port, Copy_Config.Pin, GPIO_LOW);
    }
    else if (Copy_Config.ActiveStatus == LED_ACTIVE_LOW)
    {
        GPIO_voidSetPinValue(Copy_Config.Port, Copy_Config.Pin, GPIO_HIGH);
    }
}

void LED_voidToggle(LED_Type Copy_Config)
{
    GPIO_voidTogglePinValue(Copy_Config.Port, Copy_Config.Pin);
}
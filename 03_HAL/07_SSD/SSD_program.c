/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

// in main 

// SSD_PinConfig SSD1 = {
//     .Port = {GPIOA , GPIOA ,GPIOA ,GPIOA , GPIOA ,GPIOA , GPIOA , GPIOA},
//     .Pin = {0 , 1 , 2 , 3 , 4 , 5 , 6 , 7},
//     .SSD_Type = SSD_COMMON_CATHODE,
// };

void SSD_voidInit(SSD_PinConfig Copy_Config)
{
    for (u8 i = 0; i < 8; i++)
    {
        if (Copy_Config.Port[i] == GPIOA)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
        }
        if (Copy_Config.Port[i] == GPIOB)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
        }
        if (Copy_Config.Port[i] == GPIOC)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOC_RCC);
        }   
    }
  
    for (u8 i = 0; i < 8; i++)
    {
        GPIO_voidSetPinDirection(Copy_Config.Port[i], Copy_Config.Pin[i], OUTPUT_SPEED_2MHZ_PP);
    }
}

void SSD_voidDisplay(SSD_PinConfig Copy_Config, u8 Copy_u8Number)
{
    if (Copy_u8Number < 10)
    {
        for (u8 i = 0; i < 7; i++)
        {
            u8 bitValue = GET_BIT(SSD_u8Digits[Copy_u8Number], i);
            if (Copy_Config.SSD_Type == SSD_COMMON_CATHODE)
            {
                GPIO_voidSetPinValue(Copy_Config.Port[i], Copy_Config.Pin[i], bitValue);
            }
            else
            {
                GPIO_voidSetPinValue(Copy_Config.Port[i], Copy_Config.Pin[i], !bitValue);
            }
        }
    }
}

void SSD_voidClear(SSD_PinConfig Copy_Config)
{
    for (u8 i = 0; i < 7; i++)
    {
        if (Copy_Config.SSD_Type == SSD_COMMON_CATHODE)
        {
            GPIO_voidSetPinValue(Copy_Config.Port[i], Copy_Config.Pin[i], GPIO_LOW);
        }
        else
        {
            GPIO_voidSetPinValue(Copy_Config.Port[i], Copy_Config.Pin[i], GPIO_HIGH);
        }
    }
}

void SSD_voidEnable(SSD_PinConfig Copy_Config)
{
    if (Copy_Config.SSD_Type == SSD_COMMON_CATHODE)
    {
        GPIO_voidSetPinValue(Copy_Config.Port[SSD_SEG_EN], Copy_Config.Pin[SSD_SEG_EN], GPIO_HIGH);
    }
    else
    {
        GPIO_voidSetPinValue(Copy_Config.Port[SSD_SEG_EN], Copy_Config.Pin[SSD_SEG_EN], GPIO_LOW);
    }
}

void SSD_voidDisable(SSD_PinConfig Copy_Config)
{
    if (Copy_Config.SSD_Type == SSD_COMMON_CATHODE)
    {
        GPIO_voidSetPinValue(Copy_Config.Port[SSD_SEG_EN], Copy_Config.Pin[SSD_SEG_EN], GPIO_LOW);
    }
    else
    {
        GPIO_voidSetPinValue(Copy_Config.Port[SSD_SEG_EN], Copy_Config.Pin[SSD_SEG_EN], GPIO_HIGH);
    }
}

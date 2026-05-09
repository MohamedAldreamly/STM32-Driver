/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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
#include "STK_interface.h"   

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

char KeypadDataMap[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

void Keypad_Init(KPD_PinConfig Copy_Config)
{
    for (u8 i = 0; i < KEYPAD_NUM_ROWS; i++)
    {
        if (Copy_Config.RowPort[i] == GPIOA)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
        }
        else if (Copy_Config.RowPort[i] == GPIOB)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
        }
        else if (Copy_Config.RowPort[i] == GPIOC)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOC_RCC);
        }
        GPIO_voidSetPinDirection(Copy_Config.RowPort[i], Copy_Config.RowPin[i], OUTPUT_SPEED_2MHZ_PP);
        GPIO_voidSetPinValue(Copy_Config.RowPort[i], Copy_Config.RowPin[i], GPIO_HIGH);
    }

    for (u8 j = 0; j < KEYPAD_NUM_COLS; j++)
    {
        if (Copy_Config.ColPort[j] == GPIOA)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
        }
        else if (Copy_Config.ColPort[j] == GPIOB)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
        }
        else if (Copy_Config.ColPort[j] == GPIOC)
        {
            RCC_voidEnablePeripheralClock(APB2_BUS, DIOC_RCC);
        }
        GPIO_voidSetPinDirection(Copy_Config.ColPort[j], Copy_Config.ColPin[j], INPUT_PULLUP_PULLDOWN);
        //Set the column pins PULL-UP
        GPIO_voidSetPinValue(Copy_Config.ColPort[j], Copy_Config.ColPin[j], GPIO_HIGH);
    }
}

u8 Keypad_Scan(KPD_PinConfig Copy_Config)
{
    u8 row = 0 , col = 0, key = 0xFF; // Default value when no key is pressed

    for ( row = 0 ; row < KEYPAD_NUM_ROWS ; row++)
    {
        GPIO_voidSetPinValue(Copy_Config.RowPort[row], Copy_Config.RowPin[row], GPIO_LOW); // Activate the current row
        for ( col = 0 ; col < KEYPAD_NUM_COLS ; col++)
        {
            if (GPIO_voidGetPinValue(Copy_Config.ColPort[col], Copy_Config.ColPin[col]) == GPIO_LOW) // Check if the key is pressed
            {
                STK_voidDelayMs(30); // Debounce delay
                if (GPIO_voidGetPinValue(Copy_Config.ColPort[col], Copy_Config.ColPin[col]) == GPIO_LOW) 
                {
                    while (GPIO_voidGetPinValue(Copy_Config.ColPort[col], Copy_Config.ColPin[col]) == GPIO_LOW); // Wait until the key is released
                    key = KeypadDataMap[row][col]; // Return the corresponding character from the data map
                    return key;
                }
            }
        } 
    GPIO_voidSetPinValue(Copy_Config.RowPort[row], Copy_Config.RowPin[row], GPIO_HIGH); // Deactivate the current row

    } 
    return key; 
    
}
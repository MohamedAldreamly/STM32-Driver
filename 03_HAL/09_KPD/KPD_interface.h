/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/8/2026
 *  Vertion : V01
 *  Layer   : HAL
 *
 */

#ifndef _KPD_INTERFACE_H_
#define _KPD_INTERFACE_H_
 
#include "KPD_config.h"





typedef struct
{
    GPIO_Typedef* RowPort[KEYPAD_NUM_ROWS];
    u8 RowPin[KEYPAD_NUM_ROWS];
    GPIO_Typedef* ColPort [KEYPAD_NUM_COLS];
    u8 ColPin[KEYPAD_NUM_COLS];
} KPD_PinConfig;

u8 Keypad_Scan(KPD_PinConfig Copy_Config);
void Keypad_Init(KPD_PinConfig Copy_Config);


// KPD_PinConfig KeypadPins[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
//     {{GPIOA, 0}, {GPIOA, 4}, {GPIOA, 8}, {GPIOA, 12}},
//     {{GPIOA, 1}, {GPIOA, 5}, {GPIOA, 9}, {GPIOA, 13}},
//     {{GPIOA, 2}, {GPIOA, 6}, {GPIOA, 10}, {GPIOA, 14}},
//     {{GPIOA, 3}, {GPIOA, 7}, {GPIOA, 11}, {GPIOA, 15}}
// };


#endif //_KPD_INTERFACE_H_
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    STK_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */  

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

#include "STD_TYPES.h"

/* Clock Source Options */
#define STK_AHB_DIV_8    0
#define STK_AHB          1

void STK_voidInit(void);

void STK_voidDelayUs(u32 Copy_u32DelayUs);
void STK_voidDelayMs(u32 Copy_u32DelayMs);

#endif
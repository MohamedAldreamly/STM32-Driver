/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    AFIO_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/10/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#ifndef AFIO_INTERFACE_H_
#define AFIO_INTERFACE_H_

#include "STD_TYPES.h"

typedef enum
{
    AFIO_TIM2_NO_REMAP = 0,
    AFIO_TIM2_PARTIAL_REMAP_1,
    AFIO_TIM2_PARTIAL_REMAP_2,
    AFIO_TIM2_FULL_REMAP

} AFIO_TIM2_Remap_t;


typedef enum
{
    AFIO_TIM3_NO_REMAP = 0,
    AFIO_TIM3_PARTIAL_REMAP,
    AFIO_TIM3_FULL_REMAP

} AFIO_TIM3_Remap_t;


typedef enum
{
    AFIO_TIM4_NO_REMAP = 0,
    AFIO_TIM4_REMAP

} AFIO_TIM4_Remap_t;


void AFIO_Init(void);

void AFIO_SetTIM2Remap(AFIO_TIM2_Remap_t remap);
void AFIO_SetTIM3Remap(AFIO_TIM3_Remap_t remap);
void AFIO_SetTIM4Remap(AFIO_TIM4_Remap_t remap);

#endif

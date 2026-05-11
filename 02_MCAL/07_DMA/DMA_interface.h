/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DMA_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/11/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */
 
#ifndef ADC_DMA_INTERFACE_H
#define ADC_DMA_INTERFACE_H

#include "ADC_interface.h"

typedef enum
{
    ADC_DMA_MODE_NORMAL = 0,
    ADC_DMA_MODE_CIRCULAR

} ADC_DMA_enuMode_t;

typedef void (*ADC_DMA_CallBack_t)(void);

ADC_enuErrorStatus_t ADC_DMA_Init(ADC_DMA_enuMode_t Copy_enuMode);

ADC_enuErrorStatus_t ADC_DMA_Start(u16 * Copy_pu16Buffer,
                                   u16 Copy_u16Length);

ADC_enuErrorStatus_t ADC_DMA_Stop(void);

ADC_enuErrorStatus_t ADC_DMA_SetCallback(ADC_DMA_CallBack_t Copy_pvCallback);

#endif
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : HAL
 *
 */  

#ifndef _SSD_INTERFACE_H_
#define _SSD_INTERFACE_H_

#include "STD_TYPES.h"
#include "GPIO_interface.h"

#define SSD_ENABLED 1
#define SSD_DISABLED 0

#define SSD_COMMON_CATHODE 0
#define SSD_COMMON_ANODE   1

#define SSD_SEG_A      0
#define SSD_SEG_B      1
#define SSD_SEG_C      2
#define SSD_SEG_D      3
#define SSD_SEG_E      4
#define SSD_SEG_F      5
#define SSD_SEG_G      6
#define SSD_SEG_EN     7

typedef struct
{
    GPIO_Typedef* Port [8];
    u8 Pin [8];
    u8 SSD_Type; // Common Cathode Or Common Anode
    //u8 sevenSegmentConnectionMap [8][2] ; 
} SSD_PinConfig;

void SSD_voidInit(SSD_PinConfig Copy_Config);
void SSD_voidDisplay(SSD_PinConfig Copy_Config, u8 Copy_u8Number);
void SSD_voidClear(SSD_PinConfig Copy_Config);
void SSD_voidEnable(SSD_PinConfig Copy_Config);
void SSD_voidDisable(SSD_PinConfig Copy_Config);



#endif //_SSD_INTERFACE_H_
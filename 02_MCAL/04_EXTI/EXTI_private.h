/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/9/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

//==============================================================================================================

#include "STD_TYPES.h"

typedef	struct
{
	volatile	u32		IMR;   // Enable & Disable Interrupt
	volatile	u32		EMR;
	volatile	u32		RTSR;  // Rising
	volatile	u32		FTSR;  // Falling
	volatile	u32		SWIER;
	volatile	u32		PR;
	
}EXTI_Type;

#define EXTI ((volatile EXTI_Type *)0x40010400)   //Casting to pointer to struct

//==============================================================================================================


 /* in STM32F4 driver */

// typedef struct
// {
//     volatile u32 MEMRMP;
//     volatile u32 PMC;
//     volatile u32 EXTICR[4];
//     volatile u32 RESERVED[2];
//     volatile u32 CMPCR;
// } SYSCFG_Type;

// #define SYSCFG ((volatile SYSCFG_Type *)0x40010000)   //Casting to pointer to struct

typedef struct
{
    volatile u32 EVCR;
    volatile u32 MAPR;
    volatile u32 EXTICR[4];
    volatile u32 MAPR2;
} AFIO_Type;

#define AFIO ((volatile AFIO_Type *)0x40010000)
#endif

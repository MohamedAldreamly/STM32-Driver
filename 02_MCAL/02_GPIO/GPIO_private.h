/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldremly
 *  Date    : 5/6/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */  

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

typedef struct
{
    volatile u32 GPIO_CRL;
    volatile u32 GPIO_CRH;
    volatile u32 GPIO_IDR;
    volatile u32 GPIO_ODR;
    volatile u32 GPIO_BSRR;
    volatile u32 GPIO_BRR;
    volatile u32 GPIO_LCKR;

} GPIO_Typedef;

#define GPIOA        ((GPIO_Typedef*)0x40010800)            // define the boundary address of GPIO port A
#define GPIOB        ((GPIO_Typedef*)0x40010C00)            // define the boundary address of GPIO port B
#define GPIOC        ((GPIO_Typedef*)0x40011000)            // define the boundary address of GPIO port C



// #define DIOA_Base_Address        0x40010800            // define the boundary address of GPIO port A
// #define DIOB_Base_Address        0x40010C00            // define the boundary address of GPIO port B
// #define DIOC_Base_Address        0x40011000            // define the boundary address of GPIO port C

//         /*       REGISTERS ADDRESSES FOR Port A        */

// #define DIOA_CRL                 *((u32*)(DIOA_Base_Address + 0x00))
// #define DIOA_CRH                 *((u32*)(DIOA_Base_Address + 0x04))
// #define DIOA_IDR                 *((u32*)(DIOA_Base_Address + 0x08))
// #define DIOA_ODR                 *((u32*)(DIOA_Base_Address + 0x0c))
// #define DIOA_BSR                 *((u32*)(DIOA_Base_Address + 0x10))
// #define DIOA_BRR                 *((u32*)(DIOA_Base_Address + 0x14))
// #define DIOA_LCK                 *((u32*)(DIOA_Base_Address + 0x18))

#endif

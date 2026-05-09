/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    NVIC_private.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/8/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *  
 */ 
 
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


typedef struct
{
    u32 ISER[8];   // 0xE000E100 to 0xE000E11C
    u32 r[24];     // Reserved space to reach 0xE000E180
    u32 ICER[8];   // 0xE000E180 to 0xE000E184
    
} NVIC_Type;

#define NVIC ((volatile NVIC_Type*)0xE000E100)

#endif

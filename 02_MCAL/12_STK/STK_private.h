/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    STK_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */  

#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

typedef struct
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
} STK_Typedef;

#define STK     ((volatile STK_Typedef*)0xE000E010)

/* CTRL Register Bits */
#define STK_CTRL_ENABLE       0
#define STK_CTRL_TICKINT      1
#define STK_CTRL_CLKSOURCE    2
#define STK_CTRL_COUNTFLAG    16

#endif
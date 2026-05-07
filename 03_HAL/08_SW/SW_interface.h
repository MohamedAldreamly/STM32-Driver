/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    SW_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */

#ifndef _SW_INTERFACE_H_
#define _SW_INTERFACE_H_


#define SW_PRESSED 1
#define SW_RELEASED 0

#define SW_ACTIVE_HIGH 0
#define SW_ACTIVE_LOW 1

typedef struct
{
    GPIO_Typedef* Port;
    u8 Pin;
    u8 SW_Type; // Active High Or Active Low
} SW_PinConfig;


void SW_voidInit(SW_PinConfig Copy_Config);
u8 SW_u8GetState(SW_PinConfig Copy_Config);

#endif //_SW_INTERFACE_H_
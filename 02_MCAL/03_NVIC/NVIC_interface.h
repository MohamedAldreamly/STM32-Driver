/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    NVIC_interface.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/8/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H



void NVIC_voidEnableInterrupt(u8 Copy_u8IRQNumber);
void NVIC_voidDisableInterrupt(u8 Copy_u8IRQNumber);

#endif

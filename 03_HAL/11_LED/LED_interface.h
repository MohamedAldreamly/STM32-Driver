/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/8/2026
 *  Vertion : V01
 *  Layer   : HAL
 *
 */

#ifndef _LED_INTERFACE_H_
#define _LED_INTERFACE_H_

typedef struct
{
    GPIO_Typedef* Port;
    u8 Pin;
    u8 ActiveStatus; // Active High Or Active Low
} LED_Type;

#define LED_ACTIVE_HIGH 1
#define LED_ACTIVE_LOW 0

void LED_voidInit(LED_Type Copy_Config);
void LED_voidTurnOn(LED_Type Copy_Config);
void LED_voidTurnOff(LED_Type Copy_Config);
void LED_voidToggle(LED_Type Copy_Config);

#endif //_LED_INTERFACE_H_

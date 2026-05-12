/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/9/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
//==============================================================================================================

////////////////////////////  CallBack Functions Declerations
typedef void (*EXTI_Callback)(void);

/////////////////////////////  Functions Decleration

void EXTI_voidInit(u8 Copy_u8EXTILine, u8 Copy_u8Port, u8 Copy_u8EXTISenseMode , EXTI_Callback Copy_EXTI_CallBack) ;                                 
void EXTI_voidSetSignalLatch (u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode);
void EXTI_voidEnableEXTI     (u8 Copy_u8EXTILine                          );
void EXTI_voidDisableEXTI    (u8 Copy_u8EXTILine                          );

void EXTI_voidSetCallBack(u8 Copy_u8EXTILine, EXTI_Callback Copy_EXTI_CallBack);
//-------------------------------------------------
/////////////////////////External Interrupt Modes
#define		 FALLING_EDGE		0
#define		 RISING_EDGE		1
#define		 ON_CHANGE			2

//-------------------------------------------------
//////////////////////////Ports


// #define PORTA 0b0000
// #define PORTB 0b0001
// #define PORTC 0b0010
// #define PORTD 0b0011
// #define PORTE 0b0100
// #define PORTH 0b0111

#define EXTI_PORTA  0b0000
#define EXTI_PORTB  0b0001
#define EXTI_PORTC  0b0010
#define EXTI_PORTD  0b0011
#define EXTI_PORTE  0b0100
#define EXTI_PORTF  0b0101
#define EXTI_PORTG  0b0110

//-------------------------------------------------
//////////////////External Interrupt Lines
#define		 EXTI_LINE0			0
#define		 EXTI_LINE1			1
#define		 EXTI_LINE2			2
#define		 EXTI_LINE3			3

#define		 EXTI_LINE4			4
#define		 EXTI_LINE5			5
#define		 EXTI_LINE6			6
#define		 EXTI_LINE7			7

#define		 EXTI_LINE8			8
#define		 EXTI_LINE9			9
#define		 EXTI_LINE10		10
#define		 EXTI_LINE11		11

#define		 EXTI_LINE12		12
#define		 EXTI_LINE13		13
#define		 EXTI_LINE14		14
#define		 EXTI_LINE15		15

//-------------------------------------------------
/////////////////////////External Interrupt Numbers

#define EXTI0IRQn     6
#define EXTI1IRQn     7
#define EXTI2IRQn     8
#define EXTI3IRQn     9
#define EXTI4IRQn     10

#define EXTI5IRQn     23
#define EXTI6IRQn     23
#define EXTI7IRQn     23
#define EXTI8IRQn     23
#define EXTI9IRQn     23

#define EXTI10IRQn    40
#define EXTI11IRQn    40
#define EXTI12IRQn    40
#define EXTI13IRQn    40
#define EXTI14IRQn    40
#define EXTI15IRQn    40

//#define SYSCFG_EN       14

#define AFIO_EN 0
//==============================================================================================================

#endif
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldremly
 *  Date    : 5/6/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
#include "GPIO_private.h"
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H


//==============================================================================================================

#define GPIO_HIGH    1
#define GPIO_LOW     0

#define GPIO_PORT_HIGH    0xFFFF
#define GPIO_PORT_LOW     0


#define GPIO_PIN0       0
#define GPIO_PIN1       1
#define GPIO_PIN2       2
#define GPIO_PIN3       3
#define GPIO_PIN4       4
#define GPIO_PIN5       5
#define GPIO_PIN6       6
#define GPIO_PIN7       7
#define GPIO_PIN8       8
#define GPIO_PIN9       9
#define GPIO_PIN10      10
#define GPIO_PIN11      11
#define GPIO_PIN12      12
#define GPIO_PIN13      13
#define GPIO_PIN14      14
#define GPIO_PIN15      15

//==============================================================================================================

                       /* PIN MODES   */
					   
#define INPUT_ANLOG               0b0000
#define INPUT_FLOATING            0b0100
#define INPUT_PULLUP_PULLDOWN     0b1000

//For Speed 10
#define OUTPUT_SPEED_10MHZ_PP     0b0001
#define OUTPUT_SPEED_10MHZ_OD     0b0101
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101

//For Speed 2
#define OUTPUT_SPEED_2MHZ_PP      0b0010
#define OUTPUT_SPEED_2MHZ_OD      0b0110
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110

//For Speed 2
#define OUTPUT_SPEED_50MHZ_PP     0b0011
#define OUTPUT_SPEED_50MHZ_OD     0b0111
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111

//==============================================================================================================

    /*    M for MCAL   */
void GPIO_voidSetPinDirection   ( GPIO_Typedef* Copy_GPIO , u8 Copy_u8Pin , u8 Copy_u8Mode      );
void GPIO_voidSetPinValue       ( GPIO_Typedef* Copy_GPIO , u8 Copy_u8Pin , u8 Copy_u8Value     );
void  GPIO_u8GetPinValue        ( GPIO_Typedef* Copy_GPIO, u8 Copy_u8Pin , u8* Copy_u8Value );
void GPIO_voidSetPortDirection  ( GPIO_Typedef* Copy_GPIO , u8 Copy_u8Mode                      );
void GPIO_voidSetPortValue      ( GPIO_Typedef* Copy_GPIO , u16 Copy_u8Value                    );
void GPIO_u16GetPortValue       ( GPIO_Typedef* Copy_GPIO , u16* Copy_u8Value                   );
void GPIO_voidTogglePinValue    ( GPIO_Typedef* Copy_GPIO, u8 Copy_u8Pin );


//==============================================================================================================

#endif
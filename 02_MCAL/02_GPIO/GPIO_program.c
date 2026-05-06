/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GPIO_config.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldremly
 *  Date    : 5/6/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */  

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

//==============================================================================================================

void MDIO_voidSetPinDirection(GPIO_Typedef* Copy_GPIO, u8 Copy_u8Pin, u8 Copy_u8Mode)
	{

	if ((Copy_GPIO == NULL) ||(Copy_u8Pin > 15))
	{
        return;
    }
	
    if (Copy_u8Pin <= 7)
    {
        /* Clear the 4 configuration bits of the selected pin */
		CLR_4BIT(Copy_GPIO->GPIO_CRL,Copy_u8Pin);

        /* Set the new mode */
        Copy_GPIO->GPIO_CRL |=  ((u32)Copy_u8Mode << (Copy_u8Pin * 4));
    }
    else if (Copy_u8Pin <= 15)
    {
        Copy_u8Pin = Copy_u8Pin - 8;

        /* Clear the 4 configuration bits of the selected pin */
		CLR_4BIT(Copy_GPIO->GPIO_CRH,Copy_u8Pin);

        /* Set the new mode */
        Copy_GPIO->GPIO_CRH |=  ((u32)Copy_u8Mode << (Copy_u8Pin * 4));
    }
    else
    {
        /* Wrong pin number */
    }
}


void GPIO_voidSetPinValue      ( GPIO_Typedef* Copy_GPIO, u8 Copy_u8Pin , u8 u8Copy_u8Value   )
{
	if ((Copy_GPIO == NULL) ||(Copy_u8Pin > 15))
	{
		return;
	}

	switch (u8Copy_u8Value)
	{
		case GPIO_HIGH:
			SET_BIT(Copy_GPIO->GPIO_BSRR,Copy_u8Pin);   
			
			break;
		case GPIO_LOW:
			CLR_BIT(Copy_GPIO->GPIO_BSRR,(Copy_u8Pin+ 16));  // Reset the pin
			//SET_BIT(Copy_GPIO->GPIO_BRR,Copy_u8Pin);   

			break;
		default:
			/* Wrong value */
			break;
	}

}

void  GPIO_u8GetPinValue  ( GPIO_Typedef* Copy_GPIO, u8 Copy_u8Pin , u8* u8Copy_u8Value )
{
	if ((Copy_GPIO == NULL) ||(Copy_u8Pin > 15) || (u8Copy_u8Value == NULL))
	{
		return;
	}

	*u8Copy_u8Value = GET_BIT(Copy_GPIO->GPIO_IDR, Copy_u8Pin);	
}

void GPIO_voidSetPortDirection ( GPIO_Typedef* Copy_GPIO , u8 Copy_u8Mode   )
{

	for (u8 i = 0; i < 7; i++)
    {
        /* Clear the 4 configuration bits of the selected pin */
		Copy_GPIO->GPIO_CRL &= ~((u32)0xF << ((i) * 4));
        /* Set the new mode */
        Copy_GPIO->GPIO_CRL |=  ((u32)Copy_u8Mode << (i * 4));
    }
    for (u8 i = 0; i < 7; i++)
    {
        /* Clear the 4 configuration bits of the selected pin */
		Copy_GPIO->GPIO_CRH &= ~((u32)0xF << ((i) * 4));

        /* Set the new mode */
        Copy_GPIO->GPIO_CRH |=  ((u32)Copy_u8Mode << (i * 4));
    }
    
}

void GPIO_voidSetPortValue     ( GPIO_Typedef* Copy_GPIO ,u16 Copy_u16Value )
{
	Copy_GPIO->GPIO_ODR = Copy_u16Value;
}
u16  GPIO_u16GetPortValue      ( GPIO_Typedef* Copy_GPIO , u16* Copy_u8Value       )
{
	*Copy_u8Value = Copy_GPIO->GPIO_IDR;
}


//==============================================================================================================

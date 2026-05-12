/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    NVIC_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/8/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"

/*
 * NVIC ISER/ICER registers are Write-1-to-Set/Clear registers.
 * Writing '1' affects only the targeted bit,
 * while writing '0' has no effect on other bits.
 *
 * No need to use OR assignment (|=).
 */

void NVIC_voidEnableInterrupt(u8 Copy_u8IRQNumber)
{
	NVIC->ISER[Copy_u8IRQNumber / 32] = (1UL << (Copy_u8IRQNumber % 32));
}

void NVIC_voidDisableInterrupt(u8 Copy_u8IRQNumber)
{
	NVIC->ICER[Copy_u8IRQNumber / 32] = (1UL << (Copy_u8IRQNumber % 32));
}

//===========================================================================================================


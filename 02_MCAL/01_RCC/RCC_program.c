/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */ 

/* include Libraries  */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* include files of lower layer */
// Nothing Because this driver in MCAL Layer 

/* Own Driver Files */
#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"

//==============================================================================================================

void RCC_voidInitSysClock( void )
{
	#if  RCC_CLOCK_TYPE == RCC_HSI
		// Enable HSI
		SET_BIT( MRCC->CR , HSION );
		// Wait Until HSI Is Ready
		while ( GET_BIT( MRCC->CR , HSIRDY ) == 0 );
		
		// Select HSI As System Clock
		CLR_2BIT( MRCC->CFGR , RCC_SW_HSI );
		SET_2BIT( MRCC->CFGR , RCC_SW_POSITION , RCC_SW_HSI );
	#elif RCC_CLOCK_TYPE == RCC_HSE
		// Enable HSE
		SET_BIT( MRCC->CR , HSEON );
		// Wait Until HSE Is Ready
		while ( GET_BIT( MRCC->CR , HSERDY ) == 0 );
		// Select HSE As System Clock
		CLR_2BIT( MRCC->CFGR , RCC_SW_HSE );
		SET_2BIT( MRCC->CFGR , RCC_SW_POSITION , RCC_SW_HSE );
	#elif RCC_CLOCK_TYPE == RCC_PLL
		// Enable PLL
		SET_BIT( MRCC->CR , PLLON );
		// Wait Until PLL Is Ready
		while ( GET_BIT( MRCC->CR , PLLRDY ) == 0 );

		// Select PLL As System Clock
		CLR_2BIT( MRCC->CFGR , RCC_SW_PLL );
		SET_2BIT( MRCC->CFGR , RCC_SW_POSITION , RCC_SW_PLL );
		//PLL multiplication factor
		CLR_4BIT( MRCC->CFGR , RCC_PLLMUL_POSITION );
		SET_4BIT_VALUE( MRCC->CFGR , RCC_PLLMUL_POSITION , RCC_PLL_MUL );
		
		//HPRE: AHB prescaler
		CLR_3BIT( MRCC->CFGR , RCC_HPRE_POSITION );
		SET_3BIT_VALUE( MRCC->CFGR , RCC_HPRE_POSITION , RCC_AHB_PRESCALER );
		
		//PPRE1: APB1 prescaler
		CLR_3BIT( MRCC->CFGR , RCC_PPRE1_POSITION );
		SET_3BIT_VALUE( MRCC->CFGR , RCC_PPRE1_POSITION , RCC_APB1_PRESCALER );

		//PPRE2: APB2 prescaler
		CLR_3BIT( MRCC->CFGR , RCC_PPRE2_POSITION );
		SET_3BIT_VALUE( MRCC->CFGR , RCC_PPRE2_POSITION , RCC_APB2_PRESCALER );
		
		#if  RCC_PLL_INPUT == RCC_PLL_HSI_DIVIDED_BY_2
			// Select PLL HSI/2 As System Clock
			CLR_BIT( MRCC->CFGR , RCC_PLLSRC_POSITION );
		#elif RCC_PLL_INPUT == RCC_PLL_HSE
			// Select PLL HSE As System Clock
			SET_BIT( MRCC->CFGR , RCC_PLLSRC_POSITION );
			CLR_BIT( MRCC->CFGR ,RCC_PLLXTPRE_POSITION);
		#elif RCC_PLL_INPUT == RCC_PLL_HSE_DIVIDED_BY_2
			CLR_BIT( MRCC->CFGR ,RCC_PLLXTPRE_POSITION);
		#endif 
	#endif
}

//==============================================================================================================

void RCC_voidEnablePeripheralClock( u8 Copy_u8BusId , u8 Copy_u8PeripheralId )
{
switch (Copy_u8BusId)
	{
	case AHB_BUS:
		SET_BIT( MRCC->AHBENR , Copy_u8PeripheralId );
		break;
	case APB1_BUS:
		SET_BIT( MRCC->APB1ENR , Copy_u8PeripheralId );
		break;
	case APB2_BUS:
		SET_BIT( MRCC->APB2ENR , Copy_u8PeripheralId );
		break;
	default:
		/* Wrong Bus Id */
		break;
	}
}

//==============================================================================================================

void RCC_voidDisablePeripheralClock( u8 Copy_u8BusId , u8 Copy_u8PeripheralId )
{
	switch (Copy_u8BusId)
	{
	case AHB_BUS:
		CLR_BIT( MRCC->AHBENR , Copy_u8PeripheralId );
		break;
	case APB1_BUS:
		CLR_BIT( MRCC->APB1ENR , Copy_u8PeripheralId );
		break;
	case APB2_BUS:
		CLR_BIT( MRCC->APB2ENR , Copy_u8PeripheralId );
		break;
	default:
		/* Wrong Bus Id */
		break;
	}
	
}

void RCC_voidResetPeripheralClock( u8 Copy_u8BusId , u8 Copy_u8PeripheralId )
{
	switch (Copy_u8BusId)
	{
	case AHB_BUS:
		SET_BIT( MRCC->AHBRSTR , Copy_u8PeripheralId );
		CLR_BIT( MRCC->AHBRSTR , Copy_u8PeripheralId );
		break;
	case APB1_BUS:
		SET_BIT( MRCC->APB1RSTR , Copy_u8PeripheralId );
		CLR_BIT( MRCC->APB1RSTR , Copy_u8PeripheralId );
		break;
	case APB2_BUS:
		SET_BIT( MRCC->APB2RSTR , Copy_u8PeripheralId );
		CLR_BIT( MRCC->APB2RSTR , Copy_u8PeripheralId );
		break;
	default:
		/* Wrong Bus Id */
		break;
	}
}

//==============================================================================================================

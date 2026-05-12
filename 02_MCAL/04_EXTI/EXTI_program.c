/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    EXTI_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/9/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "NVIC_interface.h"
#include "RCC_interface.h"

#include"EXTI_interface.h"
#include"EXTI_config.h"
#include"EXTI_private.h"
//==============================================================================================================

#define NULL	0

EXTI_Callback EXTICallbacks [16] = {NULL} ;
u8 EXTILineNumberNVICMap[16] = {6,7,8,9,10,23,23,23,23,23,40,40,40,40,40,40} ;  // Map between EXTI line number and NVIC IRQ number	

//==============================================================================================================

void EXTI_voidInit(u8 Copy_u8EXTILine, u8 Copy_u8Port, u8 Copy_u8EXTISenseMode , EXTI_Callback Copy_EXTI_CallBack)                                
{

	//RCC_voidEnablePeripheralClock( APB2_BUS , SYSCFG_EN );
	RCC_voidEnablePeripheralClock( APB2_BUS, AFIO_EN);

	/* EXTI line and port source selection */

	u8 AFIO_EXTICRIndex    = Copy_u8EXTILine / 4;
	u8 AFIO_EXTICRPosition = (Copy_u8EXTILine % 4) * 4;

	CLR_4BIT(AFIO->EXTICR[AFIO_EXTICRIndex], AFIO_EXTICRPosition);
	SET_4BIT_VALUE(AFIO->EXTICR[AFIO_EXTICRIndex], AFIO_EXTICRPosition, Copy_u8Port);

	// u8 SYSConfigEXTICRIndex    = Copy_u8EXTILine / 4;
	// u8 SYSConfigEXTICRPosition = (Copy_u8EXTILine % 4) * 4;

	// CLR_4BIT(SYSCFG->EXTICR[SYSConfigEXTICRIndex], SYSConfigEXTICRPosition);
	// SET_4BIT_VALUE(SYSCFG->EXTICR[SYSConfigEXTICRIndex], SYSConfigEXTICRPosition, Copy_u8Port);

	/* Clear old trigger configuration */
	CLR_BIT(EXTI->RTSR, Copy_u8EXTILine);
	CLR_BIT(EXTI->FTSR, Copy_u8EXTILine);

	/* Configure trigger here */
	/* Rising / Falling / Both */

	
	
	EXTICallbacks [Copy_u8EXTILine] = Copy_EXTI_CallBack;
	
	if(Copy_u8EXTISenseMode == FALLING_EDGE)
	{
		SET_BIT(EXTI -> FTSR , Copy_u8EXTILine);
		/*  Fore more speed  ==> (EXTI_Type -> FTSR) |= (1 <<  LineNumber);  */
	}
	else if(Copy_u8EXTISenseMode == RISING_EDGE)
	{
		SET_BIT(EXTI -> RTSR , Copy_u8EXTILine);
	}
	else if(Copy_u8EXTISenseMode == ON_CHANGE)
	{
		SET_BIT(EXTI -> RTSR , Copy_u8EXTILine);
		SET_BIT(EXTI -> FTSR , Copy_u8EXTILine);
	}
	
	/* Clear pending flag before enabling */
	SET_BIT(EXTI->PR, Copy_u8EXTILine);

	/* Enable EXTI line */
	SET_BIT(EXTI->IMR, Copy_u8EXTILine);

	/* Enable NVIC IRQ */
	NVIC_voidEnableInterrupt(EXTILineNumberNVICMap[Copy_u8EXTILine]);
	
}
//==============================================================================================================

void EXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode)
{	
	CLR_BIT(EXTI->RTSR, Copy_u8EXTILine);
	CLR_BIT(EXTI->FTSR, Copy_u8EXTILine);

	switch(Copy_u8EXTISenseMode)
	{
		case	RISING_EDGE		:	SET_BIT(EXTI -> RTSR , Copy_u8EXTILine);	break;
		case	FALLING_EDGE	:	SET_BIT(EXTI -> FTSR , Copy_u8EXTILine);	break;
		case	ON_CHANGE		:	SET_BIT(EXTI -> RTSR , Copy_u8EXTILine);	
									SET_BIT(EXTI -> FTSR , Copy_u8EXTILine);	break;
	}
	SET_BIT(EXTI -> IMR , Copy_u8EXTILine);
}


//==============================================================================================================

void EXTI_voidEnableEXTI(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI -> IMR , Copy_u8EXTILine);
	NVIC_voidEnableInterrupt(EXTILineNumberNVICMap[Copy_u8EXTILine]);

}


//==============================================================================================================

void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI -> IMR , Copy_u8EXTILine);
	NVIC_voidDisableInterrupt(EXTILineNumberNVICMap[Copy_u8EXTILine]);
}


//////////////////////////////////////////////////// ISR 0 /////////////////////////////////////////////////////

void EXTI_voidSetCallBack(u8 Copy_u8EXTILine,EXTI_Callback Copy_EXTI_CallBack)
{
		EXTICallbacks [Copy_u8EXTILine] = Copy_EXTI_CallBack ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EXTI0_IRQHandler(void)
{
	if (EXTICallbacks[0] != NULL)
	{
		EXTICallbacks[0]();  // Calling the func @ main
	}
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 0);
}

void EXTI1_IRQHandler(void)
{
	if (EXTICallbacks[1] != NULL)
	{
		EXTICallbacks[1]();  // Calling the func @ main
	}
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 1);
}
void EXTI2_IRQHandler(void)
{
	if (EXTICallbacks[2] != NULL)
	{
		EXTICallbacks[2]();  // Calling the func @ main
	}
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 2);
}
void EXTI3_IRQHandler(void)
{
	if (EXTICallbacks[3] != NULL)
	{
		EXTICallbacks[3]();  // Calling the func @ main
	}
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 3);
}

void EXTI4_IRQHandler(void)
{
	if (EXTICallbacks[4] != NULL)
	{
		EXTICallbacks[4]();  // Calling the func @ main
	}
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 4);
}
void EXTI9_5_IRQHandler(void)
{
	if (EXTI -> PR & (1 << 5))  // Check if the pending bit of line 5 is set
	{
		if (EXTICallbacks[5] != NULL)
		{
			EXTICallbacks[5]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 5);
	}

	if (EXTI -> PR & (1 << 6))  // Check if the pending bit of line 6 is set
	{
		if (EXTICallbacks[6] != NULL)
		{
			EXTICallbacks[6]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 6);
	}

	if (EXTI -> PR & (1 << 7))  // Check if the pending bit of line 5 is set
	{
	if (EXTICallbacks[7] != NULL)
		{
			EXTICallbacks[7]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 7);
	}

	if (EXTI -> PR & (1 << 8))  // Check if the pending bit of line 5 is set
	{
		if (EXTICallbacks[8] != NULL)
		{
			EXTICallbacks[8]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 8);
	}

	if (EXTI -> PR & (1 << 9))  // Check if the pending bit of line 5 is set
	{
		if (EXTICallbacks[9] != NULL)
		{
			EXTICallbacks[9]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI -> PR & (1 << 10))  // Check if the pending bit of line 10 is set
	{
		if (EXTICallbacks[10] != NULL)
		{
			EXTICallbacks[10]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 10);
	}

	if (EXTI -> PR & (1 << 11))  // Check if the pending bit of line 11 is set
	{
		if (EXTICallbacks[11] != NULL)
		{
			EXTICallbacks[11]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 11);
	}

	if (EXTI -> PR & (1 << 12))  // Check if the pending bit of line 12 is set
	{
		if (EXTICallbacks[12] != NULL)
		{
			EXTICallbacks[12]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 12);
	}
	
	if (EXTI -> PR & (1 << 13))  // Check if the pending bit of line 13 is set
	{
		if (EXTICallbacks[13] != NULL)
		{
			EXTICallbacks[13]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 13);
	}

	if (EXTI -> PR & (1 << 14))  // Check if the pending bit of line 14 is set
	{
		if (EXTICallbacks[14] != NULL)
		{
			EXTICallbacks[14]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 14);
	}
	if (EXTI -> PR & (1 << 15))  // Check if the pending bit of line 15 is set
	{
		if (EXTICallbacks[15] != NULL)
		{
			EXTICallbacks[15]();  // Calling the func @ main
		}
		SET_BIT(EXTI -> PR , 15);
	}
}
//==============================================================================================================


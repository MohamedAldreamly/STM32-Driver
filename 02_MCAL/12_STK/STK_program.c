/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    STK_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */  

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

void STK_voidInit(void)
{
    /* Disable SysTick */
    CLR_BIT(STK->CTRL, STK_CTRL_ENABLE);

    /* Disable SysTick interrupt */
    CLR_BIT(STK->CTRL, STK_CTRL_TICKINT);

#if STK_CLOCK_SOURCE == STK_AHB_DIV_8

    /* Clock source = AHB / 8 */
    CLR_BIT(STK->CTRL, STK_CTRL_CLKSOURCE);

#elif STK_CLOCK_SOURCE == STK_AHB

    /* Clock source = AHB */
    SET_BIT(STK->CTRL, STK_CTRL_CLKSOURCE);

#else
    #error "Wrong STK_CLOCK_SOURCE Configuration"
#endif

    /* Clear LOAD and VAL */
    STK->LOAD = 0;
    STK->VAL  = 0;
}

void STK_voidDelayUs(u32 Copy_u32DelayUs)
{
    /*
     * This function assumes:
     * System Clock = 8MHz
     * SysTick Clock = AHB / 8 = 1MHz
     * So 1 tick = 1 us
     */

    if (Copy_u32DelayUs == 0)
    {
        return;
    }

    /* Load delay value */
    STK->LOAD = Copy_u32DelayUs - 1;

    /* Clear current value */
    STK->VAL = 0;

    /* Enable SysTick */
    SET_BIT(STK->CTRL, STK_CTRL_ENABLE);

    /* Wait until COUNTFLAG is set */
    while (GET_BIT(STK->CTRL, STK_CTRL_COUNTFLAG) == 0);

    /* Disable SysTick */
    CLR_BIT(STK->CTRL, STK_CTRL_ENABLE);

    /* Clear LOAD and VAL */
    STK->LOAD = 0;
    STK->VAL  = 0;
}

void STK_voidDelayMs(u32 Copy_u32DelayMs)
{
    u32 Local_u32Counter;

    for (Local_u32Counter = 0; Local_u32Counter < Copy_u32DelayMs; Local_u32Counter++)
    {
        STK_voidDelayUs(1000);
    }
}
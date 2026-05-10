/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    AFIO_program.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/10/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "RCC_interface.h"

void AFIO_Init(void)
{
    /*
     * Enable AFIO clock on APB2
     */
    RCC_voidEnablePeripheralClock(APB2_BUS, AFIO_RCC);
}

//	enum value == hardware value

void AFIO_SetTIM2Remap(AFIO_TIM2_Remap_t remap)
{
    /* Check if the selected remap option is valid */
    if(remap > AFIO_TIM2_FULL_REMAP)
    {
        /* Exit function if remap value is invalid */
        return;
    }

    /* Clear TIM2 remap bits before writing new value */
    CLR_MASK(AFIO->MAPR, AFIO_MAPR_TIM2_REMAP_MASK);

    /* Write TIM2 remap value into MAPR register */
    SET_MASK(AFIO->MAPR, ((u32)remap << AFIO_MAPR_TIM2_REMAP));
}



void AFIO_SetTIM3Remap(AFIO_TIM3_Remap_t remap)
{
    if(remap > AFIO_TIM3_FULL_REMAP)
    {
        return;
    }

    CLR_MASK(AFIO->MAPR, AFIO_MAPR_TIM3_REMAP_MASK);

    switch(remap)
    {
        case AFIO_TIM3_NO_REMAP:
            SET_MASK(AFIO->MAPR, (AFIO_TIM3_REMAP_NONE << AFIO_MAPR_TIM3_REMAP));
            break;

        case AFIO_TIM3_PARTIAL_REMAP:
            SET_MASK(AFIO->MAPR, (AFIO_TIM3_REMAP_PARTIAL << AFIO_MAPR_TIM3_REMAP));
            break;

        case AFIO_TIM3_FULL_REMAP:
            SET_MASK(AFIO->MAPR, (AFIO_TIM3_REMAP_FULL << AFIO_MAPR_TIM3_REMAP));
            break;

        default:
            break;
    }
}


void AFIO_SetTIM4Remap(AFIO_TIM4_Remap_t remap)
{
    if(remap > AFIO_TIM4_REMAP)
    {
        return;
    }

    if(remap == AFIO_TIM4_REMAP)
    {
        SET_BIT(AFIO->MAPR, AFIO_MAPR_TIM4_REMAP);
    }
    else
    {
        CLR_BIT(AFIO->MAPR, AFIO_MAPR_TIM4_REMAP);
    }
}

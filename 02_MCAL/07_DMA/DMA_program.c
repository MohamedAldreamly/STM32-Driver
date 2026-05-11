/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DMA_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/11/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */ 
 
//==============================================================================================================
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "ADC_private.h"

static ADC_DMA_CallBack_t ADC_DMA_pvCallback = 0;

ADC_enuErrorStatus_t ADC_DMA_Init(ADC_DMA_enuMode_t Copy_enuMode)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;

    volatile DMA_Channel_t * Local_pstrChannel =
        &DMA1->Channel[DMA_CHANNEL_1_INDEX];

    if (Copy_enuMode > ADC_DMA_MODE_CIRCULAR)
    {
        Local_enuErrorStatus = ADC_enuNOK;
    }
    else
    {
        /* Disable DMA Channel before configuration */
        DMA_CLEAR_BIT(Local_pstrChannel->CCR, DMA_CCR_EN_BIT);

        /* Peripheral address = ADC1_DR */
        Local_pstrChannel->CPAR = ADC1_DR_ADDRESS;

        /* Direction: Peripheral to Memory */
        DMA_CLEAR_BIT(Local_pstrChannel->CCR, DMA_CCR_DIR_BIT); //Peripheral -> Memory

        /* Peripheral increment disabled */
        DMA_CLEAR_BIT(Local_pstrChannel->CCR, DMA_CCR_PINC_BIT); // fixred address 

        /* Memory increment enabled */
        DMA_SET_BIT(Local_pstrChannel->CCR, DMA_CCR_MINC_BIT);

        /* Peripheral size = 16-bit */
        DMA_WRITE_FIELD(Local_pstrChannel->CCR,
                        DMA_TWO_BITS_MASK,
                        DMA_CCR_PSIZE_START_BIT,
                        DMA_SIZE_16_BIT);

        /* Memory size = 16-bit */
        DMA_WRITE_FIELD(Local_pstrChannel->CCR,
                        DMA_TWO_BITS_MASK,
                        DMA_CCR_MSIZE_START_BIT,
                        DMA_SIZE_16_BIT);

        /* Priority = High */
        DMA_WRITE_FIELD(Local_pstrChannel->CCR,
                        DMA_TWO_BITS_MASK,
                        DMA_CCR_PL_START_BIT,
                        DMA_PRIORITY_HIGH);

        /* Normal or Circular mode */
        if (Copy_enuMode == ADC_DMA_MODE_CIRCULAR)
        {
            DMA_SET_BIT(Local_pstrChannel->CCR, DMA_CCR_CIRC_BIT);
        }
        else
        {
            DMA_CLEAR_BIT(Local_pstrChannel->CCR, DMA_CCR_CIRC_BIT);
        }

        /* Enable transfer complete interrupt */
        DMA_SET_BIT(Local_pstrChannel->CCR, DMA_CCR_TCIE_BIT);

        /* Enable ADC DMA request */
        ADC_SET_BIT(ADC1_REGS->CR2, ADC_CR2_DMA_BIT);
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_DMA_Start(u16 * Copy_pu16Buffer,
                                   u16 Copy_u16Length)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;

    volatile DMA_Channel_t * Local_pstrChannel =
        &DMA1->Channel[DMA_CHANNEL_1_INDEX];

    if (Copy_pu16Buffer == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (Copy_u16Length == 0)
    {
        Local_enuErrorStatus = ADC_enuNOK;
    }
    else
    {
        /* Disable channel before changing memory and length */
        DMA_CLEAR_BIT(Local_pstrChannel->CCR, DMA_CCR_EN_BIT);

        /* Clear old flags */
        DMA_SET_BIT(DMA1->IFCR, DMA_IFCR_CGIF1_BIT);
        DMA_SET_BIT(DMA1->IFCR, DMA_IFCR_CTCIF1_BIT);
        DMA_SET_BIT(DMA1->IFCR, DMA_IFCR_CHTIF1_BIT);
        DMA_SET_BIT(DMA1->IFCR, DMA_IFCR_CTEIF1_BIT);

        /* Memory address */
        Local_pstrChannel->CMAR = (u32)Copy_pu16Buffer;

        /* Number of transfers */
        Local_pstrChannel->CNDTR = Copy_u16Length;

        /* Enable DMA channel */
        DMA_SET_BIT(Local_pstrChannel->CCR, DMA_CCR_EN_BIT);
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_DMA_Stop(void)
{
    volatile DMA_Channel_t * Local_pstrChannel =
        &DMA1->Channel[DMA_CHANNEL_1_INDEX];

    DMA_CLEAR_BIT(Local_pstrChannel->CCR, DMA_CCR_EN_BIT);

    ADC_CLEAR_BIT(ADC1_REGS->CR2, ADC_CR2_DMA_BIT);

    return ADC_enuOK;
}


ADC_enuErrorStatus_t ADC_DMA_SetCallback(ADC_DMA_CallBack_t Copy_pvCallback)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;

    if (Copy_pvCallback == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else
    {
        ADC_DMA_pvCallback = Copy_pvCallback;
    }

    return Local_enuErrorStatus;
}

//==============================================================================================================

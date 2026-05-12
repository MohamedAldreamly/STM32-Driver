/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/11/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */ 
 
//=====================================================================================================================
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "RCC_private.h"
#include "NVIC_interface.h"


#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/* =========================================================
 * Private Global Variables
 * ========================================================= */

static volatile ADC_strRegDef_t * ADC_ApstrUnits[ADC_MAX_UNITS] =
{
    ADC1_REGS,
    ADC2_REGS,
    ADC3_REGS
};

static const u8 ADC_Au8IRQNumbers[ADC_MAX_UNITS] =
{
    18,   /* ADC1 & ADC2 */
    18,   /* ADC1 & ADC2 */
    47    /* ADC3 */
};

static ADC_enuState_t ADC_AenuState[ADC_MAX_UNITS] =
{
    ADC_STATE_IDLE,
    ADC_STATE_IDLE,
    ADC_STATE_IDLE
};

static ADC_CallBack_t ADC_ApfCallback[ADC_MAX_UNITS] = {0};


/* =========================================================
 * Private Functions Prototypes
 * ========================================================= */

static u8 ADC_u8IsValidUnit(ADC_enuUnit_t Copy_enuUnit);
static u8 ADC_u8IsValidChannel(ADC_enuChannel_t Copy_enuChannel);
static void ADC_vidSelectRegularChannel(volatile ADC_strRegDef_t * Copy_pstrADC,
                                        ADC_enuChannel_t Copy_enuChannel);
static void ADC_vidSetSampleTime(volatile ADC_strRegDef_t * Copy_pstrADC,
                                 ADC_enuChannel_t Copy_enuChannel,
                                 u8 Copy_u8SampleTime);


/* =========================================================
 * Public Functions
 * ========================================================= */

ADC_enuErrorStatus_t ADC_Init(ADC_enuUnit_t Copy_enuUnit,
                              const ADC_strConfig_t * Copy_pstrConfig)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;
    u32 Local_u32Timeout = ADC_TIMEOUT_MAX;

    if (Copy_pstrConfig == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else if ((Copy_pstrConfig->Mode != ADC_MODE_SINGLE_CONVERSION) ||
             (Copy_pstrConfig->TriggerSource != ADC_TRIGGER_SOFTWARE))
    {
        Local_enuErrorStatus = ADC_enuInvalidConfig;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        ADC_AenuState[Copy_enuUnit] = ADC_STATE_IDLE;

        /* Disable ADC before configuration */
        ADC_CLEAR_BIT(Local_pstrADC->CR2, ADC_CR2_ADON_BIT);

        /* Single conversion mode */
        ADC_CLEAR_BIT(Local_pstrADC->CR2, ADC_CR2_CONT_BIT);

        /* Disable scan mode NOW */
        ADC_CLEAR_BIT(Local_pstrADC->CR1, ADC_CR1_SCAN_BIT);

        /* Data alignment */
        if (Copy_pstrConfig->DataAlignment == ADC_ALIGN_LEFT)
        {
            ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_ALIGN_BIT);
        }
        else
        {
            ADC_CLEAR_BIT(Local_pstrADC->CR2, ADC_CR2_ALIGN_BIT);
        }

        /* Software trigger for regular conversion */
        ADC_WRITE_FIELD(Local_pstrADC->CR2,
                        ADC_THREE_BITS_MASK,
                        ADC_CR2_EXTSEL_START_BIT,
                        ADC_REGULAR_TRIGGER_SWSTART); // By Software

		// you must set bit when you want to start By Software
        ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_EXTTRIG_BIT);

        /* Interrupt mode: currently EOC only */
        if (Copy_pstrConfig->InterruptMode == ADC_INTERRUPT_EOC)
        {
            ADC_SET_BIT(Local_pstrADC->CR1, ADC_CR1_EOCIE_BIT);
        }
        else
        {
            ADC_CLEAR_BIT(Local_pstrADC->CR1, ADC_CR1_EOCIE_BIT);
        }

        /* Regular sequence length = 1 conversion */
        ADC_WRITE_FIELD(Local_pstrADC->SQR1,
                        ADC_REGULAR_SEQUENCE_LEN_MASK,
                        ADC_SQR1_L_START_BIT,
                        ADC_REGULAR_SINGLE_CONVERSION_LENGTH);

        /* Enable ADC */
        ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_ADON_BIT);

        /* Reset calibration */
        ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_RSTCAL_BIT);

        Local_u32Timeout = ADC_TIMEOUT_MAX;
        while ((ADC_GET_BIT(Local_pstrADC->CR2, ADC_CR2_RSTCAL_BIT) == 1U) &&
               (Local_u32Timeout > 0U))
        {
            Local_u32Timeout--;
        }

        if (Local_u32Timeout == 0U)
        {
            Local_enuErrorStatus = ADC_enuTimeout;
        }
        else
        {
            /* Start calibration */
            ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_CAL_BIT);

            Local_u32Timeout = ADC_TIMEOUT_MAX;
            while ((ADC_GET_BIT(Local_pstrADC->CR2, ADC_CR2_CAL_BIT) == 1U) &&
                   (Local_u32Timeout > 0U))
            {
                Local_u32Timeout--;
            }

            if (Local_u32Timeout == 0U)
            {
                Local_enuErrorStatus = ADC_enuTimeout;
            }
        }
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_DeInit(ADC_enuUnit_t Copy_enuUnit)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;

    if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        Local_pstrADC->SR    = 0;
        Local_pstrADC->CR1   = 0;
        Local_pstrADC->CR2   = 0;
        Local_pstrADC->SMPR1 = 0;
        Local_pstrADC->SMPR2 = 0;
        Local_pstrADC->SQR1  = 0;
        Local_pstrADC->SQR2  = 0;
        Local_pstrADC->SQR3  = 0;

        ADC_AenuState[Copy_enuUnit] = ADC_STATE_IDLE;
        ADC_ApfCallback[Copy_enuUnit] = 0;
    }

    return Local_enuErrorStatus;
}

ADC_enuErrorStatus_t ADC_StartConversion(ADC_enuUnit_t Copy_enuUnit,
                                         ADC_enuChannel_t Copy_enuChannel)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;

    if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else if (ADC_u8IsValidChannel(Copy_enuChannel) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidChannel;
    }
    else if (ADC_AenuState[Copy_enuUnit] == ADC_STATE_BUSY)
    {
        Local_enuErrorStatus = ADC_enuBusy;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        ADC_AenuState[Copy_enuUnit] = ADC_STATE_BUSY;

        ADC_vidSelectRegularChannel(Local_pstrADC, Copy_enuChannel);

        ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_SWSTART_BIT);
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_GetResultPolling(ADC_enuUnit_t Copy_enuUnit,
                                          u16 * Copy_pu16Result)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;
    u32 Local_u32Timeout = ADC_TIMEOUT_MAX;

    if (Copy_pu16Result == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        while ((ADC_GET_BIT(Local_pstrADC->SR, ADC_SR_EOC_BIT) == 0U) &&
               (Local_u32Timeout > 0U))
        {
            Local_u32Timeout--;
        }

        if (Local_u32Timeout == 0U)
        {
            Local_enuErrorStatus = ADC_enuTimeout;
        }
        else
        {
            *Copy_pu16Result = (u16)(Local_pstrADC->DR & ADC_DATA_MASK);

            ADC_AenuState[Copy_enuUnit] = ADC_STATE_IDLE;
        }
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_GetResult(ADC_enuUnit_t Copy_enuUnit,
                                   u16 * Copy_pu16Result)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;

    if (Copy_pu16Result == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        *Copy_pu16Result = (u16)(Local_pstrADC->DR & ADC_DATA_MASK);
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_StartConversionInterrupt(ADC_enuUnit_t Copy_enuUnit,
                                                  ADC_enuChannel_t Copy_enuChannel)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;

    if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else if (ADC_u8IsValidChannel(Copy_enuChannel) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidChannel;
    }
    else if (ADC_ApfCallback[Copy_enuUnit] == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (ADC_AenuState[Copy_enuUnit] == ADC_STATE_BUSY)
    {
        Local_enuErrorStatus = ADC_enuBusy;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        ADC_AenuState[Copy_enuUnit] = ADC_STATE_BUSY;

        ADC_vidSelectRegularChannel(Local_pstrADC, Copy_enuChannel);

        ADC_SET_BIT(Local_pstrADC->CR1, ADC_CR1_EOCIE_BIT);

		switch (Copy_enuUnit)
    {
        case ADC_UNIT_1:
        case ADC_UNIT_2:
            NVIC_voidEnableInterrupt(ADC_Au8IRQNumbers[Copy_enuUnit]);
            break;

        case ADC_UNIT_3:
            NVIC_voidEnableInterrupt(ADC_Au8IRQNumbers[Copy_enuUnit]);
            break;

        default:
            Local_enuErrorStatus = ADC_enuInvalidUnit;
            break;
    }

        ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_SWSTART_BIT);
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_SetCallback(ADC_enuUnit_t Copy_enuUnit,
                                     ADC_CallBack_t Copy_pvCallbackFunc)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;

    if (Copy_pvCallbackFunc == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else
    {
        ADC_ApfCallback[Copy_enuUnit] = Copy_pvCallbackFunc;
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_GetStatus(ADC_enuUnit_t Copy_enuUnit,
                                   ADC_enuState_t * Copy_penuState)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;

    if (Copy_penuState == 0)
    {
        Local_enuErrorStatus = ADC_enuNullPointer;
    }
    else if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else
    {
        *Copy_penuState = ADC_AenuState[Copy_enuUnit];
    }

    return Local_enuErrorStatus;
}


ADC_enuErrorStatus_t ADC_StopConversion(ADC_enuUnit_t Copy_enuUnit)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;

    if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        ADC_CLEAR_BIT(Local_pstrADC->CR1, ADC_CR1_EOCIE_BIT);
        ADC_AenuState[Copy_enuUnit] = ADC_STATE_IDLE;
    }

    return Local_enuErrorStatus;
}

ADC_enuErrorStatus_t ADC_SetPrescaler(ADC_enuPrescaler_t Copy_enuPrescaler)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;

    if (Copy_enuPrescaler > ADC_PRESCALER_DIV_8)
    {
        Local_enuErrorStatus = ADC_enuNOK;
    }
    else
    {
        ADC_WRITE_FIELD(MRCC->CFGR,
                        RCC_CFGR_ADCPRE_MASK,
                        RCC_CFGR_ADCPRE_START_BIT,
                        Copy_enuPrescaler);
    }

    return Local_enuErrorStatus;
}

ADC_enuErrorStatus_t ADC_SetDMAStatus(ADC_enuUnit_t Copy_enuUnit,
                                      u8 Copy_u8DMAStatus)
{
    ADC_enuErrorStatus_t Local_enuErrorStatus = ADC_enuOK;
    volatile ADC_strRegDef_t * Local_pstrADC = 0;

    if (ADC_u8IsValidUnit(Copy_enuUnit) == 0)
    {
        Local_enuErrorStatus = ADC_enuInvalidUnit;
    }
    else if ((Copy_u8DMAStatus != ADC_DMA_DISABLE) &&
             (Copy_u8DMAStatus != ADC_DMA_ENABLE))
    {
        Local_enuErrorStatus = ADC_enuInvalidConfig;
    }
    else
    {
        Local_pstrADC = ADC_ApstrUnits[Copy_enuUnit];

        if (Copy_u8DMAStatus == ADC_DMA_ENABLE)
        {
            ADC_SET_BIT(Local_pstrADC->CR2, ADC_CR2_DMA_BIT);
        }
        else
        {
            ADC_CLEAR_BIT(Local_pstrADC->CR2, ADC_CR2_DMA_BIT);
        }
    }

    return Local_enuErrorStatus;
}

/* =========================================================
 * ISR Handlers
 * ========================================================= */

void ADC1_2_IRQHandler(void)
{
    u16 Local_u16Result;

    if (ADC_GET_BIT(ADC1_REGS->SR, ADC_SR_EOC_BIT) == 1U)
    {
        Local_u16Result = (u16)(ADC1_REGS->DR & ADC_DATA_MASK);

        ADC_AenuState[ADC_UNIT_1] = ADC_STATE_IDLE;

        if (ADC_ApfCallback[ADC_UNIT_1] != 0)
        {
            ADC_ApfCallback[ADC_UNIT_1](Local_u16Result);
        }
    }

    if (ADC_GET_BIT(ADC2_REGS->SR, ADC_SR_EOC_BIT) == 1U)
    {
        Local_u16Result = (u16)(ADC2_REGS->DR & ADC_DATA_MASK);

        ADC_AenuState[ADC_UNIT_2] = ADC_STATE_IDLE;

        if (ADC_ApfCallback[ADC_UNIT_2] != 0)
        {
            ADC_ApfCallback[ADC_UNIT_2](Local_u16Result);
        }
    }
}


void ADC3_IRQHandler(void)
{
    u16 Local_u16Result;

    if (ADC_GET_BIT(ADC3_REGS->SR, ADC_SR_EOC_BIT) == 1U)
    {
        Local_u16Result = (u16)(ADC3_REGS->DR & ADC_DATA_MASK);

        ADC_AenuState[ADC_UNIT_3] = ADC_STATE_IDLE;

        if (ADC_ApfCallback[ADC_UNIT_3] != 0)
        {
            ADC_ApfCallback[ADC_UNIT_3](Local_u16Result);
        }
    }
}


/* =========================================================
 * Private Functions Implementation
 * ========================================================= */

static u8 ADC_u8IsValidUnit(ADC_enuUnit_t Copy_enuUnit)
{
    return (Copy_enuUnit < ADC_MAX_UNITS);
}


static u8 ADC_u8IsValidChannel(ADC_enuChannel_t Copy_enuChannel)
{
    return (Copy_enuChannel < ADC_MAX_CHANNELS);
}


static void ADC_vidSelectRegularChannel(volatile ADC_strRegDef_t * Copy_pstrADC,
                                        ADC_enuChannel_t Copy_enuChannel)
{
    /*
     * Single conversion:
     * First conversion in regular sequence = SQ1
     */

    ADC_WRITE_FIELD(Copy_pstrADC->SQR3,
                    ADC_FIVE_BITS_MASK,
                    ADC_SQR3_SQ1_START_BIT,
                    Copy_enuChannel);
}


static void ADC_vidSetSampleTime(volatile ADC_strRegDef_t * Copy_pstrADC,
                                 ADC_enuChannel_t Copy_enuChannel,
                                 u8 Copy_u8SampleTime)
{
    u8 Local_u8BitPosition;

    if (Copy_enuChannel <= ADC_CHANNEL_9)
    {
        Local_u8BitPosition = (u8)Copy_enuChannel * 3U;

        ADC_WRITE_FIELD(Copy_pstrADC->SMPR2,
                        ADC_THREE_BITS_MASK,
                        Local_u8BitPosition,
                        Copy_u8SampleTime);
    }
    else
    {
        Local_u8BitPosition = ((u8)Copy_enuChannel - 10U) * 3U;

        ADC_WRITE_FIELD(Copy_pstrADC->SMPR1,
                        ADC_THREE_BITS_MASK,
                        Local_u8BitPosition,
                        Copy_u8SampleTime);
    }
}
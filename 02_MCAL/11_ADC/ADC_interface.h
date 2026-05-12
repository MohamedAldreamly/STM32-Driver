/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/11/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


/* =========================================================
 * ADC Units
 * ========================================================= */

typedef enum
{
    ADC_UNIT_1 = 0,
    ADC_UNIT_2,
    ADC_UNIT_3
} ADC_enuUnit_t;


/* =========================================================
 * ADC Channels
 * ========================================================= */

typedef enum
{
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15,
    ADC_CHANNEL_16,
    ADC_CHANNEL_17
} ADC_enuChannel_t;


/* =========================================================
 * ADC Error Status
 * ========================================================= */

typedef enum
{
    ADC_enuOK = 0,
    ADC_enuNOK,
    ADC_enuNullPointer,
    ADC_enuInvalidUnit,
    ADC_enuInvalidChannel,
    ADC_enuInvalidConfig,
    ADC_enuBusy,
    ADC_enuTimeout
} ADC_enuErrorStatus_t;


/* =========================================================
 * ADC State
 * ========================================================= */

typedef enum
{
    ADC_STATE_IDLE = 0,
    ADC_STATE_BUSY
} ADC_enuState_t;


/* =========================================================
 * ADC Working Modes
 *
 * ADC_MODE_SINGLE_CONVERSION
 * ADC_INTERRUPT_EOC
 *
 * ========================================================= */

#define ADC_MODE_SINGLE_CONVERSION       0U
#define ADC_MODE_CONTINUOUS_CONVERSION   1U
#define ADC_MODE_SCAN_CONVERSION         2U
#define ADC_MODE_INJECTED_CONVERSION     3U
#define ADC_MODE_ANALOG_WATCHDOG         4U


/* =========================================================
 * ADC Interrupt Sources
 *
 * ========================================================= */

#define ADC_INTERRUPT_DISABLE            0U
#define ADC_INTERRUPT_EOC                1U
#define ADC_INTERRUPT_JEOC               2U
#define ADC_INTERRUPT_AWD                3U


/* =========================================================
 * ADC Conversion Trigger
 *
 * Software Start
 * ========================================================= */

#define ADC_TRIGGER_SOFTWARE             0U
#define ADC_TRIGGER_EXTERNAL             1U


/* =========================================================
 * ADC Data Alignment
 * ========================================================= */

#define ADC_ALIGN_RIGHT                  0U
#define ADC_ALIGN_LEFT                   1U


/* =========================================================
 * ADC Sample Time
 * ========================================================= */

#define ADC_SAMPLE_TIME_1_5_CYCLES       0U
#define ADC_SAMPLE_TIME_7_5_CYCLES       1U
#define ADC_SAMPLE_TIME_13_5_CYCLES      2U
#define ADC_SAMPLE_TIME_28_5_CYCLES      3U
#define ADC_SAMPLE_TIME_41_5_CYCLES      4U
#define ADC_SAMPLE_TIME_55_5_CYCLES      5U
#define ADC_SAMPLE_TIME_71_5_CYCLES      6U
#define ADC_SAMPLE_TIME_239_5_CYCLES     7U


/* =========================================================
 * ADC Enable / Disable Options
 * ========================================================= */

#define ADC_DISABLE                      0U
#define ADC_ENABLE                       1U


/* =========================================================
 * ADC Configuration Structure
 * ========================================================= */

typedef struct
{
    u8  Mode;
    u8  InterruptMode;
    u8  TriggerSource;
    u8  DataAlignment;
    u8  SampleTime;

} ADC_strConfig_t;

typedef enum
{
    ADC_PRESCALER_DIV_2 = 0,
    ADC_PRESCALER_DIV_4,
    ADC_PRESCALER_DIV_6,
    ADC_PRESCALER_DIV_8

} ADC_enuPrescaler_t;

#define RCC_CFGR_ADCPRE_START_BIT   14U
#define RCC_CFGR_ADCPRE_MASK        0x3U

#define ADC_DMA_DISABLE    0U
#define ADC_DMA_ENABLE     1U

/* =========================================================
 * ADC Callback Type
 * ========================================================= */

typedef void (*ADC_CallBack_t)(u16 u16Copy_u16Result);


/* =========================================================
 * ADC APIs
 * ========================================================= */

ADC_enuErrorStatus_t ADC_SetDMAStatus(ADC_enuUnit_t Copy_enuUnit,
                                      u8 Copy_u8DMAStatus);

ADC_enuErrorStatus_t ADC_SetPrescaler(ADC_enuPrescaler_t Copy_enuPrescaler);

ADC_enuErrorStatus_t ADC_Init(ADC_enuUnit_t Copy_enuUnit,
                              const ADC_strConfig_t * Copy_pstrConfig);

ADC_enuErrorStatus_t ADC_DeInit(ADC_enuUnit_t Copy_enuUnit);

ADC_enuErrorStatus_t ADC_StartConversion(ADC_enuUnit_t Copy_enuUnit,
                                         ADC_enuChannel_t Copy_enuChannel);

ADC_enuErrorStatus_t ADC_GetResultPolling(ADC_enuUnit_t Copy_enuUnit,
                                          u16 * Copy_pu16Result);

ADC_enuErrorStatus_t ADC_GetResult(ADC_enuUnit_t Copy_enuUnit,
                                   u16 * Copy_pu16Result);

ADC_enuErrorStatus_t ADC_StartConversionInterrupt(ADC_enuUnit_t Copy_enuUnit,
                                                  ADC_enuChannel_t Copy_enuChannel);

ADC_enuErrorStatus_t ADC_SetCallback(ADC_enuUnit_t Copy_enuUnit,
                                     ADC_CallBack_t Copy_pvCallbackFunc);

ADC_enuErrorStatus_t ADC_GetStatus(ADC_enuUnit_t Copy_enuUnit,
                                   ADC_enuState_t * Copy_penuState);

ADC_enuErrorStatus_t ADC_StopConversion(ADC_enuUnit_t Copy_enuUnit);

#endif /* ADC_INTERFACE_H */
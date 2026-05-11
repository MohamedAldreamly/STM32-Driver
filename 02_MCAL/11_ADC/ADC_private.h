/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    ADC_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/11/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


/* =========================================================
 * ADC Base Addresses - STM32F1
 * ========================================================= */

#define ADC1_BASE_ADDRESS        0x40012400UL
#define ADC2_BASE_ADDRESS        0x40012800UL
#define ADC3_BASE_ADDRESS        0x40013C00UL   /* Available only in some STM32F1 devices */


/* =========================================================
 * ADC Register Map
 * Register 32-bit
 * ========================================================= */

typedef struct
{
    volatile u32 SR;       /* Status Register flags EOC, STRT, AWD */
    volatile u32 CR1;      /* Control Register 1 interrupt, scan mode, watchdog */
    volatile u32 CR2;      /* Control Register 2 ADC, start conversion, alignment, DMA */
    volatile u32 SMPR1;    /* Sample Time Register 1 sample time CH 10-18 */
    volatile u32 SMPR2;    /* Sample Time Register 2 CH 0-9 */
    volatile u32 JOFR1;    /* Injected Channel Data Offset Register 1 */
    volatile u32 JOFR2;    /* Injected Channel Data Offset Register 2 */
    volatile u32 JOFR3;    /* Injected Channel Data Offset Register 3 */
    volatile u32 JOFR4;    /* Injected Channel Data Offset Register 4 */
    volatile u32 HTR;      /* Watchdog High Threshold Register */
    volatile u32 LTR;      /* Watchdog Low Threshold Register */

    volatile u32 SQR1;     /* Regular Sequence Register 1 CH 13-16 + L */
    volatile u32 SQR2;     /* Regular Sequence Register 2 CH 7-12 */
    volatile u32 SQR3;     /* Regular Sequence Register 3 CH 1-6 */

    volatile u32 JSQR;     /* Injected Sequence Register */
    volatile u32 JDR1;     /* Injected Data Register 1 */
    volatile u32 JDR2;     /* Injected Data Register 2 */
    volatile u32 JDR3;     /* Injected Data Register 3 */
    volatile u32 JDR4;     /* Injected Data Register 4 */

    volatile u32 DR;       /* Regular Data Register */

} ADC_strRegDef_t;


/* =========================================================
 * ADC Peripheral Pointers
 * ========================================================= */

#define ADC1_REGS       ((volatile ADC_strRegDef_t *)ADC1_BASE_ADDRESS)
#define ADC2_REGS       ((volatile ADC_strRegDef_t *)ADC2_BASE_ADDRESS)
#define ADC3_REGS       ((volatile ADC_strRegDef_t *)ADC3_BASE_ADDRESS)


/* =========================================================
 * ADC_SR Bits
 * ========================================================= */

#define ADC_SR_AWD_BIT          0U    /* Analog watchdog flag */
#define ADC_SR_EOC_BIT          1U    /* End of conversion flag */
#define ADC_SR_JEOC_BIT         2U    /* Injected channel end of conversion */
#define ADC_SR_JSTRT_BIT        3U    /* Injected conversion start flag */
#define ADC_SR_STRT_BIT         4U    /* Regular conversion start flag */


/* =========================================================
 * ADC_CR1 Bits
 * ========================================================= */

#define ADC_CR1_AWDCH_START_BIT     0U    /* Analog watchdog channel select start */
#define ADC_CR1_EOCIE_BIT           5U    /* End of conversion interrupt enable */
#define ADC_CR1_AWDIE_BIT           6U    /* Analog watchdog interrupt enable */
#define ADC_CR1_JEOCIE_BIT          7U    /* Injected EOC interrupt enable */
#define ADC_CR1_SCAN_BIT            8U    /* Scan mode enable */
#define ADC_CR1_AWDSGL_BIT          9U    /* Watchdog single channel enable */
#define ADC_CR1_JAUTO_BIT           10U   /* Automatic injected group conversion */
#define ADC_CR1_DISCEN_BIT          11U   /* Regular discontinuous mode enable */
#define ADC_CR1_JDISCEN_BIT         12U   /* Injected discontinuous mode enable */
#define ADC_CR1_DISCNUM_START_BIT   13U   /* Discontinuous mode channel count */
#define ADC_CR1_DUALMOD_START_BIT   16U   /* Dual ADC mode selection */
#define ADC_CR1_JAWDEN_BIT          22U   /* Analog watchdog enable injected */
#define ADC_CR1_AWDEN_BIT           23U   /* Analog watchdog enable regular */


/* =========================================================
 * ADC_CR2 Bits
 * ========================================================= */

#define ADC_CR2_ADON_BIT            0U    /* ADC enable / start conversion in some cases */
#define ADC_CR2_CONT_BIT            1U    /* Continuous conversion mode */
#define ADC_CR2_CAL_BIT             2U    /* Start calibration */
#define ADC_CR2_RSTCAL_BIT          3U    /* Reset calibration */
#define ADC_CR2_DMA_BIT             8U    /* DMA enable */
#define ADC_CR2_ALIGN_BIT           11U   /* Data alignment: 0 right, 1 left */
#define ADC_CR2_JEXTSEL_START_BIT   12U   /* Injected external trigger select */
#define ADC_CR2_JEXTTRIG_BIT        15U   /* Injected external trigger enable */
#define ADC_CR2_EXTSEL_START_BIT    17U   /* Regular external trigger select */
#define ADC_CR2_EXTTRIG_BIT         20U   /* Regular external trigger enable */
#define ADC_CR2_JSWSTART_BIT        21U   /* Start injected conversion by software */
#define ADC_CR2_SWSTART_BIT         22U   /* Start regular conversion by software */
#define ADC_CR2_TSVREFE_BIT         23U   /* Temperature sensor / VREFINT enable */


/* =========================================================
 * ADC_SMPR1 Channel Sample Time Bit Positions
 * Channels 10 -> 17
 * ========================================================= */

#define ADC_SMPR1_SMP10_START_BIT   0U
#define ADC_SMPR1_SMP11_START_BIT   3U
#define ADC_SMPR1_SMP12_START_BIT   6U
#define ADC_SMPR1_SMP13_START_BIT   9U
#define ADC_SMPR1_SMP14_START_BIT   12U
#define ADC_SMPR1_SMP15_START_BIT   15U
#define ADC_SMPR1_SMP16_START_BIT   18U
#define ADC_SMPR1_SMP17_START_BIT   21U


/* =========================================================
 * ADC_SMPR2 Channel Sample Time Bit Positions
 * Channels 0 -> 9
 * ========================================================= */

#define ADC_SMPR2_SMP0_START_BIT    0U
#define ADC_SMPR2_SMP1_START_BIT    3U
#define ADC_SMPR2_SMP2_START_BIT    6U
#define ADC_SMPR2_SMP3_START_BIT    9U
#define ADC_SMPR2_SMP4_START_BIT    12U
#define ADC_SMPR2_SMP5_START_BIT    15U
#define ADC_SMPR2_SMP6_START_BIT    18U
#define ADC_SMPR2_SMP7_START_BIT    21U
#define ADC_SMPR2_SMP8_START_BIT    24U
#define ADC_SMPR2_SMP9_START_BIT    27U


/* =========================================================
 * ADC_SQR1 Bits
 * ========================================================= */

#define ADC_SQR1_SQ13_START_BIT     0U
#define ADC_SQR1_SQ14_START_BIT     5U
#define ADC_SQR1_SQ15_START_BIT     10U
#define ADC_SQR1_SQ16_START_BIT     15U
#define ADC_SQR1_L_START_BIT        20U   /* Regular sequence length */


/* =========================================================
 * ADC_SQR2 Bits
 * ========================================================= */

#define ADC_SQR2_SQ7_START_BIT      0U
#define ADC_SQR2_SQ8_START_BIT      5U
#define ADC_SQR2_SQ9_START_BIT      10U
#define ADC_SQR2_SQ10_START_BIT     15U
#define ADC_SQR2_SQ11_START_BIT     20U
#define ADC_SQR2_SQ12_START_BIT     25U


/* =========================================================
 * ADC_SQR3 Bits
 * ========================================================= */

#define ADC_SQR3_SQ1_START_BIT      0U    /* First conversion in regular sequence */
#define ADC_SQR3_SQ2_START_BIT      5U
#define ADC_SQR3_SQ3_START_BIT      10U
#define ADC_SQR3_SQ4_START_BIT      15U
#define ADC_SQR3_SQ5_START_BIT      20U
#define ADC_SQR3_SQ6_START_BIT      25U


/* =========================================================
 * Useful Masks
 * ========================================================= */

#define ADC_ONE_BIT_MASK            1UL
#define ADC_THREE_BITS_MASK         0x7UL
#define ADC_FIVE_BITS_MASK          0x1FUL
#define ADC_FOUR_BITS_MASK          0xFUL
#define ADC_TWELVE_BITS_MASK        0xFFFUL

#define ADC_REGULAR_SEQUENCE_LEN_MASK   0xFUL
#define ADC_DATA_MASK                   0xFFFFUL


/* =========================================================
 * Sample Time Options
 * ========================================================= */

#define ADC_SAMPLE_1_5_CYCLES       0x0UL
#define ADC_SAMPLE_7_5_CYCLES       0x1UL
#define ADC_SAMPLE_13_5_CYCLES      0x2UL
#define ADC_SAMPLE_28_5_CYCLES      0x3UL
#define ADC_SAMPLE_41_5_CYCLES      0x4UL
#define ADC_SAMPLE_55_5_CYCLES      0x5UL
#define ADC_SAMPLE_71_5_CYCLES      0x6UL
#define ADC_SAMPLE_239_5_CYCLES     0x7UL


/* =========================================================
 * Alignment Options
 * ========================================================= */

#define ADC_RIGHT_ALIGNMENT         0U
#define ADC_LEFT_ALIGNMENT          1U


/* =========================================================
 * Regular Trigger Selection - EXTSEL[2:0]
 * Polling/Interrupt SWSTART
 * ========================================================= */

#define ADC_REGULAR_TRIGGER_TIMER1_CC1      0x0UL
#define ADC_REGULAR_TRIGGER_TIMER1_CC2      0x1UL
#define ADC_REGULAR_TRIGGER_TIMER1_CC3      0x2UL
#define ADC_REGULAR_TRIGGER_TIMER2_CC2      0x3UL
#define ADC_REGULAR_TRIGGER_TIMER3_TRGO     0x4UL
#define ADC_REGULAR_TRIGGER_TIMER4_CC4      0x5UL
#define ADC_REGULAR_TRIGGER_EXTI11          0x6UL
#define ADC_REGULAR_TRIGGER_SWSTART         0x7UL


/* =========================================================
 * Private Helper Macros
 * ========================================================= */

#define ADC_SET_BIT(REG, BIT)              ((REG) |=  (ADC_ONE_BIT_MASK << (BIT)))
#define ADC_CLEAR_BIT(REG, BIT)            ((REG) &= ~(ADC_ONE_BIT_MASK << (BIT)))
#define ADC_GET_BIT(REG, BIT)              (((REG) >> (BIT)) & ADC_ONE_BIT_MASK)

#define ADC_CLEAR_FIELD(REG, MASK, POS)     ((REG) &= ~((MASK) << (POS)))
#define ADC_WRITE_FIELD(REG, MASK, POS, VAL) \
    do                                      \
    {                                       \
        ADC_CLEAR_FIELD((REG), (MASK), (POS)); \
        (REG) |= (((VAL) & (MASK)) << (POS));  \
    } while (0)


/* =========================================================
 * ADC Private Constants
 * ========================================================= */

#define ADC_MAX_UNITS              3U
#define ADC_MAX_CHANNELS           18U
#define ADC_TIMEOUT_MAX            50000UL

#define ADC_REGULAR_SINGLE_CONVERSION_LENGTH   0U
/*  SQR1 L[3:0]  */

#endif /* ADC_PRIVATE_H */
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    AFIO_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/10/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 
 
#ifndef AFIO_PRIVATE_H_
#define AFIO_PRIVATE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* AFIO Base Address */
#define AFIO_BASE_ADDRESS        0x40010000UL


typedef struct
{
    volatile u32 EVCR;
    volatile u32 MAPR;
    volatile u32 EXTICR1;
    volatile u32 EXTICR2;
    volatile u32 EXTICR3;
    volatile u32 EXTICR4;
    volatile u32 MAPR2;

} AFIO_Type;


#define AFIO                    ((AFIO_Type *)AFIO_BASE_ADDRESS)


/* ===================================================== */
/*                  AFIO MAPR Bits                       */
/* ===================================================== */

#define AFIO_MAPR_SPI1_REMAP     0U     /* SPI1 remap */
#define AFIO_MAPR_I2C1_REMAP     1U     /* I2C1 remap */
#define AFIO_MAPR_USART1_REMAP   2U     /* USART1 remap */
#define AFIO_MAPR_USART2_REMAP   3U     /* USART2 remap */

#define AFIO_MAPR_USART3_REMAP   4U     /* USART3 remap start bit, 2 bits */
#define AFIO_MAPR_TIM1_REMAP     6U     /* TIM1 remap start bit, 2 bits */
#define AFIO_MAPR_TIM2_REMAP     8U     /* TIM2 remap start bit, 2 bits */
#define AFIO_MAPR_TIM3_REMAP     10U    /* TIM3 remap start bit, 2 bits */

#define AFIO_MAPR_TIM4_REMAP     12U    /* TIM4 remap */
#define AFIO_MAPR_CAN_REMAP      13U    /* CAN remap start bit, 2 bits */

#define AFIO_MAPR_PD01_REMAP     15U    /* PD0/PD1 remap */
#define AFIO_MAPR_TIM5CH4_IREMAP 16U    /* TIM5 channel 4 internal remap */
#define AFIO_MAPR_ADC1_ETRGINJ   17U    /* ADC1 injected external trigger remap */
#define AFIO_MAPR_ADC1_ETRGREG   18U    /* ADC1 regular external trigger remap */
#define AFIO_MAPR_ADC2_ETRGINJ   19U    /* ADC2 injected external trigger remap */
#define AFIO_MAPR_ADC2_ETRGREG   20U    /* ADC2 regular external trigger remap */

#define AFIO_MAPR_SWJ_CFG        24U    /* JTAG/SWD configuration start bit, 3 bits */


/* ===================================================== */
/*                  AFIO MAPR Masks                      */
/* ===================================================== */

#define AFIO_MAPR_TIM2_REMAP_MASK     (0x3U << AFIO_MAPR_TIM2_REMAP)
#define AFIO_MAPR_TIM3_REMAP_MASK     (0x3U << AFIO_MAPR_TIM3_REMAP)
#define AFIO_MAPR_TIM4_REMAP_MASK     (1U   << AFIO_MAPR_TIM4_REMAP)

#define AFIO_MAPR_SWJ_CFG_MASK        (0x7U << AFIO_MAPR_SWJ_CFG)


/* ===================================================== */
/*              AFIO Remap Values                        */
/* ===================================================== */

/* TIM2 remap values */
#define AFIO_TIM2_REMAP_NONE          0x0U
#define AFIO_TIM2_REMAP_PARTIAL_1     0x1U
#define AFIO_TIM2_REMAP_PARTIAL_2     0x2U
#define AFIO_TIM2_REMAP_FULL          0x3U

/* TIM3 remap values */
#define AFIO_TIM3_REMAP_NONE          0x0U
#define AFIO_TIM3_REMAP_PARTIAL       0x2U
#define AFIO_TIM3_REMAP_FULL          0x3U

/* TIM4 remap values */
#define AFIO_TIM4_REMAP_NONE          0x0U
#define AFIO_TIM4_REMAP_FULL          0x1U


#endif
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/10/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

#include "BIT_MATH.h"

/* ================= CR1 Register ================= */

/* Counter Enable */
#define TIM_CR1_CEN              0U

/* Auto Reload Preload Enable */
#define TIM_CR1_ARPE             7U

// /* TIMx_CR1 Bits */

// #define TIM_CR1_CEN      (1U << 0)   // Counter enable
// #define TIM_CR1_UDIS     (1U << 1)   // Disable update events
// #define TIM_CR1_URS      (1U << 2)   // Update request source selection
// #define TIM_CR1_OPM      (1U << 3)   // One pulse mode (stop after one update)
// #define TIM_CR1_DIR      (1U << 4)   // Counter direction (up/down)

// #define TIM_CR1_CMS_0    (1U << 5)   // Center-aligned mode selection bit 0
// #define TIM_CR1_CMS_1    (1U << 6)   // Center-aligned mode selection bit 1

// #define TIM_CR1_ARPE     (1U << 7)   // Auto-reload preload enable

// #define TIM_CR1_CKD_0    (1U << 8)   // Clock division bit 0
// #define TIM_CR1_CKD_1    (1U << 9)   // Clock division bit 1

// /* TIMx_CR2 Bits */

// #define TIM_CR2_CCDS        (1U << 3)   // Capture/Compare DMA selection

// #define TIM_CR2_MMS_0       (1U << 4)   // Master mode selection bit 0
// #define TIM_CR2_MMS_1       (1U << 5)   // Master mode selection bit 1
// #define TIM_CR2_MMS_2       (1U << 6)   // Master mode selection bit 2

// #define TIM_CR2_TI1S        (1U << 7)   // TI1 input selection

/* ================= EGR Register ================= */

/* Update Generation update event */

#define TIM_EGR_UG               0U

/* ================= SR Register ================= */

/* Update Interrupt Flag */
#define TIM_SR_UIF               0U

/* Capture/Compare 1 Interrupt Flag */
#define TIM_SR_CC1IF             1U

/* Capture/Compare 2 Interrupt Flag */
#define TIM_SR_CC2IF             2U

/* Capture/Compare 3 Interrupt Flag */
#define TIM_SR_CC3IF             3U

/* Capture/Compare 4 Interrupt Flag */
#define TIM_SR_CC4IF            4U


/* ================= DIER Register ================= */

/* Update Interrupt Enable */
#define TIM_DIER_UIE             0U

/* Capture/Compare 1 Interrupt Enable */
#define TIM_DIER_CC1IE           1U

/* Capture/Compare 2 Interrupt Enable */
#define TIM_DIER_CC2IE           2U

/* Capture/Compare 3 Interrupt Enable */
#define TIM_DIER_CC3IE           3U

/* Capture/Compare 4 Interrupt Enable */
#define TIM_DIER_CC4IE           4U


/* ===================================================== */
/*                     CCMR1 Masks                       */
/* ===================================================== */

/* Channel 1 Output Compare Mode bits */
#define TIM_CCMR1_OC1M           4U

/* Channel 1 Output Compare Preload Enable */

// OC1FE -> Fast enable
// Faster response to trigger

// OC1CE -> Clear enable
// Clear output on ETRF HIGH

// OC1PE -> CCR1 preload enable
// 0: Immediate update
// 1: Update on Update Event


#define TIM_CCMR1_OC1PE          3U

#define TIM_CCMR1_CC1S_MASK            (0x3U << TIM_CCMR1_CC1S)  /* Mask for CH1 selection bits */
#define TIM_CCMR1_OC1M_MASK            (0x7U << TIM_CCMR1_OC1M)  /* Mask for CH1 output compare mode */

/* Channel 2 Output Compare Mode bits */
#define TIM_CCMR1_OC2M           12U

/* Channel 2 Output Compare Preload Enable */
#define TIM_CCMR1_OC2PE          11U

#define TIM_CCMR1_CC2S_MASK            (0x3U << TIM_CCMR1_CC2S)  /* Mask for CH2 selection bits */
#define TIM_CCMR1_OC2M_MASK            (0x7U << TIM_CCMR1_OC2M)  /* Mask for CH2 output compare mode */



/* ===================================================== */
/*                     CCMR2 Masks                       */
/* ===================================================== */

/* Channel 3 Output Compare Mode bits */
#define TIM_CCMR2_OC3M           4U

/* Channel 3 Output Compare Preload Enable */
#define TIM_CCMR2_OC3PE          3U

#define TIM_CCMR2_CC3S_MASK            (0x3U << TIM_CCMR2_CC3S)  /* Mask for CH3 selection bits */
#define TIM_CCMR2_OC3M_MASK            (0x7U << TIM_CCMR2_OC3M)  /* Mask for CH3 output compare mode */

/* Channel 4 Output Compare Mode bits */
#define TIM_CCMR2_OC4M           12U

/* Channel 4 Output Compare Preload Enable */
#define TIM_CCMR2_OC4PE          11U

#define TIM_CCMR2_CC4S_MASK            (0x3U << TIM_CCMR2_CC4S)  /* Mask for CH4 selection bits */
#define TIM_CCMR2_OC4M_MASK            (0x7U << TIM_CCMR2_OC4M)  /* Mask for CH4 output compare mode */

/* ================= CCER Register ================= */

// CC1P -> Output polarity
// 0: Active HIGH
// 1: Active LOW

/* Capture/Compare 1 Output Enable */
#define TIM_CCER_CC1E            0U

/* Capture/Compare 2 Output Enable */
#define TIM_CCER_CC2E            4U

/* Capture/Compare 3 Output Enable */
#define TIM_CCER_CC3E            8U

/* Capture/Compare 4 Output Enable */
#define TIM_CCER_CC4E            12U

typedef struct
{
    volatile u32 CR1;      /* Control Register 1              */
    volatile u32 CR2;      /* Control Register 2              */
    volatile u32 SMCR;     /* Slave Mode Control Register     */
    volatile u32 DIER;     /* DMA/Interrupt Enable Register   */
    volatile u32 SR;       /* Status Register                 */
    volatile u32 EGR;      /* Event Generation Register       */
    volatile u32 CCMR1;    /* Capture/Compare Mode Register 1 */
    volatile u32 CCMR2;    /* Capture/Compare Mode Register 2 */
    volatile u32 CCER;     /* Capture/Compare Enable Register */
    volatile u32 CNT;      /* Counter Register                */
    volatile u32 PSC;      /* Prescaler Register              */
    volatile u32 ARR;      /* Auto-Reload Register            */
    volatile u32 RCR;      /* Repetition Counter Register     */
    volatile u32 CCR1;     /* Capture/Compare Register 1      */
    volatile u32 CCR2;     /* Capture/Compare Register 2      */
    volatile u32 CCR3;     /* Capture/Compare Register 3      */
    volatile u32 CCR4;     /* Capture/Compare Register 4      */
    volatile u32 BDTR;     /* Break and Dead-Time Register    */
    volatile u32 DCR;      /* DMA Control Register            */
    volatile u32 DMAR;     /* DMA Address for Full Transfer   */

} TIM_Type;

#define TIM1_BASE_ADDRESS      0x40012C00UL
#define TIM2_BASE_ADDRESS      0x40000000UL
#define TIM3_BASE_ADDRESS      0x40000400UL
#define TIM4_BASE_ADDRESS      0x40000800UL
#define TIM5_BASE_ADDRESS      0x40000C00UL
#define TIM6_BASE_ADDRESS      0x40001000UL
#define TIM7_BASE_ADDRESS      0x40001400UL

#define TIM1    ((TIM_Type *)TIM1_BASE_ADDRESS)
#define TIM2    ((TIM_Type *)TIM2_BASE_ADDRESS)
#define TIM3    ((TIM_Type *)TIM3_BASE_ADDRESS)
#define TIM4    ((TIM_Type *)TIM4_BASE_ADDRESS)
#define TIM5    ((TIM_Type *)TIM5_BASE_ADDRESS)
#define TIM6    ((TIM_Type *)TIM6_BASE_ADDRESS)
#define TIM7    ((TIM_Type *)TIM7_BASE_ADDRESS)



// #define     MSTK_SRC_AHB           0
// #define     MSTK_SRC_AHB_8         1

// #define     MSTK_SINGLE_INTERVAL    0
// #define     MSTK_PERIOD_INTERVAL    1


#endif

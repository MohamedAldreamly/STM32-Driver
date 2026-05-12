/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    DMA_private.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/11/2026
 *  Vertion : V01
 *  Layer   : MCAL
 *
 */ 

#ifndef ADC_DMA_PRIVATE_H
#define ADC_DMA_PRIVATE_H


/* DMA1 Base Address */
#define DMA1_BASE_ADDRESS        0x40020000UL

typedef struct
{
    volatile u32 CCR;
    volatile u32 CNDTR;
    volatile u32 CPAR;
    volatile u32 CMAR;

} DMA_Channel_t;

typedef struct
{
    volatile u32 ISR;
    volatile u32 IFCR;
    DMA_Channel_t Channel[7];

} DMA_t;

#define DMA1        ((volatile DMA_t *)DMA1_BASE_ADDRESS)

/* ADC1 Data Register Address */
#define ADC1_DR_ADDRESS          0x4001244CUL

/* DMA1 Channel 1 index */
#define DMA_CHANNEL_1_INDEX      0U

/* DMA CCR Bits */
#define DMA_CCR_EN_BIT           0U
#define DMA_CCR_TCIE_BIT         1U
#define DMA_CCR_HTIE_BIT         2U
#define DMA_CCR_TEIE_BIT         3U
#define DMA_CCR_DIR_BIT          4U
#define DMA_CCR_CIRC_BIT         5U
#define DMA_CCR_PINC_BIT         6U
#define DMA_CCR_MINC_BIT         7U
#define DMA_CCR_PSIZE_START_BIT  8U
#define DMA_CCR_MSIZE_START_BIT  10U
#define DMA_CCR_PL_START_BIT     12U
#define DMA_CCR_MEM2MEM_BIT      14U

/* DMA ISR Flags for Channel 1 */
#define DMA_ISR_GIF1_BIT         0U
#define DMA_ISR_TCIF1_BIT        1U
#define DMA_ISR_HTIF1_BIT        2U
#define DMA_ISR_TEIF1_BIT        3U

/* DMA IFCR Flags for Channel 1 */
#define DMA_IFCR_CGIF1_BIT       0U
#define DMA_IFCR_CTCIF1_BIT      1U
#define DMA_IFCR_CHTIF1_BIT      2U
#define DMA_IFCR_CTEIF1_BIT      3U

/* Field Values */
#define DMA_SIZE_8_BIT           0U
#define DMA_SIZE_16_BIT          1U
#define DMA_SIZE_32_BIT          2U

#define DMA_PRIORITY_LOW         0U
#define DMA_PRIORITY_MEDIUM      1U
#define DMA_PRIORITY_HIGH        2U
#define DMA_PRIORITY_VERY_HIGH   3U

#define DMA_ONE_BIT_MASK         1UL
#define DMA_TWO_BITS_MASK        0x3UL

#define DMA_SET_BIT(REG, BIT)      ((REG) |=  (DMA_ONE_BIT_MASK << (BIT)))
#define DMA_CLEAR_BIT(REG, BIT)    ((REG) &= ~(DMA_ONE_BIT_MASK << (BIT)))
#define DMA_GET_BIT(REG, BIT)      (((REG) >> (BIT)) & DMA_ONE_BIT_MASK)

#define DMA_WRITE_FIELD(REG, MASK, POS, VAL) \
do                                            \
{                                             \
    (REG) &= ~((MASK) << (POS));              \
    (REG) |= (((VAL) & (MASK)) << (POS));     \
} while (0)

#endif
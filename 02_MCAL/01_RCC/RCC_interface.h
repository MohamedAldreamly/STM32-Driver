/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author  : Mohamed Aldreamly
 *  Date    : 5/7/2026
 *  Vertion : V01
 *  Layer   : MCAL
 * 
 */ 

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

//==============================================================================================================

#define RCC_HSI         0
#define RCC_HSE         1
#define RCC_PLL         2
#define RCC_HSE_BYPASS  3

#define RCC_PLL_HSI_DIVIDED_BY_2  0
#define RCC_PLL_HSE               1
#define RCC_PLL_HSE_DIVIDED_BY_2  2

#define ENABLE_PERIPHERAL     1
#define DISABLE_PERIPHERAL    0
#define RESET_PERIPHERAL      2

//==============================================================================================================

//RCC_CR Register Bits
#define RCC_HSION                        0
#define RCC_HSIRDY                       1
#define RCC_HSEON                        16
#define RCC_HSERDY                       17
#define RCC_HSEBYP                       18
#define RCC_CSSON                        19
#define RCC_PLLON                        24
#define RCC_PLLRDY                       25 

/*******************************************************************/
/*                                                                 */
/*                       ClockType Maybe :                         */
/*                       1-HSI                                     */
/*                       2-HSE                                     */
/*                       3-PLL                                     */
/*                           3.1-PLL_HSI_DIVIDED_BY_2              */
/*                           3.2-PLL_HSE                           */
/*                           3.3-PLL_HSE_DIVIDED_BY_2              */
/*                       4-HSE_BYPASS                              */
/*                                                                 */
/*******************************************************************/

#define RCC_SW_POSITION  0
#define RCC_SWS_POSITION 2
#define RCC_HPRE_POSITION 4
#define RCC_PPRES1_POSITION 8
#define RCC_PPRES2_POSITION 11
#define RCC_ADCPRE_POSITION 14
#define RCC_PLLSRC_POSITION 16
#define RCC_PLLXTPRE_POSITION 17
#define RCC_PLLMUL_POSITION 18



#define RCC_SW_HSI   0b00
#define RCC_SW_HSE   0b01
#define RCC_SW_PLL   0b10


//==============================================================================================================

/********************************************************************************************/
/*                                                                                    */
/*                        ClockFactor For APB1,2 prescaler  Maybe :                      */
/*                              1-HCLK not divided                                   */
/*                              2-HCLK divided by 2                                   */
/*                              3-HCLK divided by 7                                   */
/*                              4-HCLK divided by 8                                  */ 
/*                              4-HCLK divided by 16                                  */
/*                                                                                    */
/*                                                                                    */
/********************************************************************************************/

#define HCLK_NOT_DIVIDED                         0b000
#define HCLK_DIVIDED_BY_2                        0b100
#define HCLK_DIVIDED_BY_4					     0b101
#define HCLK_DIVIDED_BY_8                        0b110
#define HCLK_DIVIDED_BY_16                       0b111


//==============================================================================================================


/********************************************************************************************/
/*                                                                                    */
/*                        ClockFactor For AHB prescaler  Maybe :                      */
/*                              1-SYSCLK not divided                                   */
/*                              2-SYSCLK divided by 2                                   */
/*                              3-SYSCLK divided by 7                                   */
/*                              4-SYSCLK divided by 8                                  */ 
/*                              5-SYSCLK divided by 16                                  */
/*                              6-SYSCLK divided by 64                                    */
/*                              7-SYSCLK divided by 128                                   */
/*                              8-SYSCLK divided by 256                                   */
/*                              9-SYSCLK divided by 512                                  */
/********************************************************************************************/

#define SYSCLK_NOT_DIVIDED          0b0000
#define SYSCLK_DIVIDED_BY_2         0b1000
#define SYSCLK_DIVIDED_BY_4			0b1001
#define SYSCLK_DIVIDED_BY_8         0b1010
#define SYSCLK_DIVIDED_BY_16        0b1011
#define SYSCLK_DIVIDED_BY_64        0b1100
#define SYSCLK_DIVIDED_BY_128		0b1101
#define SYSCLK_DIVIDED_BY_256       0b1110
#define SYSCLK_DIVIDED_BY_512       0b1111


//==============================================================================================================

/********************************************************************************************/
/*                                                                                          */
/*                             ClockFactor For PLL  Maybe :                                 */
/*                              1-PLL_CLOCKk_MULTIPLE_BY_2                                   */
/*                              2-PLL_CLOCKk_MULTIPLE_BY_3                                   */
/*                              3-PLL_CLOCKk_MULTIPLE_BY_4                                   */
/*                              4-PLL_CLOCKk_MULTIPLE_BY_5                                   */
/*                              5-PLL_CLOCKk_MULTIPLE_BY_6                                   */
/*                              6-PLL_CLOCKk_MULTIPLE_BY_7                                   */
/*                              7-PLL_CLOCKk_MULTIPLE_BY_8                                   */
/*                              8-PLL_CLOCKk_MULTIPLE_BY_9                                   */
/*                              9-PLL_CLOCKk_MULTIPLE_BY_10                                  */
/*                              10-PLL_CLOCKk_MULTIPLE_BY_11                                 */
/*                              11-PLL_CLOCKk_MULTIPLE_BY_12                                 */
/*                              12-PLL_CLOCKk_MULTIPLE_BY_13                                 */
/*                              13-PLL_CLOCKk_MULTIPLE_BY_14                                 */
/*                              14-PLL_CLOCKk_MULTIPLE_BY_15                                 */
/*                              15-PLL_CLOCKk_MULTIPLE_BY_16                                 */
/*                                                                                          */
/********************************************************************************************/

#define NO_CLOCK_FACTOR                                0b0000
#define PLL_CLOCK_MULTIPLE_BY_2                        0b0000
#define PLL_CLOCK_MULTIPLE_BY_3					       0b0001
#define PLL_CLOCK_MULTIPLE_BY_4                        0b0010
#define PLL_CLOCK_MULTIPLE_BY_5                        0b0011
#define PLL_CLOCK_MULTIPLE_BY_6                        0b0100
#define PLL_CLOCK_MULTIPLE_BY_7                        0b0101
#define PLL_CLOCK_MULTIPLE_BY_8                        0b0110
#define PLL_CLOCK_MULTIPLE_BY_9                        0b0111
#define PLL_CLOCK_MULTIPLE_BY_10                       0b1000
#define PLL_CLOCK_MULTIPLE_BY_11                       0b1001
#define PLL_CLOCK_MULTIPLE_BY_12                       0b1010
#define PLL_CLOCK_MULTIPLE_BY_13                       0b1011
#define PLL_CLOCK_MULTIPLE_BY_14                       0b1100
#define PLL_CLOCK_MULTIPLE_BY_15                       0b1101
#define PLL_CLOCK_MULTIPLE_BY_16                       0b1110

//==============================================================================================================


/**********************************************************************/
/*                                                                    */
/*                 Clock Security System May be                       */
/*                 1-Enable:                                          */
/* 				   To Set HSI By H.W When There are Failure In HSE    */
/* 				   To Set HSI By H.W When Leaving Stop Or Standby     */
/* 				   2-Disable                                          */
/* 				   The Previouse To Feature Doesnot Happen            */
/*                                                                    */
/**********************************************************************/

#define DISABLE_CLOCK_SECURITY_SYSTEM              0
#define ENABLE_CLOCK_SECURITY_SYSTEM               1

//==============================================================================================================

/**********************************************************************/
/*                                                                    */
/*                 Peripheral Clock Enable For AHB Bus                */
/*                              0-DMA1                                */
/*                              1-DMA2                                */
/*                              2-SRAM                                */
/*                              3-RESERVED                            */
/*                              4-FLITF                               */
/*                              5-RESERVED                            */
/*                              6-CRC                                 */
/*                              7-RESERVED                            */
/*                              8-FSMC                                */
/*                              9-RESERVED                            */
/*                              10-SDIO                               */
/*                                                                    */
/**********************************************************************/



#define    DMA1_RCC         0
#define    DMA2_RCC         1
#define    SRAM_RCC         2
#define    FLITF_RCC        4
#define    CRC_RCC          6
#define    FSMC_RCC         8
#define    SDIO_RCC         10

//==============================================================================================================



/**********************************************************************/
/*                                                                    */
/*                 Peripheral Clock Enable For APB2 Bus               */
/*                              0-AFIO                                */
/*                              1-RESERVED                            */
/*                              2-DIOA                               */
/*                              3-DIOB                               */
/*                              4-DIOC                               */
/*                              5-DIOD                               */
/*                              6-DIOE                               */
/*                              7-DIOF                               */
/*                              8-DIOG                               */
/*                              9-ADC1                                */
/*                              10-ADC2                               */
/*                              11-TIM1                               */
/*                              12-SPI1                               */
/*                              13-TIM8                               */
/*                              14-USART1                             */
/*                              15-ADC3                               */
/*                              16-RESERVED                           */
/*                              17-RESERVED                           */
/*                              18-RESERVED                           */
/*                              19-TIM9                               */
/*                              20-TIM10                              */
/*                              21-TIM11                              */
/*                                                                    */
/**********************************************************************/




#define    AFIO_RCC         0
#define    DIOA_RCC         2
#define    DIOB_RCC         3
#define    DIOC_RCC         4
#define    DIOD_RCC         5
#define    DIOE_RCC         6
#define    DIOF_RCC         7
#define    DIOG_RCC         8
#define    ADC1_RCC         9
#define    ADC2_RCC         10
#define    TIM1_RCC         11
#define    SPI1_RCC         12
#define    TIM8_RCC         13
#define    USART1_RCC       14
#define    ADC3_RCC         15
#define    TIM9_RCC         19
#define    TIM10_RCC        20
#define    TIM11_RCC        21

//==============================================================================================================


/**********************************************************************/
/*                                                                    */
/*                 Peripheral Clock Enable For APB1 Bus               */
/*                              0-TIM2                                */
/*                              1-TIM3                                */
/*                              2-TIM4                                */
/*                              3-TIM5                                */
/*                              4-TIM6                                */
/*                              5-TIM7                                */
/*                              6-TIM12                               */
/*                              7-TIM13                               */
/*                              8-TIM14                               */
/*                              9-RESERVED                            */
/*                              10-RESERVED                           */
/*                              11-WWDG                               */
/*                              12-RESERVED                           */
/*                              13-RESERVED                           */
/*                              14-SPI2                               */
/*                              15-SPI3                               */
/*                              16-RESERVED                           */
/*                              17-USART2                             */
/*                              18-USART3                             */
/*                              19-UART4                              */
/*                              20-UART5                              */
/*                              21-I2C1                               */
/*                              22-I2C2                               */
/*                              23-USB                                */
/*                              24-RESERVED                           */
/*                              25-CAN                                */
/*                              26-RESERVED                           */
/*                              27-BKP                                */
/*                              28-PWR                                */
/*                              29-DAC                                */
/*                                                                    */
/**********************************************************************/




#define    TIM2_RCC         0
#define    TIM3_RCC         1
#define    TIM4_RCC         2
#define    TIM5_RCC         3
#define    TIM6_RCC         4
#define    TIM7_RCC         5
#define    TIM12_RCC        6
#define    TIM13_RCC        7
#define    TIM14_RCC        8
#define    WWDG_RCC         11
#define    SPI2_RCC         14
#define    SPI3_RCC         15
#define    USART2_RCC       17
#define    USART3_RCC       18
#define    UART4_RCC        19
#define    UART5_RCC        20
#define    I2C1_RCC         21
#define    I2C2_RCC         22
#define    USB_RCC          23
#define    CAN_RCC          25
#define    BKP_RCC          27
#define    PWR_RCC          28
#define    DAC_RCC          29

//==============================================================================================================


#define    AHB_BUS       0
#define    APB1_BUS      1
#define    APB2_BUS      2

//==============================================================================================================
#define SYSCFG_EN       14


void RCC_voidInitSysClock( void );

void RCC_voidEnablePeripheralClock( u8 Copy_u8BusId , u8 Copy_u8PeripheralId );
void RCC_voidDisablePeripheralClock ( u8 Copy_u8BusId  , u8 Copy_u8PeripheralId );
void RCC_voidResetPeripheralClock(u8 Copy_u8BusId, u8 Copy_u8PeripheralId);

void RCC_voidEnableSYSCFGClock(void);
//==============================================================================================================

#endif /* RCC_INTERFACE_H_ */

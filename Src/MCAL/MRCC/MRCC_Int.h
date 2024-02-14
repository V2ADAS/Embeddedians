/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                   */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/* Description       : RCC_Prog.c --> implementations                                                  */
/* Module  Features  :                                                                                 */
/*      01- void MRCC_vInit(void);                                                                     */
/*      02- void MRCC_vEnableClock(PeripheralEnable_t Copy_u8PeripheralNo);                            */
/*      03- void MRCC_vDisableClock(PeripheralEnable_t Copy_u8PeripheralNo);                           */                                                                       
/*******************************************************************************************************/

    
/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MRCC_MRCC_INT_H_
#define MCAL_MRCC_MRCC_INT_H_


typedef enum {
    /* AHB1 */
    GPIOA_EN = 0,
    GPIOB_EN,
    GPIOC_EN,
    CRC_EN = 12,
    DMA1_EN = 21,
    DMA2_EN,

    /* AHB2 */
    OTGFS_EN = (7 + 32),
    /* APB1 */
    TIM2_EN = (0 + 64),
    TIM3_EN,
    TIM4_EN,
    TIM5_EN,
    WWDG_EN = (11 + 64),
    SPI2_EN = (14 + 64),
    SPI3_EN,
    USART2_EN = (17 + 64),
    I2C1_EN = (21 + 64),
    I2C2_EN,
    I2C3_EN,
    PWR_EN = (28 + 64),

    /* APB2 */
    TIM1_EN = (0 + 96),
    USART1_EN = (4 + 96),
    USART6_EN,
    ADC1_EN = (8 + 96),
    SPI1_EN = (12 + 96),
    SPI4_EN,
    SYSCFG_EN,
    TIM9_EN = (16 + 96),
    TIM10_EN,
    TIM11_EN
} PeripheralEnable_t;
/******************************************************************************************************/
/*                                      01- MRCC_vInit                                                */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Initializing RCC                                               */
/* 2- Function Input       -> void                                                                    */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MRCC_vInit(void);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      02- MRCC_vEnableClock                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Enable Clock for a certain peripheral                           */
/* 2- Function Input       -> @param Copy_u8PeripheralNo = Number of peripheral from enum PeripheralEnable_t */                                                                                    
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MRCC_vEnableClock(PeripheralEnable_t Copy_u8PeripheralNo);
/*************************************************************************************************************/

/******************************************************************************************************/
/*                                      03- MRCC_vDisableClock                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Disable Clock for a certain peripheral                           */
/* 2- Function Input       -> @param Copy_u8PeripheralNo = Number of peripheral from enum PeripheralEnable_t */                                                                                 
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MRCC_vDisableClock(PeripheralEnable_t Copy_u8PeripheralNo);
/*************************************************************************************************************/


#endif /* MCAL_MRCC_MRCC_INT_H_ */

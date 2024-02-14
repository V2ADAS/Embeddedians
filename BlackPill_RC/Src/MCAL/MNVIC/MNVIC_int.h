/*
 * MNVIC_int.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Omar
 */

#ifndef MCAL_MNVIC_MNVIC_INT_H_
#define MCAL_MNVIC_MNVIC_INT_H_

/*typedef enum {

	WWDG,
	EXTI16,
	EXTI

} Enum_IntNames_t;*/

typedef enum {

	GP16SUB0=3,
	GP8SUB2,
	GP4SUB4,
	GP2SUB8,
	GP0SUB16
} MNVIC_Priority_GP;


typedef enum{
	NVIC_WWDG=0,
	NVIC_EXTI16,
	NVIC_EXTI21,
	NVIC_EXTI22,
	NVIC_FLASH,
	NVIC_RCC,
	NVIC_EXTI0,
	NVIC_EXTI1,
	NVIC_EXTI2,
	NVIC_EXTI3,
	NVIC_EXTI4,
	NVIC_DMA1_Stream0,
	NVIC_DMA1_Stream1,
	NVIC_DMA1_Stream2,
	NVIC_DMA1_Stream3, //14
	NVIC_DMA1_Stream4,
	NVIC_DMA1_Stream5,
	NVIC_DMA1_Stream6,
	NVIC_ADC,
	NVIC_EXTI9_5 = 23,
	NVIC_TIM1_BRK_TIM9,
	NVIC_TIM1_UP_TIM10,
	NVIC_TIM1_TRG_COM_TIM11,
	NVIC_TIM1_CC,
	NVIC_TIM2,
	NVIC_TIM3,
	NVIC_TIM4,
	NVIC_I2C1_EV,
	NVIC_I2C1_ER,
	NVIC_I2C2_EV,
	NVIC_I2C2_ER,
	NVIC_SPI1,
	NVIC_SPI2,
	NVIC_USART1,
	NVIC_USART2,
	NVIC_EXTI15_10 = 40,
	NVIC_EXTI17,
	NVIC_EXTI18,
	NVIC_DMA1_Stream7 =47,
	NVIC_SDIO =49,
	NVIC_TIM5,
	NVIC_SPI3,
	NVIC_DMA2_Stream0 =56,
	NVIC_DMA2_Stream1,
	NVIC_DMA2_Stream2,
	NVIC_DMA2_Stream3,
	NVIC_DMA2_Stream4,
	NVIC_OTG_FS =67,
	NVIC_DMA2_Stream5,
	NVIC_DMA2_Stream6,
	NVIC_DMA2_Stream7,
	NVIC_USART6,
	NVIC_I2C3_EV,
	NVIC_I2C3_ER,
	NVIC_FPU =81,
	NVIC_SPI4 =84,
}Enum_MNVIC_NUM_t;

typedef enum {

	GP0,GP1,GP2,GP3,GP4,GP5,GP6,GP7,GP8,GP9,GP10,GP11,GP12,GP13,GP14,GP15
} MNVIC_GP_Options;

typedef enum {

	SUB0,SUB1,SUB2,SUB3,SUB4,SUB5,SUB6,SUB7,SUB8,SUB9,SUB10,SUB11,SUB12,SUB13,SUB14,SUB15

} MNVIC_SUB_Options ;



void MNVIC_vEnableInterrupt(u8 Copy_u8InterruptNo);

void MNVIC_vDisableInterrupt(u8 Copy_u8InterruptNo);

void MNVIC_vSetPendingFlag (u8 Copy_u8InterruptNo);

void MNVIC_vClearPendingFlag (u8 Copy_u8InterruptNo);

u8 MNVIC_u8ReadActiveFlag( u8 Copy_u8InterruptNo );

void MNVIC_vInitGrouping(MNVIC_Priority_GP Copy_u8Grouping);

void MNVIC_vSetIntPriority( u8 Copy_u8InterruptNo , MNVIC_GP_Options Copy_u8GP , MNVIC_SUB_Options Copy_u8SUB );

void MNVIC_vTrigSoftwareInt( u8 Copy_u8InterruptNo );

#endif /* MCAL_MNVIC_MNVIC_INT_H_ */

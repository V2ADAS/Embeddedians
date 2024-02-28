/*******************************************************************************************************/
/* Author            : Omar Wael                                                                       */
/* Version           : V0.0.0                                                                          */
/* Date              : 31 Oct 2023                                                                     */
/* Description       : MNVIC_int.h --> Functions Definitions                                           */
/* Module  Features  :                                                                                 */
/*      01- MNVIC_EnableInterrupt                                                                      */
/*      02- MNVIC_DisableInterrupt                                                                     */
/*      03- MNVIC_SetPendingFlag                                                                       */
/*      04- MNVIC_ClearPendingFlag                                                                     */
/*      05- MNVIC_ReadActiveFlag                                                                       */
/*      06- MNVIC_InitGrouping                                                                         */
/*      07- MNVIC_SetIntPriority                        											   */
/*      08- MNVIC_TrigSoftwareInt																	   */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                 						 File Guard Will Call On Time in .c File                       */
/*******************************************************************************************************/

#ifndef MCAL_MNVIC_MNVIC_INT_H_
#define MCAL_MNVIC_MNVIC_INT_H_

/*typedef enum {

	WWDG,
	EXTI16,
	EXTI

} Enum_IntNames_t;*/

/*----------------------------------------------------------------------------------------------------*/
/*                                   	  NVIC Grouping Options                                       */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {

	GP16SUB0=3,
	GP8SUB2,
	GP4SUB4,
	GP2SUB8,
	GP0SUB16
} MNVIC_Priority_GP;

/*----------------------------------------------------------------------------------------------------*/
/*                                     	 	 NVIC_Number                                    	      */
/*----------------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------------*/
/*                                      NVIC_Groups                                                   */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {
	GP0,GP1,GP2,GP3,GP4,GP5,GP6,GP7,GP8,GP9,GP10,GP11,GP12,GP13,GP14,GP15
} MNVIC_GP_Options;

/*----------------------------------------------------------------------------------------------------*/
/*                                      NVIC_SubGroups                                                */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {
	SUB0,SUB1,SUB2,SUB3,SUB4,SUB5,SUB6,SUB7,SUB8,SUB9,SUB10,SUB11,SUB12,SUB13,SUB14,SUB15
} MNVIC_SUB_Options ;


/******************************************************************************************************/
/*                                      01- MNVIC_vEnableInterrupt                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Enable NVIC Interrupt                                          */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MNVIC_vEnableInterrupt(Enum_MNVIC_NUM_t Copy_u8InterruptNo);

/******************************************************************************************************/
/*                                      02- MNVIC_vDisableInterrupt                                   */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Disable NVIC Interrupt                                         */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MNVIC_vDisableInterrupt(Enum_MNVIC_NUM_t Copy_u8InterruptNo);

/******************************************************************************************************/
/*                                      03- MNVIC_vSetPendingFlag                                     */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set Pending Flag                                               */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MNVIC_vSetPendingFlag (Enum_MNVIC_NUM_t Copy_u8InterruptNo);

/******************************************************************************************************/
/*                                      04- MNVIC_vClearPendingFlag                                   */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Clear Pending Flag                             mmm             */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MNVIC_vClearPendingFlag (Enum_MNVIC_NUM_t Copy_u8InterruptNo);

/******************************************************************************************************/
/*                                      05- MNVIC_u8ReadActiveFlag                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function read the active flag status of a specific interrupt            */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */                   
/* 3- Function Return      -> u8 (the active flag status of the specified interrupt.)                 */
/******************************************************************************************************/
u8 MNVIC_u8ReadActiveFlag( Enum_MNVIC_NUM_t Copy_u8InterruptNo );


/******************************************************************************************************/
/*                                      06- MNVIC_vInitGrouping                                       */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function initializes the grouping and sub-priority					  */
/*									configuration for the NVIC  									  */
/* 2- Function Input       -> @param Copy_u8Grouping = GP16SUB0,GP8SUB2,GP4SUB4,GP2SUB8,GP0SUB16      */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MNVIC_vInitGrouping(MNVIC_Priority_GP Copy_u8Grouping);

/******************************************************************************************************/
/*                                      07- MNVIC_vSetIntPriority                                     */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function MNVIC_vSetIntPriority                                          */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */ 
/*                         -> @param Copy_u8GP = GP0,GP1,GP2,GP3,GP4,GP5,GP6,GP7,GP8,GP9,			  */
/*													GP10,GP11,GP12,GP13,GP14,GP15 					  */                  
/*                         -> @param Copy_u8SUB = SUB0,SUB1,SUB2,SUB3,SUB4,SUB5,SUB6,SUB7,SUB8,		  */
/*													SUB9,SUB10,SUB11,SUB12,SUB13,SUB14,SUB15 		  */
/* 3- Function Return      -> void                													  */
/******************************************************************************************************/
void MNVIC_vSetIntPriority( Enum_MNVIC_NUM_t Copy_u8InterruptNo , MNVIC_GP_Options Copy_u8GP , MNVIC_SUB_Options Copy_u8SUB );

/******************************************************************************************************/
/*                                      08- MNVIC_vTrigSoftwareInt                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function triggers the Software Interrupt                                */
/* 2- Function Input       -> @param Copy_u8InterruptNo : from Enum_MNVIC_NUM_t enum                  */                   
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void MNVIC_vTrigSoftwareInt( Enum_MNVIC_NUM_t Copy_u8InterruptNo );



#endif /* MCAL_MNVIC_MNVIC_INT_H_ */

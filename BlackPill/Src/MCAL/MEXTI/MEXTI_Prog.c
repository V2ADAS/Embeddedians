/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                   */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/* Description       : Driver Functions Implementation                                                 */
/*******************************************************************************************************/

/***************************************************************************/
/*                           MCAL Components                               */
/***************************************************************************/
#include"MEXTI_Config.h"
#include"MEXTI_Private.h"
#include"MEXTI_Int.h"

/***************************************************************************/
/*                        Functions Implementations                        */
/***************************************************************************/
static void (*GLOBAL_EXTIPtr[16])(void) = {STD_NULL};

void SYSCFG_vConfigEXTI_Line(u8 Copy_u8Port,Enum_MEXTI_No_t Copy_u8EXTI_Num){
		//Clear 4 Bits Before Write
		SYSCFG->EXTICR[Copy_u8EXTI_Num / PIN_PER_REG] &= ~(MASK4 << ( (Copy_u8EXTI_Num % PIN_PER_REG)*BIT_PER_PIN ) );
		SYSCFG->EXTICR[Copy_u8EXTI_Num / PIN_PER_REG] |= (Copy_u8Port << ( (Copy_u8EXTI_Num % PIN_PER_REG)*BIT_PER_PIN ) );
}

void MEXTI_vEnableInterrupt(Enum_MEXTI_No_t Copy_u8EXTI_Num){
	SET_BIT(EXTI->IMR,Copy_u8EXTI_Num);
}

void MEXTI_vDisableInterrupt(u8 Copy_u8EXTI_Num){
	CLR_BIT(EXTI->IMR,Copy_u8EXTI_Num);
}

void MEXTI_vEnableEvent(u8 Copy_u8EXTI_Num){
	SET_BIT(EXTI->EMR,Copy_u8EXTI_Num);
}

void MEXTI_vDisableEvent(u8 Copy_u8EXTI_Num){
	CLR_BIT(EXTI->EMR,Copy_u8EXTI_Num);
}

void MEXTI_vInterruptTrigger(Enum_MEXTI_No_t Copy_u8EXTI_Num,EXTI_TRIGGER Copy_u8Trig){
	switch(Copy_u8Trig){
		case RISING:
			SET_BIT(EXTI->RTSR,Copy_u8EXTI_Num);
			CLR_BIT(EXTI->FTSR,Copy_u8EXTI_Num);
			break;
		case FALLING:
			CLR_BIT(EXTI->RTSR,Copy_u8EXTI_Num);
			SET_BIT(EXTI->FTSR,Copy_u8EXTI_Num);
			break;
		case ONCHARGE:
			SET_BIT(EXTI->RTSR,Copy_u8EXTI_Num);
			SET_BIT(EXTI->FTSR,Copy_u8EXTI_Num);
			break;
	}
}

void MEXTI_vSWevent(u8 Copy_u8EXTI_Num){
	SET_BIT(EXTI->SWIER,Copy_u8EXTI_Num);
}

void MEXTI_PtrReadInterruptFlag(u8 Copy_u8EXTI_Num,u8* Copy_u8Reg){
	* Copy_u8Reg = GET_BIT(EXTI->PR,Copy_u8EXTI_Num);
}


void MEXTI_vCallBack(Enum_MEXTI_No_t Copy_u8InterruptNo ,void(*ptr)(void)){
	if( ptr != STD_NULL){
		GLOBAL_EXTIPtr[Copy_u8InterruptNo]=ptr;
	}
}


void EXTI0_IRQHandler(void){
	GLOBAL_EXTIPtr[0]();
	EXTI->PR |= 1;
}

void EXTI1_IRQHandler(void){
	GLOBAL_EXTIPtr[1]();
	EXTI->PR |= 1<<1;
}

void EXTI2_IRQHandler(void){
	GLOBAL_EXTIPtr[2]();
	EXTI->PR |= 1<<2;
}
void EXTI3_IRQHandler(void){
	GLOBAL_EXTIPtr[3]();
	EXTI->PR |= 1<<3;
}
void EXTI4_IRQHandler(void){
	GLOBAL_EXTIPtr[4]();
	EXTI->PR |= 1<<4;
}
void EXTI9_5_IRQHandler(void){
	if((GET_BIT(EXTI->PR,EXTI5)==1)&(GLOBAL_EXTIPtr[EXTI5]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI5]();
			EXTI->PR |= 1<<EXTI5;
			}
	else if((GET_BIT(EXTI->PR,EXTI6)==1)&(GLOBAL_EXTIPtr[EXTI6]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI6]();
			EXTI->PR |= 1<<EXTI6;
		}
	else if((GET_BIT(EXTI->PR,EXTI7)==1)&(GLOBAL_EXTIPtr[EXTI7]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI7]();
			EXTI->PR |= 1<<EXTI7;
		}
	else if((GET_BIT(EXTI->PR,EXTI8)==1)&(GLOBAL_EXTIPtr[EXTI8]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI8]();
			EXTI->PR |= 1<<EXTI8;
		}
	else if((GET_BIT(EXTI->PR,EXTI9)==1)&(GLOBAL_EXTIPtr[EXTI9]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI9]();
			EXTI->PR |= 1<<EXTI9;
		}
}
void EXTI15_10_IRQHandler(void){
	if((GET_BIT(EXTI->PR,EXTI10)==1)&(GLOBAL_EXTIPtr[EXTI10]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI10]();
			EXTI->PR |= 1<<EXTI10;
			}
	else if((GET_BIT(EXTI->PR,EXTI11)==1)&(GLOBAL_EXTIPtr[EXTI11]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI11]();
			EXTI->PR |= 1<<EXTI11;
		}
	else if((GET_BIT(EXTI->PR,EXTI12)==1)&(GLOBAL_EXTIPtr[EXTI12]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI12]();
			EXTI->PR |= 1<<EXTI12;
		}
	else if((GET_BIT(EXTI->PR,EXTI13)==1)&(GLOBAL_EXTIPtr[EXTI13]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI13]();
			EXTI->PR |= 1<<EXTI13;
		}
	else if((GET_BIT(EXTI->PR,EXTI14)==1)&(GLOBAL_EXTIPtr[EXTI14]!=STD_NULL)){
			GLOBAL_EXTIPtr[EXTI14]();
			EXTI->PR |= 1<<EXTI14;
		}
	else if((GET_BIT(EXTI->PR,EXTI15)==1)&(GLOBAL_EXTIPtr[EXTI15]!=STD_NULL)){
		GLOBAL_EXTIPtr[EXTI15]();
		EXTI->PR |= 1<<EXTI15;
	}
}




/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                  */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/* Description       : Interface file for interfacing with the user                                    */
/* Module  Features  :                                                                                 */
/*      01- void SYSCFG_vConfigEXTI_Line(u8 Copy_u8Port,u8 Copy_u8EXTI_Num);                           */                                                                 
/*      02- void MEXTI_vEnableInterrupt(u8 Copy_u8EXTI_Num);                                           */
/*      03- void MEXTI_vDisableInterrupt(u8 Copy_u8EXTI_Num);                                          */
/*      04- void MEXTI_vEnableEvent(u8 Copy_u8EXTI_Num);                                               */
/*      05- void MEXTI_vDisableEvent(u8 Copy_u8EXTI_Num);                                              */
/*      06- void MEXTI_vInterruptTrigger(u8 Copy_u8EXTI_Num,EXTI_TRIGGER	Copy_u8Trig);          */    
/*      07- void MEXTI_vSWevent(u8 Copy_u8EXTI_Num);                                                   */
/*      08- void MEXTI_u8ReadInterruptFlag(u8 Copy_u8EXTI_Num);                                        */
/*******************************************************************************************************/

    
/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MEXTI_MEXTI_INT_H_
#define MCAL_MEXTI_MEXTI_INT_H_

/********************************************************************************************************/
/*                                            macros of EXTI                                            */
/********************************************************************************************************/
#define EXTI_PORTA		0
#define EXTI_PORTB		1
#define EXTI_PORTC		2
#define EXTI_PORTD		3
#define EXTI_PORTE		4
#define EXTI_PORTH		7

typedef enum{
	RISING,
	FALLING,
	ONCHARGE
}	EXTI_TRIGGER;


typedef enum {

	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15,
} Enum_MEXTI_No_t;

void SYSCFG_vConfigEXTI_Line(u8 Copy_u8Port,u8 Copy_u8EXTI_Num);

void MEXTI_vEnableInterrupt(u8 Copy_u8EXTI_Num);

void MEXTI_vDisableInterrupt(u8 Copy_u8EXTI_Num);

void MEXTI_vEnableEvent(u8 Copy_u8EXTI_Num);

void MEXTI_vDisableEvent(u8 Copy_u8EXTI_Num);

void MEXTI_vInterruptTrigger(u8 Copy_u8EXTI_Num,EXTI_TRIGGER	Copy_u8Trig);

void MEXTI_vSWevent(u8 Copy_u8EXTI_Num);

void MEXTI_u8ReadInterruptFlag(u8 Copy_u8EXTI_Num);

void MEXTI_vCallBack(Enum_MEXTI_No_t Copy_u8InterruptNo ,void(*ptr)(void));


#endif /* MCAL_MEXTI_MEXTI_INT_H_ */

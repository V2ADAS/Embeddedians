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
/*********************************************************************************************************/
/*                                      01- SYSCFG_vConfigEXTI_Line                                      */
/*-------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Configures the EXTI line for a specific port and EXTI number.              */
/* 2- Function Input       -> Copy_u8Port: The port number to configure (e.g., GPIOA, GPIOB, etc.).      */
/*                           Copy_u8EXTI_Num: The EXTI number to configure (0-15).                       */
/* 3- Function Return      -> void                                                                       */
/******************************************************************************************************/
void SYSCFG_vConfigEXTI_Line(u8 Copy_u8Port,u8 Copy_u8EXTI_Num);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      02- MEXTI_vEnableInterrupt                                      */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enables the interrupt for a specific EXTI number.                          */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to enable the interrupt for (0-15).      */
/* 3- Function Return      -> void                                                                     */
/******************************************************************************************************/
void MEXTI_vEnableInterrupt(u8 Copy_u8EXTI_Num);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      03- MEXTI_vDisableInterrupt                                     */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Disables the interrupt for a specific EXTI number.                         */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to disable the interrupt for (0-15).     */
/* 3- Function Return      -> void                                                                     */
/******************************************************************************************************/
void MEXTI_vDisableInterrupt(u8 Copy_u8EXTI_Num);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      04- MEXTI_vEnableEvent                                          */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enables the event for a specific EXTI number.                              */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to enable the event for (0-15).          */
/* 3- Function Return      -> void                                                                     */
/******************************************************************************************************/
void MEXTI_vEnableEvent(u8 Copy_u8EXTI_Num);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      05- MEXTI_vDisableEvent                                         */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Disables the event for a specific EXTI number.                             */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to disable the event for (0-15).         */
/* 3- Function Return      -> void                                                                     */
/******************************************************************************************************/
void MEXTI_vDisableEvent(u8 Copy_u8EXTI_Num);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      06- MEXTI_vInterruptTrigger                                     */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Configures the trigger type for a specific EXTI number.                    */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to configure the trigger for (0-15).     */
/*                           Copy_u8Trig: The trigger type (e.g., EXTI_TRIGGER_RISING_EDGE,             */
/*                                        EXTI_TRIGGER_FALLING_EDGE, or EXTI_TRIGGER_BOTH_EDGES).       */
/* 3- Function Return      -> void                                                                     */
/******************************************************************************************************/
void MEXTI_vInterruptTrigger(u8 Copy_u8EXTI_Num,EXTI_TRIGGER	Copy_u8Trig);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      07- MEXTI_vSWevent                                              */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Software triggers an event for a specific EXTI number.                     */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to trigger the event for (0-15).         */
/* 3- Function Return      -> void                                                                     */
/******************************************************************************************************/
void MEXTI_vSWevent(u8 Copy_u8EXTI_Num);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      08- MEXTI_u8ReadInterruptFlag                                   */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Reads the interrupt flag for a specific EXTI number.                       */
/* 2- Function Input       -> Copy_u8EXTI_Num: The EXTI number to read the interrupt flag for (0-15).   */
/* 3- Function Return      -> The interrupt flag value (0 or 1).                                         */
/******************************************************************************************************/
void MEXTI_u8ReadInterruptFlag(u8 Copy_u8EXTI_Num);
/******************************************************************************************************/
void MEXTI_vCallBack(Enum_MEXTI_No_t Copy_u8InterruptNo ,void(*ptr)(void));


#endif /* MCAL_MEXTI_MEXTI_INT_H_ */

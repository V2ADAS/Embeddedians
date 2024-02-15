/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                            	   */
/* Version           : V0.0.0                                                                          */
/* Data              : 28 Jan 2024                                                                     */
/* Description       : MTimer_Prog.c --> implementations                                               */
/* Module  Features  :                                                                                 */
/*      01- MTIMER_vPeriodicMS                                                                         */
/*      02- MTIMER_vPWM                                                                                */
/*      03- MTIMER_vICU                                                                                */
/*      04- MTIMER_GET_ICU                                                                             */
/*      05- MTIMER_CallBack                                                                            */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MTIMER_MTIMER_INT_H_
#define MCAL_MTIMER_MTIMER_INT_H_

/*******************************************************************************************************/
/*                                   enum for Timer numbers   					                       */
/*						' TIMER 1, TIMER2, TIMER3, TIMER4, TIMER5,									   */
/* 														TIMER9, TIMER10, TIMER11'					   */
/* 																									   */
/*******************************************************************************************************/
typedef enum{
	TIMER1=1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER9,
	TIMER10,
	TIMER11,
}Enum_TIMER_NUM;
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   enum for Timer channel numbers   					               */
/*			  FOR TIMER 1, TIMER2, TIMER3, TIMER4, TIMER5 ==> CH1,CH2,CH3,CH4				           */
/* 									FOR TIMER9            ==> CH1,CH2 								   */
/* 									FOR TIMER10, TIMER11  ==> CH1					   				   */
/*******************************************************************************************************/
typedef enum{
	CH1=1,
	CH2,
	CH3,
	CH4,
}Enum_TIMER_CHs;
/*******************************************************************************************************/



/******************************************************************************************************/
/*                                          APIs                                                      */
/******************************************************************************************************/


/******************************************************************************************************/
/*                                      01- MTIMER_vPeriodicMS                                        */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Configures the specified TIMER for generating periodic interrupts with a delay in milliseconds.
 * @param Copy_u8TimerNum: The TIMER number to be configured.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u32Delay: The delay in milliseconds for the periodic interrupt.
 * 							Expected to be Value from 1 to 2^32-1 "4294967296"
 * @return	void
 */
void MTIMER_vPeriodicMS(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delay);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      02- MTIMER_vPWM                                       		  */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Configures the specified TIMER in PWM mode on a specific channel.
 * @param Copy_u8TimerNum: The TIMER number to be configured.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u8Channel: The channel on which PWM is configured.
 * 							Expected to be Enum_TIMER_CHs ==> { CH1, CH2, CH3, CH4 }
 * @param Copy_u16TotalTime_uSec: The total time period for the PWM signal in microseconds.
 * @param Copy_u16PositiveDutyCycle_uSec: The positive duty cycle of the PWM signal in microseconds.
 * @return	void
 */
void MTIMER_vPWM(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel, u16 Copy_u16TotalTime_uSec, u16 Copy_u16PositiveDutyCycle_uSec);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      03- MTIMER_vICU                                       		  */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Configures the specified TIMER to work as an Input Capture Unit (ICU) on a specific channel.
 * @param Copy_u8TimerNum: The TIMER number to be configured.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u8Channel: The channel on which the Input Capture Unit is configured.
 * 							Expected to be Enum_TIMER_CHs ==> { CH1, CH2, CH3, CH4 }
 * @return	void
 */
void MTIMER_vICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      04- MTIMER_GET_ICU                                       	  */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Retrieves the captured time value from an Input Capture event on the specified TIMER and channel.
 * @param Copy_u8TimerNum: The TIMER number from which to retrieve the captured time.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u8Channel: The channel on which the Input Capture event occurred.
 * 							Expected to be Enum_TIMER_CHs ==> { CH1, CH2, CH3, CH4 }
 * @return The captured time value.
 */
u32 MTIMER_GET_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      05- MTIMER_CallBack                                       	  */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Registers a callback function to be executed when the specified TIMER generates an interrupt.
 * @param Copy_u8TimerNum: The TIMER number for which the callback is registered.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param ptr: A function pointer to the callback function."Expected to be given address of callback function"
 * @return	void
 */
void MTIMER_CallBack(Enum_TIMER_NUM Copy_u8TimerNum, void (*ptr)(void));
/******************************************************************************************************/

#endif /* MCAL_MTIMER_MTIMER_INT_H_ */

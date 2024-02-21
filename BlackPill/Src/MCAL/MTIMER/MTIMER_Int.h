/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                            	   */
/* Version           : V1.0.9                                                                          */
/* Data              : 28 Jan 2024                                                                     */
/* Description       : MTimer_Prog.c --> implementations                                               */
/* Module  Features  :                                                                                 */
/*      01- MTIMER_vPeriodicMS                                                                         */
/*		02- MTIMER_EXTCNTClock																		   */
/*      03- MTIMER_vClearCNT																		   */
/*      04- MTIMER_vPWM                                                                                */
/*      05- MTIMER_vICU                                                                                */
/*      06- MTIMER_GET_ICU                                                                             */
/*      07- MTIMER_CallBack                                                                            */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MTIMER_MTIMER_INT_H_
#define MCAL_MTIMER_MTIMER_INT_H_

/*******************************************************************************************************/
/*                                    Include files needed for MTIMER_Int.h 		                   */
/*******************************************************************************************************/
#include"../../LIB/STD_TYPES.h" //Standard Types Lib
/*******************************************************************************************************/
/*                                   enum for Timer numbers   					                       */
/*						' TIMER 1, TIMER2, TIMER3, TIMER4, TIMER5,									   */
/* 														TIMER9, TIMER10, TIMER11'					   */
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

/*******************************************************************************************************/
//   Timer and Channel Pin Mapping:
/* Timer and Channel Pin Mapping:
   TIMER1, CH1 -> Port A, Pin 8
   TIMER1, CH2 -> Port A, Pin 9
   TIMER1, CH3 -> Port A, Pin 10
   TIMER1, CH4 -> Port A, Pin 11

   TIMER2, CH1 -> Port A, Pin 15
   TIMER2, CH2 -> Port B, Pin 3
   TIMER2, CH3 -> Port A, Pin 2
   TIMER2, CH4 -> Port A, Pin 3

   TIMER3, CH1 -> Port A, Pin 6
   TIMER3, CH2 -> Port A, Pin 7
   TIMER3, CH3 -> Port B, Pin 0
   TIMER3, CH4 -> Port B, Pin 1

   TIMER4, CH1 -> Port B, Pin 6
   TIMER4, CH2 -> Port B, Pin 7
   TIMER4, CH3 -> Port B, Pin 8
   TIMER4, CH4 -> Port B, Pin 9

   TIMER5, CH1 -> Port A, Pin 0
   TIMER5, CH2 -> Port A, Pin 1
   TIMER5, CH3 -> Port A, Pin 2
   TIMER5, CH4 -> Port A, Pin 3

   TIMER9, CH1 -> Port A, Pin 2
   TIMER9, CH2 -> Port A, Pin 3

   TIMER10, CH1 -> Port B, Pin 8

   TIMER11, CH1 -> Port B, Pin 9
*/

#include"../MGPIO/MGPIO_int.h"

volatile static u8 TIMER_PORT_MAP[TIMER11][CH4]=
{
		/*TIMER 1*/
		{	PORTA,	PORTA,	PORTA,	PORTA	},

		/* TIMER2 */
		{	PORTA,	PORTB,	PORTA,	PORTA	},

		/* TIMER3 */
		{	PORTA,	PORTA,	PORTB,	PORTB	},

		/* TIMER4 */
		{	PORTB,	PORTB,	PORTB,	PORTB	},

		/* TIMER5 */
		{	PORTA,	PORTA,	PORTA,	PORTA	},

		/* TIMER9 */
		{	PORTA,	PORTA,	PORTA,	PORTA	},

		/* TIMER10 */
		{	PORTB,	PORTB,	PORTA,	PORTA	},

		/* TIMER11 */
		{	PORTB,	PORTB,	PORTA,	PORTA	},
};

volatile static u8 TIMER_PIN_MAP[TIMER11][CH4]=
{
		/*TIMER 1*/
		{	PIN8,	PIN9,	PIN10,	PIN11	},

		/* TIMER2 */
		{	PIN15,	PIN3,	PIN2,	PIN3	},

		/* TIMER3 */
		{	PIN6,	PIN7,	PIN0,	PIN1	},

		/* TIMER4 */
		{	PIN6,	PIN7,	PIN8,	PIN9	},

		/* TIMER5 */
		{	PIN0,	PIN1,	PIN2,	PIN3	},

		/* TIMER9 */
		{	PIN2,	PIN3,	PIN2,	PIN3	},

		/* TIMER10 */
		{	PIN8,	PIN8,	PIN8,	PIN8	},

		/* TIMER11 */
		{	PIN9,	PIN9,	PIN9,	PIN9	}
};

volatile static u8 TIMER_AF[TIMER11]={
		MGPIO_ALTFUNC_TIM12,MGPIO_ALTFUNC_TIM12,
		MGPIO_ALTFUNC_TIM35,MGPIO_ALTFUNC_TIM35,MGPIO_ALTFUNC_TIM35,
		MGPIO_ALTFUNC_TIM911,MGPIO_ALTFUNC_TIM911,MGPIO_ALTFUNC_TIM911		};
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
/*											02- MTIMER_vEXTCNTClock									  */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @brief Configures the specified TIMER channel to count external events on the rising edge of the input signal.
 * @param Copy_u8TimerNum: The TIMER number to be configured.
 *                         Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                           TIMER5, TIMER9 }.
 * @param Copy_u8Channel: The channel on which external events will be counted.
 *                        Expected to be Enum_TIMER_CHs ==> { CH1, CH2 }.
 * @param Copy_u32Max_Value: The maximum value for the counter. When the counter reaches this value, it will reset.
 * @return void
 * NOTE: NO EXTERNAL CLOCK MODE FOR CH3 or CH4 for Any TIMER
 * 			ALSO NO EXTERNAL MODE AT ALL FOR TIMER 10 or TIMER 11
 */
/*----------------------------------------------------------------------------------------------------*/
void MTIMER_vEXTCNTClock(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel, u32 Copy_u32Max_Value);
/******************************************************************************************************/


/******************************************************************************************************/
/*                                      03- MTIMER_vClearCNT                                          */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Clears the counter (CNT) of the specified TIMER.
 * @param Copy_u8TimerNum: The TIMER number to clear the counter.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @return	void
 */
void MTIMER_vClearCNT(Enum_TIMER_NUM Copy_u8TimerNum);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      04- MTIMER_vPWM                                       		  */
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
/*                                      05- MTIMER_vICU                                       		  */
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
/*                                      06- MTIMER_GET_ICU                                       	  */
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
/*                                      07- MTIMER_CallBack                                       	  */
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

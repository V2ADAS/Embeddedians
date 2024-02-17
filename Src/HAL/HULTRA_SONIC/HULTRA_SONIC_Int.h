/********************************************************************************************************/
/* Author            : Amr ElMaghraby                                                             		*/
/* Version           : V1.0.5                                                                           */
/* Data              : 5 Feb 2024                                                                       */
/* Description       : HULTRA_SONIC_Int.h --> implementations                                          */
/* Module  Features  :																					*/
/* @Functions:																							*/
/*      01- HULTRA_vInitialize                                                                          */
/*      02- HULTRA_vSendTrigger                                                                         */
/*      03- HULTRA_vGetDistance																			*/
/* @TypeDef:																							*/
/* 		@Enums:																							*/
/* 	    	 01- Enum_ULTRA_SONIC_NUM                                                        			*/
/********************************************************************************************************/


/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef HAL_HULTRA_SONIC_HULTRA_SONIC_INT_H_
#define HAL_HULTRA_SONIC_HULTRA_SONIC_INT_H_

/*******************************************************************************************************/
/*                                    Include files needed for HULTRA_SONIC_Int.h 		               */
/*******************************************************************************************************/
#include"../../LIB/STD_TYPES.h" //Standard Types Lib
#include "../../MCAL/MTIMER/MTIMER_Int.h" // TIMER (Timer Control)
/********************************************************************************************************/
/*                                     Enum for ULTRASONIC Numbering        		                    */
/********************************************************************************************************/
typedef	enum{
	ULTRA_SONIC1,ULTRA_SONIC2,ULTRA_SONIC3,ULTRA_SONIC4,ULTRA_SONIC5,
	ULTRA_SONIC6,ULTRA_SONIC7,ULTRA_SONIC8,ULTRA_SONIC9,ULTRA_SONIC10,
	ULTRA_SONIC11,ULTRA_SONIC12,ULTRA_SONIC13,ULTRA_SONIC14,ULTRA_SONIC15,
	ULTRA_SONIC16,ULTRA_SONIC17,ULTRA_SONIC18,ULTRA_SONIC19,ULTRA_SONIC20,
}Enum_ULTRA_SONIC_NUM;




/******************************************************************************************************/
/*                                          APIs                                                      */
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      01- HULTRA_vInitialize                                        */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description  Initialize ultrasonic sensor parameters including GPIO and timer configurations.
 *
 *@param	Copy_u8Ultra_NUM: Numbering ultrasonic as wanted to be used in the HULTRA_vGetDistance function.
 * 								Expected to be Enum_ULTRA_SONIC_NUM { ULTRA_SONIC1 , .... , ULTRA_SONIC20 }
 *
 * @param   Copy_u8TimerNum: The timer number used for ultrasonic sensor measurement.
 * 								Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 									TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param   Copy_u8ChannelNum: The timer channel number used for ultrasonic sensor measurement.
 * 								Expected to be Enum_TIMER_CHs ==> { CH1, CH2, CH3, CH4 }
 *
 *
 * @return	void
 *
 * @note    This function sets up the GPIO pins and configures the specified timer for ultrasonic sensor interfacing.
 *          The ultrasonic sensor parameters are stored in the ULTRA_NUM array based on the timer and channel numbers.
 */
void HULTRA_vInitialize(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,Enum_TIMER_NUM Copy_u8TimerNum, u8 Copy_u8ChannelNum);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      02- HULTRA_vSendTrigger                                       */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description   Send a trigger signal to an ultrasonic sensor.
 *
 * @param   Copy_u8Port: The GPIO port of the ultrasonic sensor trigger pin.
 * 							Expected to be any defined port name {GPIOA, GPIOB, GPIOC}
 * @param   Copy_u8Pin: The GPIO pin of the ultrasonic sensor trigger.
 *							Expected to be any defined pin number  {PIN1 , . . . , PIN15}
 *
 * @return	void
 *
 * @note    This function sets the specified pin as an OUTPUT, raises it to HIGH for a short duration,
 *          then brings it back to LOW. It is typically used to initiate distance measurements in ultrasonic sensors.
 */
void HULTRA_vSendTrigger(u8 Copy_u8Port, u8 Copy_u8Pin);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      03- HULTRA_vGetDistance                                       */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description   Get the distance measurement from an ultrasonic sensor.
 *
 * @param	Copy_u8Ultra_NUM: Write any ultrasonic number defined in initialization function as wanted.
 * 								Expected to be Enum_ULTRA_SONIC_NUM { ULTRA_SONIC1 , .... , ULTRA_SONIC20 }
 * @param   Copy_f64Distance: Pointer to a variable to store the calculated distance.
 *
 * @return	void
 *
 * @note    This function calculates the distance based on the input from a specified timer channel.
 *          The calculated distance is stored in the variable pointed to by Copy_f64Distance.
 *          The formula used for the calculation assumes a speed of sound of 343 meters per second.
 *          The timer values are expected to represent the time taken for the ultrasonic signal to travel
 *          to an object and back, divided by 2 to get the one-way distance.
 */
void HULTRA_vGetDistance(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,f64* Copy_f64Distance);

/******************************************************************************************************/

#endif /* HAL_HULTRA_SONIC_HULTRA_SONIC_INT_H_ */

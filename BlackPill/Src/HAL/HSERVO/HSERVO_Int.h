/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                                  */
/* Version           : V1.0.3                                                                          */
/* Data              : 28 Dec 2023                                                                     */
/* Description       : HSERVO_Interface.h --> implementations                                          */
/* Module  Features  :                                                                                 */
/*      01- HSERVO_vServoInit                                                                          */
/*      02- HSERVO_vServoDeg                                                                           */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef HAL_HSERVO_HSERVO_INT_H_
#define HAL_HSERVO_HSERVO_INT_H_

/*******************************************************************************************************/
/*                                    Include files needed for HSERVO_Int.h 		                   */
/*******************************************************************************************************/
#include"../../LIB/STD_TYPES.h" //Standard Types Lib
#include "../../MCAL/MTIMER/MTIMER_Int.h" // TIMER (Timer Control)
/*******************************************************************************************************/
/*                                   enum for Servo number					                           */
/*******************************************************************************************************/
typedef enum {
	SERVO1, SERVO2, SERVO3, SERVO4, SERVO5,
	SERVO6, SERVO7, SERVO8, SERVO9, SERVO10,
    SERVO11, SERVO12, SERVO13, SERVO14, SERVO15,
    SERVO16, SERVO17, SERVO18, SERVO19, SERVO20,
} Enum_SERVO_NUM;
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                          APIs                                                       */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      01- HSERVO_vServoInit                                          */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Initializes a servo motor connected to a specific TIMER and channel for PWM control.
 * @param Copy_u8ServoNum: The enumeration representing the servo motor number.
 * 							Expected to be Enum_SERVO_NUM ==> {SERVO1, SERVO2, ... , SERVO20}
 * @param Copy_u8TimerNum: The enumeration representing the TIMER to be used for PWM control.
 * 							Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 * 								TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u8ChannelNum: The channel number on the selected TIMER to which the servo is connected.
 * 							Expected to be Enum_TIMER_CHs ==> { CH1, CH2, CH3, CH4 }
 *
 * @note This function configures the specified TIMER and channel to generate PWM signals suitable for
 * 		 servo control.Ensure that the corresponding timer and channel are available for servo control
 * 		 on the selected microcontroller.
 *       Additionally, adjust the servo-specific parameters, such as PWM frequency and duty cycle,
 *        based on servo specifications.
 */
void HSERVO_vServoInit(Enum_SERVO_NUM Copy_u8ServoNum,Enum_TIMER_NUM Copy_u8TimerNum,u8 Copy_u8ChannelNum);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      01- HSERVO_vServoDeg                                          */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @brief Moves a servo motor to a specified angle in degrees.
 * @param Copy_u8ServoNum: The enumeration representing the servo motor number.
 * 							Expected to be Enum_SERVO_NUM ==> {SERVO1, SERVO2, ... , SERVO20}
 * @param Copy_u8Deg: The desired angle in degrees to which the servo motor should be positioned.
 * 							Expected to be { ANY ANGLE from ( ZERO_POS - 45 ) to ( ZERO_POS + 45 )  }
 * 							NOTE: Input Angle input will be added to ZERO_POS Macros defined
 * 							 						in configuration file.
 * @return:	void
 * @note This function adjusts the PWM signal sent to the specified servo motor to achieve the desired angle.
 *       Ensure that the servo motor is initialized using HSERVO_vServoInit before calling this function.
 *       Additionally, consider the servo motor specifications and adjust the PWM signal parameters accordingly.
 *       PWM signal:	20msec FullTime		(0.5 => 2.5msec) Duty Cycle for 0 to 180 Deg.
 */
void HSERVO_vServoDeg(Enum_SERVO_NUM Copy_u8ServoNum,s8 Copy_s8Deg);
/******************************************************************************************************/

#endif /* HAL_HSERVO_HSERVO_INT_H_ */

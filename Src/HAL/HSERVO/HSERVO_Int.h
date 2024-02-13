/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                                  */
/* Version           : V0.0.0                                                                          */
/* Data              : 28 Dec 2023                                                                     */
/* Description       : HSERVO_Interface.c --> implementations                                          */
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
/*                                   enum for Servo number					                           */
/*******************************************************************************************************/
typedef enum {
	SERVO1, SERVO2, SERVO3, SERVO4, SERVO5,
	SERVO6, SERVO7, SERVO8, SERVO9, SERVO10,
    SERVO11, SERVO12, SERVO13, SERVO14, SERVO15,
    SERVO16, SERVO17, SERVO18, SERVO19, SERVO20,
} Enum_SERVO_NUM;
/*******************************************************************************************************/

/******************************************************************************************************/
/*                                          APIs                                                      */
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      01- HSERVO_vServoInit                                              */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description Initializes a servo motor connected to a specific timer and channel for PWM control.
 * @param Copy_u8ServoNum: The enumeration representing the servo motor number.
 * @param Copy_u8TimerNum: The enumeration representing the timer to be used for PWM control.
 * @param Copy_u8ChannelNum: The channel number on the selected timer to which the servo is connected.
 *
 * @note This function configures the specified timer and channel to generate PWM signals suitable for servo control.
 *       Ensure that the corresponding timer and channel are available for servo control on the selected microcontroller.
 *       Additionally, adjust the servo-specific parameters, such as PWM frequency and duty cycle, based on servo specifications.
 */
void HSERVO_vServoInit(Enum_SERVO_NUM Copy_u8ServoNum,Enum_TIMER_NUM Copy_u8TimerNum,u8 Copy_u8ChannelNum);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      01- HSERVO_vServoDeg                                          */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @brief Moves a servo motor to a specified angle in degrees.
 * @param Copy_u8ServoNum: The enumeration representing the servo motor number.
 * @param Copy_u8Deg: The desired angle in degrees to which the servo motor should be positioned.
 * @return:	void
 * @note This function adjusts the PWM signal sent to the specified servo motor to achieve the desired angle.
 *       Ensure that the servo motor is initialized using HSERVO_vServoInit before calling this function.
 *       Additionally, consider the servo motor specifications and adjust the PWM signal parameters accordingly.
 *       PWM signal:	20msec FullTime		(0.5 => 2.5msec) Duty Cycle for 0 to 180 Deg.
 */
void HSERVO_vServoDeg(Enum_SERVO_NUM Copy_u8ServoNum,u32 Copy_u8Deg);
/******************************************************************************************************/

#endif /* HAL_HSERVO_HSERVO_INT_H_ */

/*
 *  HAL_MOTOR.h
 *
 *  Created on: 31/1/2024
 *  Author: Mohamed Hawas
 */

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_


#include "../../LIB/STD_TYPES.h"


void HAL_MOTOR_Init ( u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 ,u8 PORT_PWM ,
					u8 PIN_PWM, u8 PWM_TIMER , u8 ENCODER_EXTIx ,u8 NVIC_EXTIx);

void HAL_MOTOR_MOVE(u8 DIRCTION ,u8 SPEED ,f32 DISTANCE_cm_);

void HAL_MOTOR_STOP();






/*************************Configuration************************/
typedef struct {
	//3 pins from the h-bridge
	u8 PORT_N1 ;
	u8 PIN_N1 ;
	u8 PORT_N2 ;
	u8 PIN_N2 ;
	u8 PORT_PWM ;
	u8 PIN_PWM ;
	//2 pins from encoder
	u8 PORT_SIGNAL1 ;
	u8 PIN_SIGNAL1 	;
	u8 PORT_SIGNAL2 ;
	u8 PIN_SIGNAL2 	;

}MOTOR_PINS_t;

#define FORWARD   1
#define BACKWARD  0



















#endif /*HAL_MOTOR_H_*/
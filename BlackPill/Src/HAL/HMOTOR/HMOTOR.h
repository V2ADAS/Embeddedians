/*
 *  HAL_MOTOR.h
 *  Created on: 31/1/2024
 *  Author: Mohamed Hawas
 */

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"

#define WHEEL_AREA   26
#define PULSES_PER_REVOLUTION 1024
#define PULSES_PER_1_CM		39		// ( 1 * PULSES_PER_REVOLUTION ) / WHEEL_AREA
#define DC_MOTOR	1
#define CALP_MOTOR	2

void HAL_MOTOR_Init(u8 MOTOR , u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 , Enum_TIMER_NUM PWM_TIMER , Enum_TIMER_CHs PWM_CH);

//void HAL_MOTOR_Init ( u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 ,u8 PORT_PWM ,
//					u8 PIN_PWM, u8 PWM_TIMER , u8 ENCODER_EXTIx ,u8 NVIC_EXTIx);

void HAL_MOTOR_MOVE(u8 MOTOR , s8 DIRCTION ,u8 SPEED );

void HAL_MOTOR_ForceStop(u8 MOTOR);

void HAL_MOTOR_StopDcAfterDistance(f32 distance);


void HAL_ENCODER_Init( Enum_TIMER_NUM CNTR_TIMER , Enum_TIMER_CHs CNTR_CH );

f64 HAL_MOTOR_GetMovedDistance();



/*************************Configuration************************/
typedef struct {
	//3 pins from the h-bridge
	u8 PORT_N1 ;
	u8 PIN_N1 ;
	u8 PORT_N2 ;
	u8 PIN_N2 ;
	u8 PWM_TIMER ;
	u8 PWM_CH ;
}MOTOR_t;

extern MOTOR_t DC_Motor;

typedef struct {
	u8 CNTR_TIMER;
	u8 CNTR_CH;
}ENCODER_t;
#define FORWARD   1
#define BACKWARD  -1



















#endif /*HAL_MOTOR_H_*/

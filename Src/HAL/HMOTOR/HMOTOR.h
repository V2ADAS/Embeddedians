/*
 *  HAL_MOTOR.h
 *
 *  Created on: 31/1/2024
 *  Author: Mohamed Hawas
 */

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_





void HAL_MOTOR_Init(u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 ,u8 PORT_PWM , u8 PIN_PWM);
void HAL_MOTOR_MOVE(u8 DIRCTION ,u8 SPEED );
void HAL_MOTOR_STOP();
void test(u8 x);





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

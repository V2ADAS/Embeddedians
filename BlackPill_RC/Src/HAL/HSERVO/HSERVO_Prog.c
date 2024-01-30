/*
 * HSERVO_Prog.c
 *
 *  Created on: Dec 21, 2023
 *      Author: Hardware
 */

#include"../../MCAL/MRCC/MRCC_Int.h"

#include"../../MCAL/MGPIO/MGPIO_Int.h"

#include"../../MCAL/MTIMER/MTIMER_Int.h"

#include"HSERVO_Config.h"
#include"HSERVO_Int.h"

u8 Global_Channel = 1;

void HSERVO_vServoInit(u8 Copy_u8Port,u8 Copy_u8Pin){
	MGPIO_vSetPinMode(Copy_u8Port, Copy_u8Pin, ALTFUNC);
	MGPIO_vSetAlternativeFunction(Copy_u8Port, Copy_u8Pin, AF1);
	MRCC_vEnableClock(TIM1_EN);
	Global_Channel = Copy_u8Pin - 7;
}

void HSERVO_vServoDeg(u32 Copy_u8Deg){
	if(Copy_u8Deg >180){
		Copy_u8Deg = 180;
	}
	u16 Positive_Duty = ( (Copy_u8Deg * 1000)/180 + 1000 );
	MTIMER1_vPWM(Global_Channel, SERVO_FullPeriod, Positive_Duty);
}







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

typedef struct{
	Enum_TIMER_NUM	TIMER;
	Enum_TIMER_CHs	CHANNEL;
}LOC_SERVO_NUM;
LOC_SERVO_NUM	SERVO_STRUCT[20];

void HSERVO_vServoInit(Enum_SERVO_NUM Copy_u8ServoNum,Enum_TIMER_NUM Copy_u8TimerNum,u8 Copy_u8ChannelNum){

	switch(Copy_u8TimerNum){
	case TIMER1:
		MGPIO_vSetPinMode(PORTA, Copy_u8ChannelNum + 7 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, Copy_u8ChannelNum + 7 , MGPIO_ALTFUNC_TIM12);
		break;
	case TIMER2:
		if(Copy_u8ChannelNum == 1){
			MGPIO_vSetPinMode(PORTA, Copy_u8ChannelNum + 14 , ALTFUNC);
			MGPIO_vSetAlternativeFunction(PORTA, Copy_u8ChannelNum + 14 , MGPIO_ALTFUNC_TIM12);}
		else if(Copy_u8ChannelNum == 2){
			MGPIO_vSetPinMode(PORTB, Copy_u8ChannelNum + 1 , ALTFUNC);
			MGPIO_vSetAlternativeFunction(PORTB, Copy_u8ChannelNum + 1 , MGPIO_ALTFUNC_TIM12);
		}
		else{
			MGPIO_vSetPinMode(PORTA, Copy_u8ChannelNum - 1 , ALTFUNC);
			MGPIO_vSetAlternativeFunction(PORTA, Copy_u8ChannelNum - 1 , MGPIO_ALTFUNC_TIM12);
		}
		break;
	case TIMER3:
		if(Copy_u8ChannelNum<CH3){
			MGPIO_vSetPinMode(PORTA, Copy_u8ChannelNum + 5 , ALTFUNC);
			MGPIO_vSetAlternativeFunction(PORTA, Copy_u8ChannelNum + 5 , MGPIO_ALTFUNC_TIM35);}
		else{
			MGPIO_vSetPinMode(PORTB, Copy_u8ChannelNum  - CH3 , ALTFUNC);
			MGPIO_vSetAlternativeFunction(PORTB, Copy_u8ChannelNum - CH3 , MGPIO_ALTFUNC_TIM35);
		}
		break;
	case TIMER4:
		MGPIO_vSetPinMode(PORTB, Copy_u8ChannelNum + 5 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTB, Copy_u8ChannelNum + 5 , MGPIO_ALTFUNC_TIM35);
		break;
	case TIMER5:
		MGPIO_vSetPinMode(PORTA, Copy_u8ChannelNum - 1  , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, Copy_u8ChannelNum - 1 , MGPIO_ALTFUNC_TIM35);
		break;
	case TIMER9:
		MGPIO_vSetPinMode(PORTA, Copy_u8ChannelNum + 1 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, Copy_u8ChannelNum + 1 , MGPIO_ALTFUNC_TIM911);
		break;
	case TIMER10:
		MGPIO_vSetPinMode(PORTB, Copy_u8ChannelNum + 7 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTB, Copy_u8ChannelNum + 7 , MGPIO_ALTFUNC_TIM911);
		break;
	case TIMER11:
		MGPIO_vSetPinMode(PORTB, Copy_u8ChannelNum + 8 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTB, Copy_u8ChannelNum + 8 , MGPIO_ALTFUNC_TIM911);
		break;
	}
	SERVO_STRUCT[Copy_u8ServoNum].TIMER = Copy_u8TimerNum;
	SERVO_STRUCT[Copy_u8ServoNum].CHANNEL = Copy_u8ChannelNum;
}

void HSERVO_vServoDeg(Enum_SERVO_NUM Copy_u8ServoNum,s8 Copy_s8Deg){
	if(Copy_s8Deg < -45)
		Copy_s8Deg = -45;
	else if(Copy_s8Deg > 45)
		Copy_s8Deg = 45;
	Copy_s8Deg += ZERO_POS;
	u16 Positive_Duty = ( (Copy_s8Deg * 2000)/180 + 500 );
	MTIMER_vPWM(SERVO_STRUCT[Copy_u8ServoNum].TIMER,SERVO_STRUCT[Copy_u8ServoNum].CHANNEL, SERVO_FullPeriod, Positive_Duty);
}







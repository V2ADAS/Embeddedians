/*
 * HULTRA_SONIC_Prog.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Hardware
 */

#include"../../MCAL/MRCC/MRCC_Int.h"
#include"../../MCAL/MGPIO/MGPIO_int.h"
#include"../../MCAL/MTIMER/MTIMER_Int.h"
#include"../../MCAL/MSTK/MSYSTICK_Int.h"

#include"HULTRA_SONIC_Config.h"
#include"HULTRA_SONIC_Int.h"


void HULTRA_vInitialize(Enum_TIMER_NUM Copy_u8TimerNum , u8 Copy_u8ChannelNum)
{
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

	MTIMER_vICU(Copy_u8TimerNum,Copy_u8ChannelNum);

}


void HULTRA_vSendTrigger(u8 Copy_u8Port, u8 Copy_u8Pin) {
    // Set the ultrasonic sensor trigger pin as OUTPUT
    MGPIO_vSetPinMode(Copy_u8Port, Copy_u8Pin, OUTPUT);

    // Raise the ultrasonic sensor trigger pin to HIGH for a short duration
    MGPIO_vSetPinAtomic(Copy_u8Port, Copy_u8Pin, HIGH);
    MSYSTICK_vDelayms(100);  // Wait for 100 milliseconds

    // Bring the ultrasonic sensor trigger pin back to LOW
    MGPIO_vSetPinAtomic(Copy_u8Port, Copy_u8Pin, LOW);
}


void HULTRA_vGetDistance(f64* Copy_f64Distance, u8 Copy_u8TimerNum, u8 Copy_u8ChannelNum) {
    // Calculate distance based on timer values and assume speed of sound is 343 meters per second
    *Copy_f64Distance = ((f64)MTIMER_GET_ICU(Copy_u8TimerNum, Copy_u8ChannelNum) / 2) * 3.43;
}




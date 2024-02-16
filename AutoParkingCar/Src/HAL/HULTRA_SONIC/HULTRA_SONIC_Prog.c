/********************************************************************************************************/
/* Author            : Amr ElMaghraby                                                             		*/
/* Version           : V1.0.5                                                                           */
/* Data              : 5 Feb 2024                                                                       */
/* Description       : HULTRA_SONIC_Prog.c --> implementations                                          */
/* Module  Features  :																					*/
/* @Functions:																							*/
/*      01- HULTRA_vInitialize                                                                          */
/*      02- HULTRA_vSendTrigger                                                                         */
/*      03- HULTRA_vGetDistance																			*/
/* @TypeDef:																							*/
/* 		@Enums:																							*/
/* 	    	 01- Enum_ULTRA_SONIC_NUM                                                        			*/
/********************************************************************************************************/

#include "../../MCAL/MRCC/MRCC_Int.h"   // MRCC: Reset and Clock Control driver
#include "../../MCAL/MGPIO/MGPIO_Int.h" // MGPIO: General Purpose Input/Output driver
#include "../../MCAL/MTIMER/MTIMER_Int.h" // MTIMER: Timer driver
#include "../../MCAL/MSTK/MSYSTICK_Int.h" // MSTK: SysTick timer driver

#include "HULTRA_SONIC_Config.h" // Configuration header for the Ultrasonic Sensor
#include "HULTRA_SONIC_Int.h"    // Interface header for the Ultrasonic Sensor


// Definition of a structure to hold Ultrasonic Sensor information
typedef struct {
    Enum_TIMER_NUM TIMER;
    Enum_TIMER_CHs CHANNELS;
} LOC_ULTRA_NUM;

// Array to store information for multiple Ultrasonic Sensors
LOC_ULTRA_NUM ULTRA_STRUCT[TOT_ULTRA_SONIC_NUM];


void HULTRA_vInitialize(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,Enum_TIMER_NUM Copy_u8TimerNum, u8 Copy_u8ChannelNum)
{	// Configure GPIO pins and alternative functions based on the selected timer and channel
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
	ULTRA_STRUCT[Copy_u8Ultra_NUM].TIMER = Copy_u8TimerNum;
	ULTRA_STRUCT[Copy_u8Ultra_NUM].CHANNELS = Copy_u8ChannelNum;

}


void HULTRA_vSendTrigger(u8 Copy_u8Port, u8 Copy_u8Pin) {
    // Set the ultrasonic sensor trigger pin as OUTPUT
    MGPIO_vSetPinMode(Copy_u8Port, Copy_u8Pin, OUTPUT);

    // Raise the ultrasonic sensor trigger pin to HIGH for a short duration
    MGPIO_vSetPinAtomic(Copy_u8Port, Copy_u8Pin, HIGH);
    MSYSTICK_vDelayms(Trigger_Pulse_Width);  // Wait for "Trigger_Pulse_Width" milliseconds

    // Bring the ultrasonic sensor trigger pin back to LOW
    MGPIO_vSetPinAtomic(Copy_u8Port, Copy_u8Pin, LOW);
}


void HULTRA_vGetDistance(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,f64* Copy_f64Distance) {
    // Calculate distance based on timer values and assume speed of sound is 343 meters per second
    *Copy_f64Distance = ((f64)MTIMER_GET_ICU(ULTRA_STRUCT[Copy_u8Ultra_NUM].TIMER, ULTRA_STRUCT[Copy_u8Ultra_NUM].CHANNELS) / 2) * 3.43;
}




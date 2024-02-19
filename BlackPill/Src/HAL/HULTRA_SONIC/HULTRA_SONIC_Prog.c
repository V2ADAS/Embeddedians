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
	MGPIO_vSetPinMode(
			TIMER_PORT_MAP[Copy_u8TimerNum - 1][Copy_u8ChannelNum - 1],
			TIMER_PIN_MAP[Copy_u8TimerNum - 1][Copy_u8ChannelNum - 1],
			ALTFUNC
	);

	MGPIO_vSetAlternativeFunction(
			TIMER_PORT_MAP[Copy_u8TimerNum - 1][Copy_u8ChannelNum - 1],
			TIMER_PIN_MAP[Copy_u8TimerNum - 1][Copy_u8ChannelNum - 1],
			TIMER_AF[Copy_u8TimerNum - 1]
	);

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




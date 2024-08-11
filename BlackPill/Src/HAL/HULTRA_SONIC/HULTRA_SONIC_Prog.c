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
#include "../../MCAL/MGPIO/MGPIO_int.h" // MGPIO: General Purpose Input/Output driver
#include "../../MCAL/MTIMER/MTIMER_Int.h" // MTIMER: Timer driver
#include "../../MCAL/MSTK/MSYSTICK_Int.h" // MSTK: SysTick timer driver

#include "HULTRA_SONIC_Config.h" // Configuration header for the Ultrasonic Sensor
#include "HULTRA_SONIC_Int.h"    // Interface header for the Ultrasonic Sensor

//Car positioned ultrasonics struct
UltraSonics_STRUCT UltraSonics_ST;

// Definition of a structure to hold Ultrasonic Sensor information
typedef struct {
	Enum_TIMER_NUM TIMER;
	Enum_TIMER_CHs CHANNELS;
} LOC_ULTRA_NUM;

// Array to store information for multiple Ultrasonic Sensors
LOC_ULTRA_NUM ULTRA_STRUCT[TOT_ULTRA_SONIC_NUM];

void LOC_ContTrigger(void);
void HULTRA_vInitialize(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM, Enum_TIMER_NUM Copy_u8TimerNum, u8 Copy_u8ChannelNum)
{
    // Initialize the Input Capture Unit (ICU) of the specified timer and channel
    MTIMER_vICU(Copy_u8TimerNum, Copy_u8ChannelNum);

    // Store the timer number and channel number in the ultrasonic sensor structure
    ULTRA_STRUCT[Copy_u8Ultra_NUM].TIMER = Copy_u8TimerNum;
    ULTRA_STRUCT[Copy_u8Ultra_NUM].CHANNELS = Copy_u8ChannelNum;
}

u16 Gl_TriggerPulseMicro=0,Gl_OffTime=0;
u8 Gl_TriggerPort=0,Gl_TriggerPin=0;
void HULTRA_vInitContTrigger(Enum_TIMER_NUM Copy_u8TimerNum,u16 Copy_u16TriggerPulseMicro,u16 Copy_u16OffTime,u8 Copy_u8Port, u8 Copy_u8Pin){
	MGPIO_vSetPinMode(Copy_u8Port, Copy_u8Pin, OUTPUT);
	u16 Total_time = Copy_u16TriggerPulseMicro + Copy_u16OffTime * Copy_u16TriggerPulseMicro;
	Gl_TriggerPort = Copy_u8Port;
	Gl_TriggerPin = Copy_u8Pin;
	Gl_OffTime = Copy_u16OffTime;
	MTIMER_vPeriodicMicro(Copy_u8TimerNum, Total_time);
	MTIMER_CallBack(Copy_u8TimerNum, LOC_ContTrigger);
}


void HULTRA_vSendTrigger(u8 Copy_u8Port, u8 Copy_u8Pin) {
	// Set the ultrasonic sensor trigger pin as OUTPUT
	MGPIO_vSetPinMode(Copy_u8Port, Copy_u8Pin, OUTPUT);

	// Raise the ultrasonic sensor trigger pin to HIGH for a short duration
	MGPIO_vSetPinAtomic(Copy_u8Port, Copy_u8Pin, HIGH);
//	MSYSTICK_vDelayMicroSec(Trigger_Pulse_Width);  // Wait for "Trigger_Pulse_Width" microseconds
	for (int i = 0; i < 10000; ++i);
//	MSYSTICK_vDelayms(30);
	// Bring the ultrasonic sensor trigger pin back to LOW
	MGPIO_vSetPinAtomic(Copy_u8Port, Copy_u8Pin, LOW);
}

void LOC_ContTrigger(void){
	static u8 period = 0;
	if(period == 0)
		MGPIO_vSetPinAtomic(Gl_TriggerPort, Gl_TriggerPin, HIGH);
	else if (period == 1)
		MGPIO_vSetPinAtomic(Gl_TriggerPort, Gl_TriggerPin, LOW);
	else if (period == (Gl_OffTime+1) ){
		HULTRA_vGetDistance(US_RF, &UltraSonics_ST.RF);
		HULTRA_vGetDistance(US_CF, &UltraSonics_ST.CF);
		HULTRA_vGetDistance(US_LF, &UltraSonics_ST.LF);

		HULTRA_vGetDistance(US_RC, &UltraSonics_ST.RC);
		HULTRA_vGetDistance(US_LC, &UltraSonics_ST.LC);

		HULTRA_vGetDistance(US_RB, &UltraSonics_ST.RB);
		HULTRA_vGetDistance(US_CB, &UltraSonics_ST.CB);
		HULTRA_vGetDistance(US_LB, &UltraSonics_ST.LB);
	}
	period = (period+1)%(Gl_OffTime+2);
}



void HULTRA_vGetDistance(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,f32* Copy_f32Distance) {
	// Calculate distance based on timer values and assume speed of sound is 343 meters per second
	*Copy_f32Distance = ( (f32)MTIMER_GET_ICU(ULTRA_STRUCT[Copy_u8Ultra_NUM].TIMER, ULTRA_STRUCT[Copy_u8Ultra_NUM].CHANNELS) ) * 3.43 / 20;
}









#include "HMOTOR.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/MGPIO/MGPIO_Int.h"
#include "../../MCAL/MGPIO/MGPIO_Config.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"
#include"../../MCAL/MEXTI/MEXTI_int.h"
#include"../../MCAL/MNVIC/MNVIC_int.h"
#include"../../MCAL/MSTK/MSYSTICK_int.h"
#include"../../APP/Inc/Motion_Planing.h"
#define WHEEL_AREA   26
#define PULSES_PER_REVOLUTION 1024

volatile MOTOR_PINS_t Motor_Pins ;
volatile u32 encoder_pulses = 0 ;
volatile u32 moved_distance_pulses = 0 ;
volatile u32 target_distance_pulses = 0 ;

//void Increment_Pulse_CallBack(){
//	encoder_pulses++ ;
//	moved_distance_pulses++ ;
//	if (!(encoder_pulses % 38))
//	{
//		MP_PaB_Scan();
//	}
//	if (target_distance_pulses <= moved_distance_pulses){
//		HAL_MOTOR_STOP();
//	}
//}





void HAL_MOTOR_Init(u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 , Enum_TIMER_NUM PWM_TIMER , Enum_TIMER_CHs PWM_CH){
	Motor_Pins.PORT_N1  = PORT_N1 	;
	Motor_Pins.PORT_N2  = PORT_N2 	;
	Motor_Pins.PWM_TIMER = PWM_TIMER  ;
	Motor_Pins.PIN_N1 	 = PIN_N1	;
	Motor_Pins.PIN_N2 	 = PIN_N2	;
	Motor_Pins.PWM_CH  = PWM_CH	;
	MGPIO_vSetPinMode(PORT_N1, PIN_N1, OUTPUT);
	MGPIO_vSetPinMode(PORT_N2, PIN_N2, OUTPUT);
}

void HAL_ENCODER_Init( Enum_TIMER_NUM CNTR_TIMER , Enum_TIMER_CHs CNTR_CH ){
	Motor_Pins.CNTR_TIMER = CNTR_TIMER ;
	Motor_Pins.CNTR_CH = CNTR_CH ;
	MNVIC_vEnableInterrupt(NVIC_TIM5);
}

void HAL_MOTOR_MOVE(u8 DIRCTION ,u8 SPEED , f32 DISTANCE_cm_){
	f32 high_duty = (SPEED / 100.0)  ;
	f32 num_of_revolutions  ;
	moved_distance_pulses = 0 ;
	target_distance_pulses = 0 ;
	switch(DIRCTION){
	case BACKWARD :
		MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, HIGH);
		MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, LOW);
		break;
	case FORWARD:
		MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, LOW);
		MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, HIGH);
		break;
	}
	/****************************speed********************************/
	MTIMER_vPWM(Motor_Pins.PWM_TIMER, Motor_Pins.PWM_CH, 10000, high_duty*10000);
	/***************************distance******************************/
	num_of_revolutions = (DISTANCE_cm_/ WHEEL_AREA);
	target_distance_pulses = (u32)(num_of_revolutions * PULSES_PER_REVOLUTION);
	MTIMER_vEXTCNTClock(Motor_Pins.CNTR_TIMER, Motor_Pins.CNTR_CH , target_distance_pulses );
	MTIMER_CallBack(Motor_Pins.CNTR_TIMER,HAL_MOTOR_STOP );
}

void HAL_MOTOR_STOP(){
	MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, LOW);
	MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, LOW);
}

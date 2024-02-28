
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/MGPIO/MGPIO_Int.h"
#include "../../MCAL/MGPIO/MGPIO_Config.h"
#include "HMOTOR.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"
#include"../../MCAL/MEXTI/MEXTI_int.h"
#include"../../MCAL/MSTK/MSYSTICK_int.h"

#define WHEEL_AREA   26.4
#define PULSES_PER_REVOLUTION 1024

volatile MOTOR_PINS_t Motor_Pins ;
volatile u32 encoder_pulses = 0 ;
volatile u32 temp_pulses = 0 ;
void Increment_Pulse_CallBack(){
	encoder_pulses++ ;
	temp_pulses++ ;
	if (!(encoder_pulses % 38))
	{
		MP_PaB_Scan();
	}
}



void HAL_MOTOR_Init(u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 ,u8 PORT_PWM ,
		u8 PIN_PWM, u8 PWM_TIMER , u8 ENCODER_EXTIx ,u8 NVIC_EXTIx){
	Motor_Pins.PORT_N1  = PORT_N1 	;
	Motor_Pins.PORT_N2  = PORT_N2 	;
	Motor_Pins.PORT_PWM = PORT_PWM  ;
	Motor_Pins.PIN_N1 	 = PIN_N1	;
	Motor_Pins.PIN_N2 	 = PIN_N2	;
	Motor_Pins.PIN_PWM  = PIN_PWM	;
	MGPIO_vSetPinMode(PORT_N1, PIN_N1, OUTPUT);
	MGPIO_vSetPinMode(PORT_N2, PIN_N2, OUTPUT);
	MGPIO_vSetPinMode(PORT_PWM, PIN_PWM,ALTFUNC);
	MGPIO_vSetAlternativeFunction(PORT_PWM, PIN_PWM,PWM_TIMER);

	/********************Interrupt of encoder*****************************/
	MEXTI_vEnableInterrupt(ENCODER_EXTIx);
	MEXTI_vInterruptTrigger(ENCODER_EXTIx, RISING);
	SYSCFG_vConfigEXTI_Line(EXTI_PORTB, ENCODER_EXTIx);
	MEXTI_vCallBack(ENCODER_EXTIx, Increment_Pulse_CallBack);
	MNVIC_vEnableInterrupt(NVIC_EXTIx);
}


void HAL_MOTOR_MOVE(u8 DIRCTION ,u8 SPEED , f32 DISTANCE_cm_){
	f32 high_duty = (SPEED / 100.0)  ;
	f32 num_of_revolutions  ;
	u32 total_pulses = 0 ;
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
	MTIMER_vPWM(TIMER1, CH1, 10000, high_duty*10000);
	/***************************distance******************************/
	num_of_revolutions = (DISTANCE_cm_/ WHEEL_AREA);
//	num_of_revolutions = 4;
	total_pulses = (u32)(num_of_revolutions * PULSES_PER_REVOLUTION);
		while( total_pulses > temp_pulses );
		HAL_MOTOR_STOP();
		temp_pulses = 0 ;
}

void HAL_MOTOR_STOP(){
	MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, LOW);
	MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, LOW);
}

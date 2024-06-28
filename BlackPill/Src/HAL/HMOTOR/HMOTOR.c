#include "HMOTOR.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/MGPIO/MGPIO_int.h"
#include "../../MCAL/MGPIO/MGPIO_Config.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"
#include"../../MCAL/MEXTI/MEXTI_Int.h"
#include"../../MCAL/MNVIC/MNVIC_int.h"
#include"../../MCAL/MSTK/MSYSTICK_Int.h"
#include"../../APP/Inc/Motion_Planing.h"
#include "../../APP/Inc/Odometry.h"

MOTOR_t DC_Motor ;
MOTOR_t CALP_Motor ;

ENCODER_t Encoder ;
u32 encoder_pulses = 0 ;
f64 moved_distance = 0 ;
f64 total_moved_distance = 0 ;

/*****************************Local Functions***********************************/
MOTOR_t* LOC_GetMotorName(u8 MOTOR);

void LOC_MotorCallBack();


//void Increment_Pulse_CallBack(){
//	moved_distance_pulses++ ;
//	if (!(encoder_pulses % 38))
//	{
//		MP_PaB_Scan();
//	}
//	if (target_distance_pulses <= moved_distance_pulses){
//		HAL_MOTOR_STOP();
//	}
//}





void HAL_MOTOR_Init(u8 MOTOR , u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 , Enum_TIMER_NUM PWM_TIMER , Enum_TIMER_CHs PWM_CH){
	MOTOR_t *Motor = LOC_GetMotorName(MOTOR);

	Motor->PORT_N1  = PORT_N1 	;
	Motor->PORT_N2  = PORT_N2 	;
	Motor->PWM_TIMER= PWM_TIMER;
	Motor->PIN_N1 	= PIN_N1	;
	Motor->PIN_N2 	= PIN_N2	;
	Motor->PWM_CH  = PWM_CH	;
	MGPIO_vSetPinMode(PORT_N1, PIN_N1, OUTPUT);
	MGPIO_vSetPinMode(PORT_N2, PIN_N2, OUTPUT);
}

void HAL_ENCODER_Init( Enum_TIMER_NUM CNTR_TIMER , Enum_TIMER_CHs CNTR_CH ){
	Encoder.CNTR_TIMER = CNTR_TIMER ;
	Encoder.CNTR_CH = CNTR_CH ;
	MNVIC_vEnableInterrupt(NVIC_TIM5);
}

void HAL_MOTOR_MOVE(u8 MOTOR , u8 DIRCTION ,u8 SPEED ){

	MOTOR_t *Motor = LOC_GetMotorName(MOTOR);

	f32 high_duty = (SPEED / 100.0)  ;
	f32 num_of_revolutions  ;
	u32 target_distance_pulses = 0 ;

	switch(DIRCTION){
	case BACKWARD :
		MGPIO_vSetPinValue(Motor->PORT_N1, Motor->PIN_N1, HIGH);
		MGPIO_vSetPinValue(Motor->PORT_N2, Motor->PIN_N2, LOW);
		break;
	case FORWARD:
		MGPIO_vSetPinValue(Motor->PORT_N1, Motor->PIN_N1, LOW);
		MGPIO_vSetPinValue(Motor->PORT_N2, Motor->PIN_N2, HIGH);
		break;
	}
	/****************************speed********************************/
	MTIMER_vPWM(Motor->PWM_TIMER, Motor->PWM_CH, 10000, high_duty*10000);

	/****************************distance*****************************/
//	num_of_revolutions = (DISTANCE_cm_/ WHEEL_AREA);
//	target_distance_pulses = (u32)(num_of_revolutions * PULSES_PER_REVOLUTION);
//	MTIMER_vEXTCNTClock(Encoder.CNTR_TIMER, Encoder.CNTR_CH , 65000 );
//	moved_distance = DISTANCE_cm_ ;
//	MTIMER_CallBack(Encoder.CNTR_TIMER,LOC_MotorCallBack );


}

void HAL_MOTOR_ForceStop(u8 MOTOR){
	MOTOR_t *Motor = LOC_GetMotorName(MOTOR);

	MGPIO_vSetPinValue(Motor->PORT_N1, Motor->PIN_N1, LOW);
	MGPIO_vSetPinValue(Motor->PORT_N2, Motor->PIN_N2, LOW);
}

void HAL_MOTOR_StopDcAfterDistance(f32 DISTANCE_cm_){
	f32 num_of_revolutions  ;
	u32 target_distance_pulses = 0 ;

	num_of_revolutions = (DISTANCE_cm_/ WHEEL_AREA);
	target_distance_pulses = (u32)(num_of_revolutions * PULSES_PER_REVOLUTION);
	MTIMER_vEXTCNTClock(Encoder.CNTR_TIMER, Encoder.CNTR_CH , target_distance_pulses );
	moved_distance = DISTANCE_cm_ ;
	MTIMER_CallBack(Encoder.CNTR_TIMER,LOC_MotorCallBack );

}


f64 HAL_MOTOR_GetMovedDistance(){
	u32 moved_distance_pulses = MTIMER_u32GetElapsedTicks(Encoder.CNTR_TIMER);
	f64 num_of_revolutions = (f64) moved_distance_pulses / PULSES_PER_REVOLUTION ;
	f64 moved_distance_cm = num_of_revolutions * WHEEL_AREA ;
	return total_moved_distance + moved_distance_cm ;
}
void LOC_MotorCallBack(){
	HAL_MOTOR_ForceStop(DC_MOTOR);
	total_moved_distance += moved_distance ;
	Update_Odometry();
}

MOTOR_t* LOC_GetMotorName(u8 MOTOR){
	MOTOR_t *Motor ;
	switch (MOTOR) {
	case DC_MOTOR:
		Motor = &DC_Motor ;
		break;
	case CALP_MOTOR:
		Motor = &CALP_Motor ;
		break;
	default:
		break;
	}
	return Motor ;
}




#include "../../MCAL/MGPIO/MGPIO_Int.h"
#include "../../MCAL/MGPIO/MGPIO_Config.h"
#include "HMOTOR.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"


volatile MOTOR_PINS_t Motor_Pins ;

void HAL_MOTOR_Init(u8 PORT_N1 , u8 PIN_N1, u8 PORT_N2 , u8 PIN_N2 ,u8 PORT_PWM , u8 PIN_PWM){
	Motor_Pins.PORT_N1  = PORT_N1 	;
	Motor_Pins.PORT_N2  = PORT_N2 	;
	Motor_Pins.PORT_PWM = PORT_PWM  ;
	Motor_Pins.PIN_N1 	 = PIN_N1	;
	Motor_Pins.PIN_N2 	 = PIN_N2	;
	Motor_Pins.PIN_PWM  = PIN_PWM	;
	MGPIO_vSetPinMode(PORT_N1, PIN_N1, OUTPUT);
	MGPIO_vSetPinMode(PORT_N2, PIN_N2, OUTPUT);
	MGPIO_vSetPinMode(PORT_PWM, PIN_PWM,ALTFUNC);
	MGPIO_vSetAlternativeFunction(PORT_PWM, PIN_PWM, MGPIO_ALTFUNC_TIM12);
}


void HAL_MOTOR_MOVE(u8 DIRCTION ,u8 SPEED ){
	switch(DIRCTION){
	case FORWARD :
		MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, HIGH);
		MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, LOW);
		break;
	case BACKWARD:
		MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, LOW);
		MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, HIGH);
		break;
	}

	MTIMER_vPWM(TIMER1,CH1, 10000,10000);
}


void HAL_MOTOR_STOP(){
	MGPIO_vSetPinValue(Motor_Pins.PORT_N1, Motor_Pins.PIN_N1, LOW);
	MGPIO_vSetPinValue(Motor_Pins.PORT_N2, Motor_Pins.PIN_N2, LOW);
}


void increment_pulse(){
//	x++;b
}

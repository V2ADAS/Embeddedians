
#include"MCAL/MRCC/MRCC_int.h"
#include"MCAL/MGPIO/MGPIO_int.h"
#include"MCAL/MNVIC/MNVIC_int.h"
#include"MCAL/MEXTI/MEXTI_int.h"
#include"MCAL/MEXTI/MEXTI_config.h"
#include"MCAL/MEXTI/MEXTI_Private.h"
#include"MCAL/MIWDT/MIWDT_int.h"
#include"MCAL/MSTK/MSYSTICK_int.h"
#include"MCAL/MSPI/MSPI_int.h"
#include"MCAL/MRCC/MRCC_private.h"
#include"MCAL/MUART/MUSART_Interface.h"
#include"MCAL/MUART/MUSART_Config.h"
#include"MCAL/MUART/MUSART_Private.h"
#include"HAL/HMOTOR/HMOTOR.h"
#include"HAL/HSERVO/HSERVO_Int.h"
#include "MCAL/MTIMER/MTIMER_Int.h"


#define SCB_CPACR       (*((volatile u32 *)0xE000ED88))


int main (void){

	SCB_CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
	MRCC_vInit();
	MRCC_vEnableClock(GPIOA_EN);
	MRCC_vEnableClock(GPIOB_EN);
	MRCC_vEnableClock(GPIOC_EN);
	MRCC_vEnableClock(SYSCFG_EN);
	MRCC_vEnableClock(USART1_EN);
	MRCC_vEnableClock(USART2_EN);
	MRCC_vEnableClock(USART6_EN);
	MRCC_vEnableClock(TIM1_EN);
	/**/


	//*************************test*******************************
	MGPIO_vSetPinMode(PORTC, PIN13, OUTPUT);
	MGPIO_vSetPinValue(PORTC, PIN13, LOW);
	//********************************************************

	//***************************Motor*****************************
	HAL_MOTOR_Init(PORTA, PIN1, PORTA, PIN2, PORTA, PIN8,
	MGPIO_ALTFUNC_TIM12, EXTI8,NVIC_EXTI9_5);
	HAL_MOTOR_STOP();
	/***********************************************************************/
	/****************switch***************************/
	MGPIO_vSetPinMode(PORTB, PIN4, INPUT);
	MGPIO_vSetPinValue(PORTB, PIN4, LOW);
	/*******************************Servo***********************************/
//
//	if(MGPIO_u8GetPinValue(PORTB, PIN4)){
		HSERVO_vServoInit(SERVO1, TIMER1, CH3);
		HSERVO_vServoDeg(SERVO1, 0);
		HAL_MOTOR_MOVE(FORWARD, 70 , 100);
		HSERVO_vServoDeg(SERVO1, -30);
		HAL_MOTOR_MOVE(BACKWARD, 50 , 60);
		HSERVO_vServoDeg(SERVO1, 30);
		HAL_MOTOR_MOVE(BACKWARD, 50 , 60);
		HSERVO_vServoDeg(SERVO1, 0);
		HAL_MOTOR_MOVE(FORWARD, 50 , 30);
//	}
	while(1){
		//		HSERVO_vServoDeg(SERVO1, 30);
		//		MSYSTICK_vDelayms(100);
		//		HSERVO_vServoDeg(SERVO1, -30);
		//		MSYSTICK_vDelayms(100);
	}

}


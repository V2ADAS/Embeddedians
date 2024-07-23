#include "LIB/STD_TYPES.h"
#include <stdio.h>
#include <string.h>
#include "LIB/BIT_MATH.h"
#include "math.h"

#include "MCAL/MRCC/MRCC_Int.h"
#include "MCAL/MFPU/MFPU_Int.h"
#include "MCAL/MSTK/MSYSTICK_Int.h"
#include "MCAL/MGPIO/MGPIO_int.h"
#include "MCAL/MTIMER/MTIMER_Int.h"
#include "MCAL/MNVIC/MNVIC_int.h"
#include "MCAL/MEXTI/MEXTI_Int.h"
#include "MCAL/MIWDT/MIWDT_int.h"
#include "MCAL/MSPI/MSPI_int.h"
#include "MCAL/MI2C/MI2C_int.h"
#include "MCAL/MUART/MUSART_Interface.h"


#include "HAL/HLCD/HLCD_Int.h"
#include "HAL/HSERVO/HSERVO_Int.h"
#include "HAL/HMOTOR/HMOTOR.h"
#include "HAL/HMPU/HMPU6050.h"
#include "HAL/HCOMPASS/HAL_COMPASS.h"
#include "HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"
#include "APP/Inc/Auto_Parking.h"
#include "APP/Inc/Motion_Planing.h"
#include "APP/Inc/Path_Tracking.h"
#include "APP/Inc/Odometry.h"
#include "APP/Inc/Car_Control.h"
#include "APP/Inc/MoveBack.h"

//Internal_Data_ST internal ;

void HAL_Init();
void System_Clock_Init();
void Interrupt_Init();

typedef struct{
	u8 start ;

	u16 US_RightForward ;
	u16 US_CenterForward ;
	u16 US_LeftForward ;
	u16 US_RightCenter ;
	u16 US_LeftCenter ;
	u16 US_RightBackward ;
	u16 US_CenterBackward ;
	u16 US_LeftBackward ;

	u32 TotalMovedDistance ;

	s16 Yaw_Compass ;
	s16 Yaw_MPU ;

	f32 var1 ;
	f32 var2 ;
	f32 var3 ;
	f32 var4 ;
	f32 var5 ;
}Data_ST ;

Data_ST Tx = {'*' , 50 , 199 ,0 ,1,10, 20, 30, 40, 50, -991, -70, 80.99, 90,11.11,80.8,999.9};
Data_ST Rx = {0};
u8 * Rx_ptr = (u8*)&Rx ;


u8 *ptr = (u8*)&Tx ;
u8 size = sizeof(Tx);

s8 Steering_tx = 0;	u8 data_rx ;
void RX_Callback()
{
	data_rx = MUART_Receive_Data(UART1);
//	if (data_rx == '*')
//		Rx_ptr = (u8*)&Rx ;
//	*Rx_ptr = data_rx ;
//	Rx_ptr++;
	if (data_rx == 'f' ){
		HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 50);
	}
	else if (data_rx == 'b' ){
		HAL_MOTOR_MOVE(DC_MOTOR, BACKWARD, 50);
	}
	else if (data_rx == 's' ){
		HAL_MOTOR_ForceStop(DC_MOTOR);
	}
	else {
		Steering_tx = data_rx - 41 ;
		HSERVO_vServoDeg(SERVO1, Steering_tx);
	}
}

void EXTI_CAll(){
	MUART_Send_Data(UART1, ptr  ,size );
}


int main (void){

	MFPU_Enable();
	System_Clock_Init();
	Interrupt_Init();
	HAL_Init();
	//***********************************************************
	//CarControl_SetEncoderCallBack();


	//*************************test*******************************
	MGPIO_vSetPinMode(PORTC, PIN13, OUTPUT);
	MGPIO_vSetPinValue(PORTC, PIN13, LOW);

	//*************************run key******************************************

	MUART_Init(UART1);
	MUART_vSetRxCallBackFunc(UART1, RX_Callback);



	MGPIO_vSetPinMode(PORTA, PIN0, INPUT);
	MGPIO_vSetPinInPutType(PORTA, PIN0, PULLUP);

	MNVIC_vEnableInterrupt(NVIC_EXTI0);

	SYSCFG_vConfigEXTI_Line(EXTI_PORTA, EXTI0);
	MEXTI_vInterruptTrigger(EXTI0, FALLING);
	MEXTI_vEnableInterrupt(EXTI0);
	MEXTI_vCallBack(EXTI0, &EXTI_CAll);


	MUART_Enable(UART1);
	//	 HSERVO_vServoDeg(SERVO1, 0);
	//	 HAL_MOTOR_MOVE(DC_MOTOR,FORWARD, 70 );
	//	 HAL_MOTOR_StopDcAfterDistance(70);
	//	 	 while (HAL_MOTOR_GetMovedDistance() <= 70);
	//
	//	 MSYSTICK_vDelayms(2000);
	//
	//	 HSERVO_vServoDeg(SERVO1, 0);
	//	 HAL_MOTOR_MOVE(DC_MOTOR,FORWARD, 70 );
	//	 HAL_MOTOR_StopDcAfterDistance(70);

	//
	//	 HSERVO_vServoDeg(SERVO1, -40);
	//	 HAL_MOTOR_MOVE(DC_MOTOR,BACKWARD, 50 );
	//	 HAL_MOTOR_StopDcAfterDistance(50);
	//	 while (HAL_MOTOR_GetMovedDistance() <= 150);
	//
	//	 HSERVO_vServoDeg(SERVO1, 0);
	//	 HAL_MOTOR_MOVE(DC_MOTOR,BACKWARD, 50 );
	//	 HAL_MOTOR_StopDcAfterDistance(20);
	//	 while (HAL_MOTOR_GetMovedDistance() <= 170);
	//
	//	 HSERVO_vServoDeg(SERVO1, 40);
	//	 HAL_MOTOR_MOVE(DC_MOTOR,BACKWARD, 50 );
	//	 HAL_MOTOR_StopDcAfterDistance(50);
	//	 while (HAL_MOTOR_GetMovedDistance() <= 220);
	//
	//	 HSERVO_vServoDeg(SERVO1, 0);
	//	 HAL_MOTOR_MOVE(DC_MOTOR,FORWARD, 50 );
	//	 HAL_MOTOR_StopDcAfterDistance(15);
	//	 while (HAL_MOTOR_GetMovedDistance() <= 250);



	//	u8 txt[10] = {'1','2','3','4','5','6','7','8','9','0'};
	//	u8 *ptr = txt;
	//	u8 size = sizeof(txt)/sizeof(txt[0]);
	//MUART_Send_Data(UART1, ptr  ,size );
	while(1){
		//MUART_Send_Data(UART1, ptr  ,size );
		MGPIO_vSetPinValue(PORTC, PIN13, HIGH);
		MSYSTICK_vDelayms(500);
		MGPIO_vSetPinValue(PORTC, PIN13, LOW);
		MSYSTICK_vDelayms(500);
		Tx.US_LeftForward++;
		Tx.Yaw_MPU++;
	}

}


void System_Clock_Init(){
	MRCC_vInit();
	MRCC_vEnableClock(GPIOA_EN);
	MRCC_vEnableClock(GPIOB_EN);
	MRCC_vEnableClock(GPIOC_EN);
	MRCC_vEnableClock(SYSCFG_EN);
	MRCC_vEnableClock(USART1_EN);
	MRCC_vEnableClock(USART2_EN);
	MRCC_vEnableClock(USART6_EN);
	MRCC_vEnableClock(TIM1_EN);
	MRCC_vEnableClock(TIM2_EN);
	MRCC_vEnableClock(TIM3_EN);
	MRCC_vEnableClock(TIM4_EN);
	MRCC_vEnableClock(TIM5_EN);
	MRCC_vEnableClock(TIM9_EN);
	MRCC_vEnableClock(TIM10_EN);
	MRCC_vEnableClock(TIM11_EN);
	MRCC_vEnableClock(I2C1_EN);
}
void Interrupt_Init(){
	MNVIC_vEnableInterrupt(NVIC_TIM1_CC);
	MNVIC_vEnableInterrupt(NVIC_TIM1_UP_TIM10);
	MNVIC_vEnableInterrupt(NVIC_TIM2);
	MNVIC_vEnableInterrupt(NVIC_TIM3);
	MNVIC_vEnableInterrupt(NVIC_TIM4);
	MNVIC_vEnableInterrupt(NVIC_TIM1_BRK_TIM9);
	MNVIC_vEnableInterrupt(NVIC_TIM5);
	MNVIC_vInitGrouping(GP16SUB0);
	//MNVIC_vSetIntPriority(NVIC_TIM1_UP_TIM10, GP15, SUB0);
	//MNVIC_vSetIntPriority(NVIC_TIM3, GP1, SUB0);
	//MNVIC_vSetIntPriority(NVIC_EXTI9_5, GP9, SUB0);
	MNVIC_vEnableInterrupt(NVIC_EXTI1);
	MEXTI_vEnableInterrupt(EXTI1);
	MEXTI_vCallBack(EXTI1, LCD_Display);

}
void HAL_Init(){
	HAL_MOTOR_Init(DC_MOTOR,PORTB, PIN13, PORTB, PIN14, TIMER11, CH1);//PWM ON B9

	HAL_ENCODER_Init(TIMER1,CH1); // A8
	HSERVO_vServoInit(SERVO1, TIMER10, CH1);
	HULTRA_vInitialize(ULTRA_SONIC1, TIMER3, CH4);
	HCOMPASS_vInit();
	HLCD_vInit();
	MSYSTICK_vDelayms(100);
	HMPU_vInit(TIMER9);
}



//		static flg =0;
//		if(s>60&&!flg){
//			MSYSTICK_vDelayms(2000);
//			flg=1;
//			CarControl_Move(FORWARD, 38.25, -30, 70);
//		}
//		if(s>100&&flg==1){
//			MSYSTICK_vDelayms(2000);
//			flg=2;
//			CarControl_Move(FORWARD, 25.5, 20, 70);
//		}
//************************* Basmagaaaaaa *****************************************/
//	MSYSTICK_vDelayms(20000);
//	CarControl_Move(FORWARD, 50, 0, 50);
//	while (HAL_MOTOR_GetMovedDistance() <= 50);
//	//sign 100
//	CarControl_Move(FORWARD, 500, 0, 100);
//	while (HAL_MOTOR_GetMovedDistance() <= 100);
//	//sign 80
//	CarControl_Move(FORWARD, 500, 0, 30);
//	while (HAL_MOTOR_GetMovedDistance() <= 200);

//	HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 30);
//	while (HAL_MOTOR_GetMovedDistance() <= 300);
//sign 50
//	CarControl_Move(FORWARD, 150, 0, 50);
//	while (HAL_MOTOR_GetMovedDistance() <= 600);
//	//sign 30
//	CarControl_Move(FORWARD, 150, 0, 30);
//	while (HAL_MOTOR_GetMovedDistance() <= 750);


//	 CarControl_Move(FORWARD, 100, 0, 70);
//	 while (HAL_MOTOR_GetMovedDistance() <= 100);
//	 CarControl_Move(BACKWARD, 60, -40, 50);
//	 while (HAL_MOTOR_GetMovedDistance() <= 150);
//	 CarControl_Move(BACKWARD, 60, 40, 50);
//	 while (HAL_MOTOR_GetMovedDistance() <= 200);
//	 CarControl_Move(FORWARD, 30, 0, 50);
//	 while (HAL_MOTOR_GetMovedDistance() <= 230);



//**************************Basmagaaaaaa *****************************************/
//**************************scan******************************

//	MTIMER_vEXTCNTClock(TIMER5,CH2, 38 );
//	MTIMER_CallBack(TIMER5,MP_PaB_Scan);
//
//	HAL_MOTOR_MOVE(FORWARD, 100 , 100) ;


// HSERVO_vServoDeg(SERVO1, 0);
// HAL_MOTOR_MOVE(DC_MOTOR,FORWARD, 70 , 100);
// HSERVO_vServoDeg(SERVO1, -30);
// HAL_MOTOR_MOVE(BACKWARD, 50 , 60);
// HSERVO_vServoDeg(SERVO1, 30);
// HAL_MOTOR_MOVE(BACKWARD, 50 , 60);
// HSERVO_vServoDeg(SERVO1, 0);
// HAL_MOTOR_MOVE(FORWARD, 50 , 30);

//		x += delta_d * sin(yaw_rad);
//		y += delta_d * cos(yaw_rad);


//		yaw_old = yaw_new ;
//		x_center = x_org + 13.5 * cos(yaw_rad);
//		y_center = y_org - 13.5 * sin(yaw_rad);

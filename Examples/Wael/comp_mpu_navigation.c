#include "LIB/STD_TYPES.h"
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

#include "APP/Inc/Navigation.h"
#include "APP/Inc/Motion_Planing.h"



#define SCB_CPACR  (*((volatile u32 *)0xE000ED88))

void HAL_Init();
void System_Clock_Init();
void Interrupt_Init();

volatile f32 Heading;
f64 	x =0 ,
		y= 0 ,
		x_center ,
		y_center ,
		servo_angle = 10 ,
		steering_error = 10.5,
		L = 32 ,
		BL = 28,
		delta_d,
		R  ,
		R_40 = 63 ,
		R_30 = 80,
		R_20=116.3,
		//		reduc_factor = R_30 / 78 ,
		reduc_factor ,
		area ,
		yaw = 0 ,
		yaw_comp,
		yaw_mpu,
		yaw_rad,
		yaw_arc,
		actual_distance ,
		s = 0 ; // distance moved on circle
void navigate (){

}
u8 wwe=0;

int main (void){
	MFPU_Enable();
	System_Clock_Init();
	Interrupt_Init();
	HAL_Init();


	//*************************test*******************************
	MGPIO_vSetPinMode(PORTC, PIN13, OUTPUT);
	MGPIO_vSetPinValue(PORTC, PIN13, LOW);

	//*************************run key******************************************
	MGPIO_vSetPinMode(PORTA, PIN0, INPUT);
	MGPIO_vSetPinInPutType(PORTA, PIN0, PULLUP);


	//wait for run key

	/*
	do {


	} while(MGPIO_u8GetPinValue(PORTA, PIN0));
	f32 Heading_Ref= HCOMPASS_f32GetHeading();*/
	HMPU_vInit(TIMER9);

	do{
		HCOMPASS_vSetRowData();
		Heading = HCOMPASS_f32GetHeading();

		HLCD_vPutCur(0,6);
		HLCD_vSendNum((u32)Heading);
		HLCD_vSendString("' ");
		MSYSTICK_vDelayms(100);

	}while(MGPIO_u8GetPinValue(PORTA, PIN0));
	f32 Heading_Ref= HCOMPASS_f32GetHeading();

	HMPU_vCalibration(250);
	yaw = HMPU_f32GetYawAngle();
	HLCD_vPutCur(0,12);
	HLCD_vSendNum((f32)yaw);
	HLCD_vSendString("' ");
	MSYSTICK_vDelayms(100);


	R  = ( L / tan((servo_angle-steering_error) *PI/180 ) );

	//	reduc_factor = ( R - (BL/2) ) / ( R ) ;
	//	R = R * reduc_factor ;
	area = 2*PI*R_20 ;
	u8 Q_area = area /4 ;



	HSERVO_vServoDeg(SERVO1, (s8)(2 - servo_angle));
	MSYSTICK_vDelayms(2000);

	u16 distance = 50 ;
	HAL_MOTOR_MOVE( DC_MOTOR , FORWARD , 70 , distance );




	//	HLCD_vPutCur(1,0);
	//	HLCD_vSendString("X:");
	//	HLCD_vPutCur(1,5);
	//	HLCD_vSendString("Y:");




	u8 servo_flag=0;

	while(1){
		//		HLCD_vPutCur(0,0);
		//		HLCD_vSendString("Degree: ");


		HCOMPASS_vSetRowData();
		Heading = HCOMPASS_f32GetHeading();
		yaw_comp = Heading - Heading_Ref ;
		yaw_rad=( (yaw_comp * PI) / 180.0 ) ;
		yaw_mpu = HMPU_f32GetYawAngle(TIMER9)+ s*(5.0/70.0);

		//yaw_rad = ( (yaw_mpu * PI) / 180.0 ) ;
		delta_d += get_delta_distance() * 1 ;
		s = HAL_MOTOR_GetMovedDistance();
		yaw_arc = ((s*360)/area) ;
		//yaw_rad=( (yaw_arc * PI) / 180.0 ) ;

		if (s >= 50 && servo_flag==0) {
			HAL_MOTOR_STOP(DC_MOTOR);
			MSYSTICK_vDelayms(2000);
			HSERVO_vServoDeg(SERVO1, (s8)(2 + servo_angle));
			MSYSTICK_vDelayms(2000);
			servo_flag=1;
			distance=50;
			HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 70, distance);

		}

				/******************************************* delta **********************************************/
				if( delta_d >=  15 * 1000 ){
					x +=  sin(yaw_rad)*delta_d / 1000;
					y +=  cos(yaw_rad)*delta_d / 1000;
					delta_d=0;
				}
				if (distance - s < 15 ) {
					x +=  sin(yaw_rad)*delta_d / 1000;
					y +=  cos(yaw_rad)*delta_d / 1000;
					delta_d=0;
				}
				/******************************************* delta **********************************************/


				//******************** navigate with encoder only **************************



				/************ print x and y  ****************************/
				HLCD_vPutCur(0,0);
				HLCD_vSendNum((u32)yaw_arc);
				HLCD_vSendString("' ");
				HLCD_vPutCur(0,6);
				HLCD_vSendNum((u32)yaw_comp);
				HLCD_vSendString("' ");
				HLCD_vPutCur(0,12);
				HLCD_vSendNum((u32)yaw_mpu);
				HLCD_vSendString("' ");

				HLCD_vPutCur(1,0);
				HLCD_vSendNum(x);
				HLCD_vPutCur(1,5);
				HLCD_vSendString(":");
				//		HLCD_vPutCur(1,7);
				HLCD_vSendNum(y);
				HLCD_vPutCur(1,10);
				HLCD_vSendString(":");

				//	HLCD_vSendNum(delta_d/1000);
				HLCD_vSendNum(s);

				/************ end of print x and y  *********************/
//						if(yaw_mpu>=359){
//							HAL_MOTOR_STOP(DC_MOTOR);
//						}

				//		MSYSTICK_vDelayms(250);
				MGPIO_vSetPinValue(PORTC,PIN13, HIGH);
				//
				//		MSYSTICK_vDelayms(250);
				MGPIO_vSetPinValue(PORTC,PIN13, LOW);
				//				HLCD_vClear();
				//		 MSYSTICK_vDelayms(500);

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
			MNVIC_vEnableInterrupt(NVIC_TIM3);
			MNVIC_vEnableInterrupt(NVIC_TIM4);
			MNVIC_vEnableInterrupt(NVIC_TIM1_BRK_TIM9);
			MNVIC_vEnableInterrupt(NVIC_TIM5);
			MNVIC_vInitGrouping(GP16SUB0);
			MNVIC_vSetIntPriority(NVIC_TIM1_UP_TIM10, GP15, SUB0);
			MNVIC_vSetIntPriority(NVIC_TIM3, GP1, SUB0);
			MNVIC_vSetIntPriority(NVIC_EXTI9_5, GP9, SUB0);
		}
		void HAL_Init(){
			HAL_MOTOR_Init(DC_MOTOR,PORTB, PIN13, PORTB, PIN14, TIMER11, CH1);//PWM ON B9
			//	HAL_MOTOR_Init(CALP_MOTOR,PORTA, PIN11, PORTA, PIN12, TIMER5, CH1); //PWM ON A0

			HAL_ENCODER_Init(TIMER1,CH1); // A8
			HSERVO_vServoInit(SERVO1, TIMER10, CH1);
			HULTRA_vInitialize(ULTRA_SONIC1, TIMER3, CH4);
			HCOMPASS_vInit();
			HLCD_vInit();
		}




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

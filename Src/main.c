
#include "MCAL/MGPIO/MGPIO_Int.h"

#include "MCAL/MRCC/MRCC_Int.h"

#include"MCAL/MEXTI/MEXTI_Int.h"

#include"MCAL/MNVIC/MNVIC_Int.h"

#include"MCAL/MSTK/MSYSTICK_Int.h"

#include"MCAL/MTIMER/MTIMER_Int.h"

#include"HAL/HSERVO/HSERVO_Int.h"

#include"HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"


void Led(void){
	static u8 Tog = 1;
	//Toggle Led
	MGPIO_vSetPinValue(PORTC,PIN13,Tog);
	Tog ^= 1;
}	

void testt(){
	static u8 x = 0;
	HSERVO_vServoDeg(TIMER4, CH4, x);
	x = (x+30)%180;
}

u8 main(){
	//Initialize RCC
	MRCC_vInit();
	//Enable GPIO Clock
	MRCC_vEnableClock(GPIOA_EN);
	MRCC_vEnableClock(GPIOB_EN);
	MRCC_vEnableClock(GPIOC_EN);
	//Enable SYSCFG
	MRCC_vEnableClock(SYSCFG_EN);

	//Initialize SYSTICK
	MSYSTICK_vInit();

	MGPIO_vSetPinMode(PORTA,PIN0,INPUT);
	MGPIO_vSetPinInPutType(PORTA,PIN0,PULLUP);

	//Initialize EXTI
	MNVIC_vEnableInterrupt(NVIC_EXTI0);

	SYSCFG_vConfigEXTI_Line(EXTI_PORTA,EXTI0);
	MEXTI_vEnableInterrupt(EXTI0);
	//Set EXTI0 to RISING
	MEXTI_vInterruptTrigger(EXTI0, FALLING);
	//Set Call Back Function
	MEXTI_vCallBack(EXTI0,&Led);

	//Set LED PIN as OUTPUT
	MGPIO_vSetPinMode(PORTC,PIN13,OUTPUT);

	//OUTPUT LED

	MGPIO_vSetPinMode(PORTA,PIN1,OUTPUT);
	MGPIO_vSetPinMode(PORTA,PIN2,OUTPUT);
	MGPIO_vSetPinMode(PORTA,PIN3,OUTPUT);

	MGPIO_vSetPinMode(PORTA,PIN5,OUTPUT);
	MGPIO_vSetPinMode(PORTA,PIN6,OUTPUT);
	MGPIO_vSetPinMode(PORTA,PIN7,OUTPUT);

	//**************TIMER1**************************//
	MRCC_vEnableClock(TIM1_EN);
	MRCC_vEnableClock(TIM2_EN);
	MRCC_vEnableClock(TIM3_EN);
	MRCC_vEnableClock(TIM4_EN);
	MRCC_vEnableClock(TIM5_EN);

	MRCC_vEnableClock(TIM9_EN);
	MRCC_vEnableClock(TIM10_EN);
	MRCC_vEnableClock(TIM11_EN);

	MNVIC_vEnableInterrupt(NVIC_TIM1_BRK_TIM9);
	MNVIC_vEnableInterrupt(NVIC_TIM1_UP_TIM10);
	MNVIC_vEnableInterrupt(NVIC_TIM1_TRG_COM_TIM11);
	MNVIC_vEnableInterrupt(NVIC_TIM1_CC);
	MNVIC_vEnableInterrupt(NVIC_TIM2);
	MNVIC_vEnableInterrupt(NVIC_TIM3);
	MNVIC_vEnableInterrupt(NVIC_TIM4);
	MNVIC_vEnableInterrupt(NVIC_TIM5);

	HULTRA_vInitialize(TIMER1, CH1);
	HULTRA_vInitialize(TIMER1, CH2);
	HSERVO_vServoInit(TIMER4,CH4);

	MTIMER_vPeriodicMS(TIMER5, 2000);
	MTIMER_CallBack(TIMER5, &testt);

	f64 Distance=0;
	f64 Distance1=0;
	while(1){
		HULTRA_vSendTrigger(PORTB, PIN12);
		HULTRA_vGetDistance(&Distance, TIMER1, CH1);
		HULTRA_vGetDistance(&Distance1, TIMER1, CH2);
		if(Distance<10){
			MGPIO_vSetPinAtomic(PORTA, PIN1, HIGH);
			MGPIO_vSetPinAtomic(PORTA, PIN2, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN3, LOW);
		}
		else if(Distance <20){
			MGPIO_vSetPinAtomic(PORTA, PIN1, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN2, HIGH);
			MGPIO_vSetPinAtomic(PORTA, PIN3, LOW);
		}
		else if(Distance <50){
			MGPIO_vSetPinAtomic(PORTA, PIN1, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN2, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN3, HIGH);
		}
		else{
			MGPIO_vSetPinAtomic(PORTA, PIN1, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN2, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN3, LOW);
		}

		if(Distance1<10){
			MGPIO_vSetPinAtomic(PORTA, PIN5, HIGH);
			MGPIO_vSetPinAtomic(PORTA, PIN6, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN7, LOW);
		}
		else if(Distance1 <20){
			MGPIO_vSetPinAtomic(PORTA, PIN5, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN6, HIGH);
			MGPIO_vSetPinAtomic(PORTA, PIN7, LOW);
		}
		else if(Distance1 <50){
			MGPIO_vSetPinAtomic(PORTA, PIN5, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN6, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN7, HIGH);
		}
		else{
			MGPIO_vSetPinAtomic(PORTA, PIN5, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN6, LOW);
			MGPIO_vSetPinAtomic(PORTA, PIN7, LOW);
		}

	}

}


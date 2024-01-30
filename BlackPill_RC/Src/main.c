
#include "MCAL/MGPIO/MGPIO_Int.h"

#include "MCAL/MRCC/MRCC_Int.h"

#include"MCAL/MEXTI/MEXTI_Int.h"

#include"MCAL/MNVIC/MNVIC_Int.h"

#include"MCAL/MSTK/MSYSTICK_Int.h"

#include"MCAL/MTIMER/MTIMER_Int.h"

#include"HAL/HSERVO/HSERVO_Int.h"



void Led(void){
	static u8 Tog = 1;
	//Toggle Led
	MGPIO_vSetPinValue(PORTC,PIN13,Tog);
	Tog ^= 1;
}



u8 main(){
	//Initialize RCC
	MRCC_vInit();
	//Enable GPIO Clock
	MRCC_vEnableClock(GPIOA_EN);
	MRCC_vEnableClock(GPIOB_EN);
	//Enable SYSCFG
	MRCC_vEnableClock(SYSCFG_EN);

	//Initialize SYSTICK
	MSYSTICK_vInit();






	//Enable GPIO Clock
	MRCC_vEnableClock(GPIOC_EN);
	//Set LED PIN as OUTPUT
	MGPIO_vSetPinMode(PORTC,PIN13,OUTPUT);



	while(1){

		MGPIO_vSetPinValue(PORTC,PIN13, HIGH);
		MSYSTICK_vDelayms(1000);
		MGPIO_vSetPinValue(PORTC,PIN13, LOW);
		MSYSTICK_vDelayms(1000);
	}

}

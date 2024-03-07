
#include "MCAL/MGPIO/MGPIO_Config.h"
#include "MCAL/MGPIO/MGPIO_Private.h"
#include "MCAL/MGPIO/MGPIO_Int.h"

#include "MCAL/MRCC/MRCC_Config.h"
#include "MCAL/MRCC/MRCC_Private.h"
#include "MCAL/MRCC/MRCC_Int.h"

void delay(volatile u32 count){
	while(count--);
}

u8 main(){
	//Initialize RCC
	MRCC_voidInit();
	//Enable GPIO Clock
	MRCC_voidEnableClock(GPIOCEN);
	//Set LED PIN as OUTPUT
	MGPIO_voidSetPinMode(PORTC,PIN13,OUTPUT);
	while(1){
		//Toggle LED
		static u8 Tog = 0;
		Tog ^= 1;
		MGPIO_voidSetPinValue(PORTC,PIN13,Tog);
		//Delay
		delay(1000000);
	}

}

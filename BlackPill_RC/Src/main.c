
#include "MCAL/MGPIO/MGPIO_Int.h"

#include "MCAL/MRCC/MRCC_Int.h"

#include"MCAL/MEXTI/MEXTI_Int.h"

#include"MCAL/MNVIC/MNVIC_Int.h"

#include"MCAL/MSTK/MSYSTICK_Int.h"

#include"MCAL/MTIMER/MTIMER_Int.h"

#include"MCAL/MI2C/MI2C_int.h"

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
	// ENABLE I2C1
	MRCC_vEnableClock(I2C1_EN);
	//MRCC_vEnableClock(I2C2_EN);
	//Initialize SYSTICK
	MSYSTICK_vInit();

	/* I2C 1 Initialization */
	MGPIO_vSetPinMode(PORTB,PIN6,ALTFUNC);
	MGPIO_vSetPinMode(PORTB,PIN7,ALTFUNC);
	//MGPIO_vSetPinOutPutType(PORTB, PIN6, GPIO_PUSH_PULL);
	//MGPIO_vSetPinOutPutType(PORTB, PIN7, GPIO_PUSH_PULL);
	MGPIO_vSetPinOutPutType(PORTB, PIN6, GPIO_OPEN_DRAIN);
	MGPIO_vSetPinOutPutType(PORTB, PIN7, GPIO_OPEN_DRAIN);
	MGPIO_vSetPinOutPutSpeed(PORTB, PIN6, MGPIO_SPEED_HIGH);
	MGPIO_vSetPinOutPutSpeed(PORTB, PIN7, MGPIO_SPEED_HIGH);

	/* I2C 2 Initialization */
	/*MGPIO_vSetPinMode(PORTB,PIN10,ALTFUNC);
	MGPIO_vSetPinMode(PORTB,PIN3,ALTFUNC);
	//MGPIO_vSetPinOutPutType(PORTB, PIN10, GPIO_PUSH_PULL);
	//MGPIO_vSetPinOutPutType(PORTB, PIN3, GPIO_PUSH_PULL);
	MGPIO_vSetPinOutPutType(PORTB, PIN10, GPIO_OPEN_DRAIN);
	MGPIO_vSetPinOutPutType(PORTB, PIN3, GPIO_OPEN_DRAIN);
	MGPIO_vSetPinOutPutSpeed(PORTB, PIN10, MGPIO_SPEED_HIGH);
	MGPIO_vSetPinOutPutSpeed(PORTB, PIN3, MGPIO_SPEED_HIGH);*/

	MGPIO_vSetAlternativeFunction(PORTB, PIN6,MGPIO_ALTFUNC_I2C13);
	MGPIO_vSetAlternativeFunction(PORTB, PIN7,MGPIO_ALTFUNC_I2C13);
	//MGPIO_vSetAlternativeFunction(PORTB, PIN10,MGPIO_ALTFUNC_I2C13);
	//MGPIO_vSetAlternativeFunction(PORTB, PIN3,MGPIO_ALTFUNC_I2C23);

	MGPIO_vSetPinInPutType(PORTB, PIN6, PULLUP);
	MGPIO_vSetPinInPutType(PORTB, PIN7, PULLUP);
	//MGPIO_vSetPinInPutType(PORTB, PIN10, PULLUP);
	//MGPIO_vSetPinInPutType(PORTB, PIN3, PULLUP);


	//Enable GPIO Clock
	MRCC_vEnableClock(GPIOC_EN);
	//Set LED PIN as OUTPUT
	MGPIO_vSetPinMode(PORTC,PIN13,OUTPUT);
	MGPIO_vSetPinMode(PORTA,PIN0,OUTPUT);


	MI2C_vMasterInit(I2C1);
	//MI2C_vSlaveInit(I2C2,0x1E);
	u8 TxData[] = {15};
	u8 RxData = 0;
	u8 flag = NoError;
	while(1){

		flag=MI2C_vMasterTx(I2C1, 0b1010000, TxData,1,WithStop);
		if(flag== ADDRFAIL)
				MGPIO_vSetPinValue(PORTA, PIN0,HIGH);

		//RxData=MI2C_u8SlaveRx(I2C2);

		if (1){
		MGPIO_vSetPinValue(PORTC,PIN13, HIGH);
		MSYSTICK_vDelayms(1000);
		MGPIO_vSetPinValue(PORTC,PIN13, LOW);
		MSYSTICK_vDelayms(1000);
		}

	}

}

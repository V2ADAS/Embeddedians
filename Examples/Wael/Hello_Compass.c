
#include "MCAL/MGPIO/MGPIO_Int.h"

#include "MCAL/MRCC/MRCC_Int.h"

#include"MCAL/MEXTI/MEXTI_Int.h"

#include"MCAL/MNVIC/MNVIC_Int.h"

#include"MCAL/MSTK/MSYSTICK_Int.h"

#include"MCAL/MTIMER/MTIMER_Int.h"

#include"MCAL/MI2C/MI2C_int.h"

#include"HAL/HCOMPASS/HAL_COMPASS.h"

#include"HAL/HSERVO/HSERVO_Int.h"

#include"HAL/HLCD/HLCD_Int.h"

#include"LIB/BIT_MATH.h"

#include"stdio.h"

void Led(void){
	static u8 Tog = 1;
	//Toggle Led
	MGPIO_vSetPinValue(PORTC,PIN13,Tog);
	Tog ^= 1;
}



#define SCB_CPACR       (*((volatile u32 *)0xE000ED88))


volatile f32 Heading;

u8 main(){

	SCB_CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
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

	//Enable GPIO Clock
	MRCC_vEnableClock(GPIOC_EN);
	//Set LED PIN as OUTPUT
	MGPIO_vSetPinMode(PORTC,PIN13,OUTPUT);

	HCOMPASS_vInit();
	HLCD_vInit();


	HLCD_vPutCur(0,0);
	HLCD_vSendString("Degree : ");
	HLCD_vPutCur(1,0);
	HLCD_vSendString("Direction:");

	while(1){


		/* read registers from 0 to 5 */
		s16 RxData[3]={0};
		HCOMPASS_vSetRowData();
		HCOMPASS_vReadRowData(RxData);
		Heading = HCOMPASS_f32GetHeading();
		f32 Roll = HCOMPASS_f32GetRoll();
		f32 Pitch = HCOMPASS_f32GetPitch();

		MSYSTICK_vDelayms(250);
		HLCD_vPutCur(0,10);
		HLCD_vSendNum((u32)Heading);
		HLCD_vSendString("' ");
		HLCD_vPutCur(1, 11);

		//North
		if (Heading<15 || Heading>350)
			HLCD_vSendString("North");
		// West
		else if(Heading<105 && Heading>80)
			HLCD_vSendString("East ");

		//East
		else if(Heading<285 && Heading>255)
			HLCD_vSendString("West ");

		//South
		else if(Heading<195 && Heading>165){
			HLCD_vSendString("South");
		}






		//RxData=MI2C_u8SlaveRx(I2C2);


		MGPIO_vSetPinValue(PORTC,PIN13, HIGH);
		MSYSTICK_vDelayms(200);
		MGPIO_vSetPinValue(PORTC,PIN13, LOW);
		MSYSTICK_vDelayms(200);

	}

}

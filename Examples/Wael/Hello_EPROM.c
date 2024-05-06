
#include "MCAL/MGPIO/MGPIO_Int.h"

#include "MCAL/MRCC/MRCC_Int.h"

#include"MCAL/MEXTI/MEXTI_Int.h"

#include"MCAL/MNVIC/MNVIC_Int.h"

#include"MCAL/MSTK/MSYSTICK_Int.h"
#include"MCAL/MSTK/MSYSTICK_Private.h"

#include"MCAL/MTIMER/MTIMER_Int.h"

#include"MCAL/MI2C/MI2C_int.h"

#include"HAL/HCOMPASS/HAL_COMPASS.h"

#include"HAL/HSERVO/HSERVO_Int.h"

#include"HAL/HLCD/HLCD_Int.h"

#include"HAL/HEPROM/MEPROM_Int.h"

#include"LIB/BIT_MATH.h"

#include"stdio.h"

void Led(void){
	static u8 Tog = 1;
	//Toggle Led
	MGPIO_vSetPinValue(PORTC,PIN13,Tog);
	Tog ^= 1;
}



void busy_wait_iterations(u32 iterations) {
    for (u32 i = 0; i < iterations; i++) {
        // Do nothing, just wait
    }
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
	MRCC_vEnableClock(GPIOC_EN);
	//Enable SYSCFG
	MRCC_vEnableClock(SYSCFG_EN);
	// ENABLE I2C1
	MRCC_vEnableClock(I2C1_EN);
	//MRCC_vEnableClock(I2C2_EN);
	//Initialize SYSTICK
	MSYSTICK_vInit();

	//Enable GPIO Clock

	//Set LED PIN as OUTPUT
	MGPIO_vSetPinMode(PORTC,PIN13,OUTPUT);
	MGPIO_vSetPinMode(PORTA, PIN10, OUTPUT);


	MI2C_vMasterInit(I2C1);
	HLCD_vInit();
	HLCD_vPutCur(0,0);
	HLCD_vSendString("Degree : ");
	HLCD_vPutCur(1,0);

	HCOMPASS_vInit();



	s16 calibrationData[3][2] = {{500, 643}, {-1135, 326}, {0, 706}};
	HEPROM_vWriteData(0,0,calibrationData, 8);





	while(1){
		int i =0;

		HLCD_vPutCur(1,0);
		HLCD_vSendNum(calibrationData[0][0]);

		u8 EPROM_CalibratingData[8];
		HEPROM_vReadData(0, 0,EPROM_CalibratingData ,8);
		/* x min */
		calibrationData[0][0]= (s16)(EPROM_CalibratingData[1]<<8) | EPROM_CalibratingData[0] ;
		/* x max */
		calibrationData[0][1]= (s16)(EPROM_CalibratingData[3]<<8) | EPROM_CalibratingData[2] ;
		/* y min */
		calibrationData[1][0]= (s16)(EPROM_CalibratingData[5]<<8) | EPROM_CalibratingData[4] ;
		/* y max */
		calibrationData[1][1]= (s16)(EPROM_CalibratingData[7]<<8) | EPROM_CalibratingData[6] ;




		MGPIO_vSetPinValue(PORTC,PIN13, HIGH);
//		busy_wait_iterations(600000);

		MSYSTICK_vDelayms(200);
		MGPIO_vSetPinValue(PORTC,PIN13, LOW);
//		busy_wait_iterations(600000);

		MSYSTICK_vDelayms(200);

	}

}

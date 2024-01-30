/*
 * MTIMER_Prog.c
 *
 *  Created on: Dec 19, 2023
 *      Author: Hardware
 */
#include"MTIMER_Private.h"
#include"MTIMER_Int.h"
#include"MTIMER_Config.h"


static void (*GLOBAL_Ptr)(void)=STD_NULL;

void ICU(void);
u16 Time=0;

void MTIMER1_vTimeMS(u32 Copy_u32Delay){
	//Reset Control Reg Value
	TIM1 ->  CR1 = 0;
	//Prescaler
	TIM1 ->	PSC = SYS_CLOCK*1000-1;
	//Auto Reset Value
	TIM1 -> ARR = Copy_u32Delay -1;
	//Set Update Interrupt
	SET_BIT(TIM1->DIER,UIE);
	//Control Enabled 'Start To Run'
	SET_BIT(TIM1 -> CR1,CEN);
 }

void MTIMER1_vPWM(u8 Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec){

	SET_BIT(TIM1->CR1,ARPE);    // Enable auto-reload preload
	CLR_BIT(TIM1->CR1,DIR); 	// UP COUNT
	CLR_BIT(TIM1->CR1,CMS0); 	// 00: Edge-aligned mode. The counter counts up
	CLR_BIT(TIM1->CR1,CMS1);    // 		or down depending on the direction bit(DIR)

	//01: CCx channel is configured as output  "PWM"
	CLR_BIT(TIM1->CCMR[Copy_u8Channel / 3],(CCxS0+(((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIM1->CCMR[Copy_u8Channel / 3],(CCxS1+(((Copy_u8Channel-1)%2)*8)));

	// set prescaler
	TIM1->PSC = SYS_CLOCK*10-1;
	TIM1->ARR = (Copy_u16TotalTime_uSec*100)/1000-1; // Timer auto-reload to max <<Periodic time>>
	TIM1->CCR[Copy_u8Channel-1] = (Copy_u16PositiveDutyCycle_uSec*100)/1000-1; // << DUTY CYCLE >>
	SET_BIT(TIM1->CCMR[Copy_u8Channel / 3],(OCxPE+(((Copy_u8Channel-1)%2)*8)));  //1: Preload register on TIMx_CCRx enabled

	CLR_BIT(TIM1->CCMR[Copy_u8Channel / 3],(OCxM0+(((Copy_u8Channel-1)%2)*8)));// PWM Mode1 (high then low)
	SET_BIT(TIM1->CCMR[Copy_u8Channel / 3],(OCxM1+(((Copy_u8Channel-1)%2)*8)));
	SET_BIT(TIM1->CCMR[Copy_u8Channel / 3],(OCxM2+(((Copy_u8Channel-1)%2)*8)));

	CLR_BIT(TIM1->CCER,(CCxP+(Copy_u8Channel-1)*4)); //Polarity 0: active high
	//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
	SET_BIT(TIM1->CCER,(CCxE+(Copy_u8Channel-1)*4)); //Bit 0 CC1E: Capture/Compare 1 output enable
	SET_BIT(TIM1->BDTR,15);// MOE 1: OC and OCN outputs are enabled

	SET_BIT(TIM1->CR1,CEN);// Enable timer1
}


void MTIMER1_vInitializeICU(){
	SET_BIT(TIM1->CR1,ARPE);    // Enable auto-reload preload
		CLR_BIT(TIM1->CR1,DIR); 	// UP COUNT
		CLR_BIT(TIM1->CR1,CMS0); 	// 00: Edge-aligned mode. The counter counts up
		CLR_BIT(TIM1->CR1,CMS1);    // 		or down depending on the direction bit(DIR)

		//01: CCx channel is configured as ICU
		SET_BIT(TIM1->CCMR[1],8);
		CLR_BIT(TIM1->CCMR[1],9);

		// set prescaler
		TIM1->PSC = 0;
		TIM1 -> ARR = 0xFFFF;

		//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
		SET_BIT(TIM1->CCER,12); //Bit 0 CC1E: Capture/Compare 1 output enable
		CLR_BIT(TIM1->CCER,13);
		SET_BIT(TIM1-> DIER,4);
		MTIMER_CallBack(&ICU);
		SET_BIT(TIM1->CR1,CEN);// Enable timer1


}
void ICU(void){
	static u8 x=0;
	u16 T1,T2;
	if (x ==0){
		T1 = TIM1->CCR[3];
		SET_BIT(TIM1->CCER,13);
		x++;
		}
	else{
		T2 = TIM1->CCR[3];
		CLR_BIT(TIM1->CCER,13);
		Time = T2 - T1;
		x=0;}
}

u16 GET_ICU(void){
	return Time;
}



void MTIMER_CallBack(void(*ptr)(void)){
		GLOBAL_Ptr=ptr;
}/*

void TIM1_UP_TIM10_IRQHandler(void){
	GLOBAL_Ptr();
}

void TIM1_TRG_COM_TIM11_IRQHandler(void){
	GLOBAL_Ptr();
}

void TIM1_BRK_TIM9_IRQHandler(void){
	GLOBAL_Ptr();
}
*/

void TIM1_CC_IRQHandler(void){
	ICU();
	CLR_BIT(TIM1-> SR,4);
}




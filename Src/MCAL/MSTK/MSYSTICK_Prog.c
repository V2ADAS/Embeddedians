/*
 * MSTK_Prog.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Hardware
 */
#include"MSYSTICK_Private.h"
#include"MSYSTICK_Config.h"
#include"MSYSTICK_Int.h"

static void (*GLOBAL_SYSTICK_CallBack) (void)= STD_NULL;

void MSYSTICK_vInit(void){

	//Clock Source
#if CLK_SOURCE == MSYSTICK_AHB8
	CLR_BIT(STK->CTRL,STK_CLK_SOURCE);
#elif CLK_SOURCE == MSYSTICK_AHB
	SET_BIT(STK->CTRL,STK_CLK_SOURCE);
#endif
	//Clear Flag
	CLR_BIT(STK->CTRL,STK_EN);
}

void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay){
	//Cal Value in mills sec
	Copy_u32Delay = Copy_u32Delay * 1000 * STK_CLOCK;
	//Load Reload Value
	STK->LOAD = Copy_u32Delay - 1;
	//CLR VAL Reg
	STK->VAL = CLR;
	//SET INT
	SET_BIT(STK->CTRL,STK_INT);
	//Enable SYSTICK
	SET_BIT(STK->CTRL,STK_EN);
}

void MSYSTICK_vDelayms(u32 Copy_u32Delay){
	/* MAX Delay: ((1or8)/SYS_CLOCK)* 2^24  " 1.04sec for HSI " */
	//Disable INT
	CLR_BIT(STK->CTRL,STK_INT);
	//Cal Value in mills sec
	if( (Copy_u32Delay*1000 * STK_CLOCK) >= MAX_LOAD_VALUE)
		Copy_u32Delay = MAX_LOAD_VALUE;
	else
		Copy_u32Delay = Copy_u32Delay * 1000 * STK_CLOCK;
	//Load Reload Value
	STK->LOAD = Copy_u32Delay;
	//CLR VAL Reg
	STK->VAL = CLR;
	//Enable SYSTICK
	SET_BIT(STK->CTRL,STK_EN);
	//Wait Flag polling
	while(!GET_BIT(STK->CTRL,COUNT_FLAG));
	//Disable SYSTICK
	CLR_BIT(STK->CTRL,STK_EN);
}

f32 MSYSTICK_u32GetElapsedTime(void){
	//Return Time in milli second
	f32 Elapsed = (STK->LOAD - STK->VAL)*(1/(STK_CLOCK*1000)) ;
	return Elapsed;
}

f32 MSYSTICK_u32GetRemainingTime(void){
	//Return Time in milli second
	return (STK->VAL)*(1/(STK_CLOCK*1000));
}

void MSYSTICK_vStop(void){
	CLR_BIT(STK->CTRL,STK_EN);
}


void MSYSTICK_vCallBack(void(*ptr) (void)){
	GLOBAL_SYSTICK_CallBack = ptr;
}

void SysTick_Handler(void){
	if(GLOBAL_SYSTICK_CallBack != STD_NULL){
		GLOBAL_SYSTICK_CallBack();
	}
}


/*
 * MTIMER_Int.h
 *
 *  Created on: Dec 19, 2023
 *      Author: Hardware
 */

#ifndef MCAL_MTIMER_MTIMER_INT_H_
#define MCAL_MTIMER_MTIMER_INT_H_
/*Timers*/
typedef enum{
	TIMER1=1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER9,
	TIMER10,
	TIMER11,
}Enum_TIMER_NUM;


/*Channels*/
#define CH1		1
#define CH2		2
#define CH3		3
#define CH4		4


void MTIMER_vTimeMS(u8 Copy_u8TimerNum , u32 Copy_u32Delay);

void MTIMER_vPWM(u8 Copy_u8TimerNum,u8 Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec);

void MTIMER_vICU(u8 Copy_u8TimerNum,u8 Copy_u8Channel);

u32 MTIMER_GET_ICU(u8 Copy_u8TimerNum, u8 Copy_u8Channel);

void MTIMER_CallBack(u8 Copy_u8TimerNum,void(*ptr)(void));

#endif /* MCAL_MTIMER_MTIMER_INT_H_ */

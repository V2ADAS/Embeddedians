/*
 * MTIMER_Int.h
 *
 *  Created on: Dec 19, 2023
 *      Author: Hardware
 */

#ifndef MCAL_MTIMER_MTIMER_INT_H_
#define MCAL_MTIMER_MTIMER_INT_H_

/*Channels*/
#define CH1		1
#define CH2		2
#define CH3		3
#define CH4		4

void MTIMER1_vTimeMS(u32 Copy_u32Delay);

void MTIMER1_vPWM(u8 Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec);

void MTIMER1_vInitializeICU();
u16 GET_ICU(void);
void MTIMER_CallBack(void(*ptr)(void));

#endif /* MCAL_MTIMER_MTIMER_INT_H_ */

/*
 * MSTK_Int.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Hardware
 */

#ifndef MCAL_MSTK_MSYSTICK_INT_H_
#define MCAL_MSTK_MSYSTICK_INT_H_


void MSYSTICK_vInit(void);

void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay);

void MSYSTICK_vDelayms(u32 Copy_u32Delay);

f32 MSYSTICK_u32GetElapsedTime(void);

f32 MSYSTICK_u32GetRemainingTime(void);

void MSYSTICK_vStop(void);

void MSYSTICK_vCallBack(void(*ptr) (void));


#endif /* MCAL_MSTK_MSYSTICK_INT_H_ */

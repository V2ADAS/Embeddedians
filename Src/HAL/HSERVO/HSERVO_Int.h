/*
 * HSERVO_Int.h
 *
 *  Created on: Dec 21, 2023
 *      Author: Hardware
 */

#ifndef HAL_HSERVO_HSERVO_INT_H_
#define HAL_HSERVO_HSERVO_INT_H_

void HSERVO_vServoInit(Enum_TIMER_NUM Copy_u8TimerNum,u8 Copy_u8ChannelNum);

void HSERVO_vServoDeg(u8 Copy_u8TimerNum,u8 Copy_u8ChannelNum,u32 Copy_u8Deg);

#endif /* HAL_HSERVO_HSERVO_INT_H_ */

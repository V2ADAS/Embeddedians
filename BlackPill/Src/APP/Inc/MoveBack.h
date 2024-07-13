/*
 * MoveBack.h
 *
 *  Created on: Jun 28, 2024
 *      Author: Omar
 */

#ifndef APP_INC_MOVEBACK_H_
#define APP_INC_MOVEBACK_H_

#include"../../LIB/STD_TYPES.h"
#include"../../MCAL/MTIMER/MTIMER_Int.h"
#include"Car_Control.h"


#define BUFFER_SIZE 200


void MVBack_Init(Enum_TIMER_NUM timer, u16 periodic_ms , CarControl_Data_ST * CarControl_Data );
void MVBack_StartApply(void);

#endif /* APP_INC_MOVEBACK_H_ */

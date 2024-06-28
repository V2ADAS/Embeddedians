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


#define BUFFER_SIZE				200


void MVBack_Init(Enum_TIMER_NUM timer, u16 periodic_ms);
//void MVBack_UpdateHist(void);
//void MVBack_ApplyHist(void);
void MVBack_Start(void);

#endif /* APP_INC_MOVEBACK_H_ */

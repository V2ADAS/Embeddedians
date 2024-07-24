/*
 * Car_History.h
 *
 *  Created on: Jul 12, 2024
 *      Author: Omar
 */

#ifndef APP_INC_CAR_HISTORY_H_
#define APP_INC_CAR_HISTORY_H_

#include"Car_Control.h"
#include"string.h"

#include"../../MCAL/MTIMER/MTIMER_Int.h"



#define CARHIST_BUFFER_SIZE			500
#define CARHIST_NEEDED_STATES		3

typedef enum{

	REVERSE,
	FORWORD
}CarHist_Direction;

typedef struct  {

	u8 History_Buffer[CARHIST_BUFFER_SIZE][CARHIST_NEEDED_STATES];
	u8 Used_Timer  ;
	u8 (*Apply_Buffer_PTR)[CARHIST_NEEDED_STATES]; // Pointer to an array of 3 u8 elements
	u8 Needed_States;
	u16 BufferSize ;
	u16 Peroidic_ms ;
	s16 Buffer_PTR ;
	CarHist_Direction Apply_Buffer_Dir;
	CarControl_Data_ST* Global_PTR_CarControl;

}Car_Histort_ST;

void CarHistory_vInit(Enum_TIMER_NUM TimerNo ,u8 Periodic_ms,CarControl_Data_ST* Local_PTR_CarControl);

void CarHistory_StartSaving();

void CarHistory_StartApplying();

void CarHistory_CopyArray(u8* Src_Ptr , u8* Des_Ptr , u16 Start_idx , u16 End_idx , u16 Size,u8 Arr_dim);

Car_Histort_ST* CarHistory_GetStructADD();



#endif /* APP_INC_CAR_HISTORY_H_ */

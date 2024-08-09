/*
 * Car_History.c
 *
 *  Created on: Jul 12, 2024
 *      Author: Omar
 */

#include"Inc/Car_History.h"
#include"math.h"





Car_Histort_ST car_history_st;

s16 Global_TMP_PTR ;

void Loc_SavingFunc();

void Loc_ApplyingFunc();


void CarHistory_vInit(Enum_TIMER_NUM TimerNo ,u8 Periodic_ms,CarControl_Data_ST* Local_PTR_CarControl){

	memset(&car_history_st, 0, sizeof(car_history_st));
	car_history_st.BufferSize = CARHIST_BUFFER_SIZE ;
	car_history_st.Needed_States = CARHIST_NEEDED_STATES ;
	car_history_st.Used_Timer=TimerNo;
	car_history_st.Peroidic_ms=Periodic_ms;
	car_history_st.Global_PTR_CarControl=Local_PTR_CarControl;

	CarHistory_StartSaving();

}

void CarHistory_StartSaving(){


	MTIMER_vClearCNT(car_history_st.Used_Timer);
	/* set call back function to MVBack_UpdateHist */
	MTIMER_CallBack(car_history_st.Used_Timer, Loc_SavingFunc);
	/* initalize the timer */
	MTIMER_vPeriodicMS(car_history_st.Used_Timer, car_history_st.Peroidic_ms);
}

void CarHistory_StartApplying(){

	car_history_st.Buffer_PTR--;
	Global_TMP_PTR = car_history_st.Buffer_PTR;
	//car_history_st.Apply_Buffer_Dir=REVERSE;
	MTIMER_vClearCNT(car_history_st.Used_Timer);
	/* set call back function to MVBack_UpdateHist */
	MTIMER_CallBack(car_history_st.Used_Timer, Loc_ApplyingFunc);
	/* initalize the timer */
	MTIMER_vPeriodicMS(car_history_st.Used_Timer, car_history_st.Peroidic_ms);


}

Car_Histort_ST* CarHistory_GetStructADD(){
	return &car_history_st;
}

void CarHistory_CopyArray(u8* Src_Ptr, u8* Des_Ptr, u16 Start_idx, u16 End_idx, u16 Size, u8 Arr_dim) {
	for (u16 i = 0; i < Size; i++) {
		if (Start_idx == End_idx)
			return;

		if (Start_idx >= Size)
			Start_idx = 0;

		for (u8 j = 0; j < Arr_dim; j++) {
			Des_Ptr[i * Arr_dim + j] = Src_Ptr[Start_idx * Arr_dim + j];
		}

		Start_idx++;
	}
}


void Loc_SavingFunc(){

	s16 Loc_PTR = car_history_st.Buffer_PTR;
	u8 Speed = car_history_st.Global_PTR_CarControl->Speed ;

	if(Speed == 0)
		return;

	car_history_st.History_Buffer[Loc_PTR][0]=car_history_st.Global_PTR_CarControl->Direction;
	car_history_st.History_Buffer[Loc_PTR][1]=car_history_st.Global_PTR_CarControl->Steering;
	car_history_st.History_Buffer[Loc_PTR][2]=Speed;
	Loc_PTR = (Loc_PTR + 1) % CARHIST_BUFFER_SIZE;
	car_history_st.Buffer_PTR =Loc_PTR;

}

void Loc_ApplyingFunc(){

	if(car_history_st.Apply_Buffer_Dir==FORWORD){

		static s16 Loc_ptr=0;
		u8 Loc_Speed = car_history_st.Apply_Buffer_PTR[Loc_ptr][2];
		if (Loc_Speed == 0){
			//Loc_ptr++;
			//if(Loc_ptr==CARHIST_BUFFER_SIZE){
				HAL_MOTOR_ForceStop(DC_MOTOR);
				CarHistory_StartSaving();
				Loc_ptr=0;
			//}
			return;
		}

		u8 Loc_Direction = car_history_st.Apply_Buffer_PTR[Loc_ptr][0];
		u8 Loc_Steering = car_history_st.Apply_Buffer_PTR[Loc_ptr][1];


		HSERVO_vServoDeg(SERVO1, Loc_Steering);
		//for(u32 i=0 ; i<1000000 ; ++i);//delay
		HAL_MOTOR_MOVE(DC_MOTOR, Loc_Direction,Loc_Speed);


		Loc_ptr++;
		if(Loc_ptr==CARHIST_BUFFER_SIZE){
			HAL_MOTOR_ForceStop(DC_MOTOR);
			CarHistory_StartSaving();
			Loc_ptr=0;
		}
	}

	else if(car_history_st.Apply_Buffer_Dir==REVERSE){

		//volatile static s16 Loc_ptr = car_history_st.Buffer_PTR;
		//	Loc_ptr=car_history_st.Buffer_PTR;

		if(car_history_st.Buffer_PTR==-1)
			car_history_st.Buffer_PTR+=CARHIST_BUFFER_SIZE;

		u8 Loc_Speed = car_history_st.Apply_Buffer_PTR[car_history_st.Buffer_PTR][2];

		if (Loc_Speed == 0 ){
			//car_history_st.Buffer_PTR--;
			//if(car_history_st.Buffer_PTR==Global_TMP_PTR){
				HAL_MOTOR_ForceStop(DC_MOTOR);
				memset(car_history_st.Apply_Buffer_PTR, 0, sizeof(car_history_st.History_Buffer) );
				CarHistory_StartSaving();
				car_history_st.Buffer_PTR=Global_TMP_PTR;
			//}
			return;
		}
		u8 Loc_Direction = (car_history_st.Apply_Buffer_PTR[car_history_st.Buffer_PTR][0])*-1;
		u8 Loc_Steering = car_history_st.Apply_Buffer_PTR[car_history_st.Buffer_PTR][1];


		HSERVO_vServoDeg(SERVO1, Loc_Steering);
		//for(u32 i=0 ; i<1000000 ; ++i);//delay
		HAL_MOTOR_MOVE(DC_MOTOR, Loc_Direction,Loc_Speed);
		// TODO
		car_history_st.Buffer_PTR--;
		if(car_history_st.Buffer_PTR==Global_TMP_PTR){
			HAL_MOTOR_ForceStop(DC_MOTOR);
			CarHistory_StartSaving();
			car_history_st.Buffer_PTR=Global_TMP_PTR;
		}

	}

}



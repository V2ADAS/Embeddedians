/*
 * MoveBack.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Omar
 */

#include"Inc/MoveBack.h"


CarControl_Data_ST * Global_CarControl_Data = NULL_PTR;

/* first element ----> speed */
/* second element ----> steering */
u8 History_buffer[BUFFER_SIZE][2]={{0,0}};
u16 Global_periodic_ms ;
u8 Global_Timer;
s16 buffer_ptr=0;
u16 last_ptr_pos=0;
u8 ovf_flag=0;

void Loc_StartSaving(void);
void Loc_ApplyHistory(void);
void Loc_UpdateHistory(void);

void MVBack_Init(Enum_TIMER_NUM timer, u16 periodic_ms , CarControl_Data_ST * CarControl_Data ){

	Global_CarControl_Data = CarControl_Data ;
	Global_Timer=timer;
	Global_periodic_ms= periodic_ms;
	Loc_StartSaving();
}

void MVBack_StartApply(void){


	last_ptr_pos = buffer_ptr;
	buffer_ptr--;
	/* set call back to MVBack_Apply History*/
	MTIMER_CallBack(Global_Timer, Loc_ApplyHistory);
	/* initalize the timer */
	MTIMER_vClearCNT(Global_Timer);


}



void Loc_UpdateHistory(void){

	/* get current speed */
	History_buffer[buffer_ptr][0] = Global_CarControl_Data->Speed;
	History_buffer[buffer_ptr][1] = Global_CarControl_Data->Steering ;
	buffer_ptr++;
	if(buffer_ptr==BUFFER_SIZE)
		ovf_flag=1;
	buffer_ptr %= BUFFER_SIZE;

}

static u8 local_ptr =BUFFER_SIZE;

void Loc_ApplyHistory(void){

	/* Apply for carcontrol */
	if(buffer_ptr !=-1){
		HAL_MOTOR_MOVE(DC_MOTOR, BACKWARD,History_buffer[buffer_ptr][0]);
		HSERVO_vServoDeg(SERVO1, History_buffer[buffer_ptr][1]);
		buffer_ptr--;
	}
	else if(buffer_ptr==-1 && local_ptr>last_ptr_pos && ovf_flag==1){

		HAL_MOTOR_MOVE(DC_MOTOR, BACKWARD,History_buffer[local_ptr][0]);
		HSERVO_vServoDeg(SERVO1, History_buffer[local_ptr][1]);
		local_ptr--;
	}
	else  {

		HAL_MOTOR_ForceStop(DC_MOTOR);
		Loc_StartSaving();
		local_ptr= BUFFER_SIZE;
	}

}



void Loc_StartSaving (void){
	/* set call back function to MVBack_UpdateHist */
	MTIMER_CallBack(Global_Timer, Loc_UpdateHistory);
	/* initalize the timer */
	MTIMER_vPeriodicMS(Global_Timer, Global_periodic_ms);
	buffer_ptr=0;
	ovf_flag=0;

}

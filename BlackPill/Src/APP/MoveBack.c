/*
 * MoveBack.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Omar
 */

#include"Inc/MoveBack.h"
#include"../HAL/HMOTOR/HMOTOR.h"


Car_Histort_ST * Global_CarHistory_Data = NULL_PTR;

/* first element ----> direction */
/* second element ----> steering */
/* third element ----> speed */

void MVBack_Start(){


	Global_CarHistory_Data=CarHistory_GetStructADD();
	MTIMER_vCntTimer(Global_CarHistory_Data->Used_Timer, StopTimer);
	/* Set Applying Parameters*/
	Global_CarHistory_Data->Apply_Buffer_Dir=REVERSE;
	Global_CarHistory_Data->Apply_Buffer_PTR=Global_CarHistory_Data->History_Buffer;
	/*Start Applying*/
	CarHistory_StartApplying();

}

void MVBack_Stop(){


	HAL_MOTOR_ForceStop(DC_MOTOR);
	memset(Global_CarHistory_Data->History_Buffer, 0, sizeof(Global_CarHistory_Data->History_Buffer) );
	CarHistory_StartSaving();
}


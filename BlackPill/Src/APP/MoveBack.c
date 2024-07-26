/*
 * MoveBack.c
 *
 *  Created on: Jun 28, 2024
 *      Author: Omar
 */

#include"Inc/MoveBack.h"


Car_Histort_ST * Global_CarHistory_Data = NULL_PTR;

/* first element ----> direction */
/* second element ----> steering */
/* third element ----> speed */

void MVBack_Start(){

	MTIMER_vCntTimer(Global_CarHistory_Data->Used_Timer, StopTimer);

	Global_CarHistory_Data=CarHistory_GetStructADD();
	/* Set Applying Parameters*/
	Global_CarHistory_Data->Apply_Buffer_Dir=REVERSE;
	Global_CarHistory_Data->Apply_Buffer_PTR=Global_CarHistory_Data->History_Buffer;
	/*Start Applying*/
	CarHistory_StartApplying();

}


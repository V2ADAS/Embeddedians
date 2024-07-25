/*
 * App_Connection.c
 *
 *  Created on: Jul 24, 2024
 *      Author: Hardware
 */

#include "Inc/App_Connection.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "Inc/Car_Control.h"
#include"Inc/MoveBack.h"
#include"Inc/Personal_Parking.h"

u8 Gl_UART_Used = 0;

Data_ST	App_Tx = {'*' , 50 , 199 ,0 ,1,10, 20, 30, 40, 50, -991, -70, 80.99, 90,11.11,80.8,999.9};
u8 *ptr = (u8*)&App_Tx ;
u8 size = sizeof(App_Tx);

void RX_Callback()
{
	u8 data_rx = MUART_Receive_Data(UART1);
	s8 Steering_tx = 0;
	if (data_rx == 'f' ){
		HAL_MOTOR_StopDcAfterDistance( 10000 );
		HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 50);
	}
	else if (data_rx == 'b' ){
		HAL_MOTOR_MOVE(DC_MOTOR, BACKWARD, 50);
	}
	else if (data_rx == 's' ){
		HAL_MOTOR_ForceStop(DC_MOTOR);
	}
	else if(data_rx == 'd')
		MVBack_Start();

	else if (data_rx == 'r'){
		static u8 loc_flag = 0 ;
		if(loc_flag == 0){
			PersonalParking_StartSaving();
			loc_flag=1;
		}
		else if(loc_flag == 1){
			PersonalParking_EndSaving();
			loc_flag = 0 ;
		}
	}
	else if(data_rx == 'a')
		PersonalParking_Apply();

	else {
		Steering_tx = data_rx - 41 ;
		HSERVO_vServoDeg(SERVO1, Steering_tx);
	}
}

void App_Start_Connect(u8 Copy_u8UART_Num){
	Gl_UART_Used = Copy_u8UART_Num;
	MUART_Init(Copy_u8UART_Num);
	MUART_vSetRxCallBackFunc(Copy_u8UART_Num, RX_Callback);
	MUART_Enable(Copy_u8UART_Num);

}


void App_Tx_Data(){
	MUART_Send_Data(Gl_UART_Used, ptr  ,size );
}






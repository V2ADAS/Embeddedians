/*
 * Parking_Scanner.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Hardware
 */


#include "Inc/Parking_Scanner.h"
#include "Inc/Motion_Planing.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MGPIO/MGPIO_int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"


Position_ST point_CSA,point_SP,point_EP;   // Center point of the parking space
u8 GInit_D; // The distance between our car and the surrounding car, measured at the start point.

u8 Scanned_Area [2][Array_Length];

u8 FOR_START=0,FOR_END=2;

u8 Gl_TimerNum=0;

//void Scanning_vInit(Enum_TIMER_NUM Copy_EnumTimerNum){
//	MTIMER_vPeriodicMS(Copy_EnumTimerNum, 1000);
//	MTIMER_CallBack(Copy_EnumTimerNum, ptr);
//
//}

void Scanning_vStart(Enum_Parking_Scenarios Copy_EnumParkingScenario,Enum_Scanning_Dir Copy_EnumParkingScanningPos,
		Enum_TIMER_NUM Copy_enumTimerNum, Enum_TIMER_CHs Copy_enumTimerCh){
	switch(Copy_EnumParkingScenario){
	case PaF:
		MTIMER_CallBack(Copy_enumTimerNum, PaF_Scan);
		break;
	case PaB:
		MTIMER_CallBack(Copy_enumTimerNum, PaB_Scan);
		break;
	case PeF:
		MTIMER_CallBack(Copy_enumTimerNum, PeF_Scan);
		break;
	case PeB:
		MTIMER_CallBack(Copy_enumTimerNum, PeB_Scan);
		break;
	default:
		break;
	}
	switch(Copy_EnumParkingScanningPos){
	case Scan_Both:
		FOR_START = 0;
		FOR_END = 2;
		break;
	case Scan_Right:
		FOR_START = 0;
		FOR_END = 1;
		break;
	case Scan_Left:
		FOR_START = 1;
		FOR_END = 2;
		break;
	}
	Gl_TimerNum = Copy_enumTimerNum;
	MTIMER_vEXTCNTClock(Copy_enumTimerNum, Copy_enumTimerCh, PULSES_PER_1_CM);

}

void PaF_Scan(){};
void PeF_Scan(){};

void PaB_Scan ()
{
	u8 Local_Distance[2]={0};
	u8 Local_parkL[2], Local_parkW[2];
	static int Dis_Count[2]={0};
	HULTRA_vSendTrigger(PORTB, PIN12);
	HULTRA_vGetDistance(US_RC,&UltraSonics_ST.RC);
	HULTRA_vGetDistance(US_LC,&UltraSonics_ST.LC);
	static u8 itr=0;
	Scanned_Area[0][itr]=(u8)UltraSonics_ST.RC;
	Scanned_Area[1][itr++]=(u8)UltraSonics_ST.LC;itr=itr%Array_Length;

	Local_Distance[0] = (u8)UltraSonics_ST.RC;
	Local_Distance[1] = (u8)UltraSonics_ST.LC;

	static f32 endX[2]={0},endY[2]={0};

	for(u8 i=FOR_START;i<FOR_END;i++){
		if ( Local_Distance[i] > (Car_Width + Safety_Margin ))
		{
			Dis_Count[i]++;
			if (Dis_Count[i] > 10) // back axis of the car point
			{
				endX[i]= internal_data.Odometry.CurrentPoint.x - (i*2-1)*(Local_Distance[i]/2);
				endY[i]= internal_data.Odometry.CurrentPoint.y;

				//				point_EP.x =(Car_Width/2)+ GInit_D + (Local_Distance - (GInit_D )/2);
				//				point_EP.y = Dis_Count[i]; // no. of cm passed by the car starting from point(0,0)
			}
		}
		else
		{
			Dis_Count[i] = 0;
		}
		if (Dis_Count[i] > Vth_Parallel)
		{
			//		Local_parkW = (u8)Local_Distance[i] - GInit_D;
			Local_parkW[i] = Local_Distance[i];
			Local_parkL[i] = Dis_Count[i] ;
			// WE FOUND A PARKING SPACE
			// Start point of parking
			//			point_SP.x=0; // the car is moving on the y direction
			//			point_SP.y=Dis_Count[i]; // the moved distance (cm)
			point_SP.x = internal_data.Odometry.CurrentPoint.x;
			point_SP.y = internal_data.Odometry.CurrentPoint.y;

			point_EP.x = endX[i];
			point_EP.y = endY[i];
			// Center of scanned Area
			point_CSA.y=Local_parkL[i]/2;
			point_CSA.x=Local_parkW[i]/2;
			Dis_Count[i] =0 ;
			itr=0;
			HAL_MOTOR_ForceStop(DC_MOTOR);
			MTIMER_vCntTimer(Gl_TimerNum, StopTimer);
			//			AutoParking();
		}
	}

}


void PeB_Scan(){
	u8 Local_Distance[2]={0};
	u8 Local_parkL[2], Local_parkW[2];
	static int Dis_Count[2]={0};
	HULTRA_vSendTrigger(PORTB, PIN12);
	HULTRA_vGetDistance(US_RC,&UltraSonics_ST.RC);
	HULTRA_vGetDistance(US_LC,&UltraSonics_ST.LC);
	static u8 itr=0;
	Scanned_Area[0][itr]=(u8)UltraSonics_ST.RC;
	Scanned_Area[1][itr++]=(u8)UltraSonics_ST.LC;itr=itr%Array_Length;

	Local_Distance[0] = (u8)UltraSonics_ST.RC;
	Local_Distance[1] = (u8)UltraSonics_ST.LC;

	static f32 endX[2]={0},endY[2]={0};

	for(u8 i=FOR_START;i<FOR_END;i++){
		if ( Local_Distance[i] > (Car_Length + Safety_Margin ))
		{
			Dis_Count[i]++;
			if (Dis_Count[i] > 10) // back axis of the car point
			{
				endX[i]= internal_data.Odometry.CurrentPoint.x - (i*2-1)*(Local_Distance[i]/2);
				endY[i]= internal_data.Odometry.CurrentPoint.y;

				//				point_EP.x =(Car_Width/2)+ GInit_D + (Local_Distance - (GInit_D )/2);
				//				point_EP.y = Dis_Count[i]; // no. of cm passed by the car starting from point(0,0)
			}
		}
		else
		{
			Dis_Count[i] = 0;
		}
		if (Dis_Count[i] > Vth_Perpendicular)
		{
			//		Local_parkW = (u8)Local_Distance[i] - GInit_D;
			Local_parkW[i] = Local_Distance[i];
			Local_parkL[i] = Dis_Count[i] ;
			// WE FOUND A PARKING SPACE
			// Start point of parking
			//			point_SP.x=0; // the car is moving on the y direction
			//			point_SP.y=Dis_Count[i]; // the moved distance (cm)
			point_SP.x = internal_data.Odometry.CurrentPoint.x;
			point_SP.y = internal_data.Odometry.CurrentPoint.y;

			point_EP.x = endX[i];
			point_EP.y = endY[i];
			// Center of scanned Area
			point_CSA.y=Local_parkL[i]/2;
			point_CSA.x=Local_parkW[i]/2;
			Dis_Count[i] =0 ;
			itr=0;
			HAL_MOTOR_ForceStop(DC_MOTOR);
			MTIMER_vCntTimer(Gl_TimerNum, StopTimer);
			//			AutoParking();
		}
	}
}



//void Scan(u8 Scanned_Area[])
//{
//	static int i=0;
//	f64 Local_Distance=0;
//	HULTRA_vSendTrigger(PORTB, PIN12);
//	HULTRA_vGetDistance(US_RC,&Local_Distance);
//	Scanned_Area[i++]=(u8)Local_Distance;
//}
//void Process(u8 Scanned_Area[])
//{
//	u8 count=0;
//	u8 Local_parkL, Local_parkW;
//	for (int i=0;i<100;i++)
//	{
//
//		if ((u8)Scanned_Area[i] > (Car_Width + Safety_Margin + GInit_D))
//		{
//			count++;
//			if (count > 10) // back axis of the car point
//			{
//				point_EP.x =(Car_Width/2)+ GInit_D + (Scanned_Area[i] - (GInit_D )/2);
//				point_EP.y = i; // no. of cm passed by the car starting from point(0,0)
//			}
//		}
//		else
//		{
//			GInit_D=Scanned_Area[i];
//			count = 0;
//			point_EP.y=0;
//			point_EP.x=0;
//		}
//		if (count > Vth_Parallel)
//		{
//			Local_parkW = (u8)Scanned_Area[i] - GInit_D;
//			Local_parkL = count ;
//			// WE FOUND A PARKING SPACE
//			// Start point of parking
//			point_SP.x=0; // the car is moving on the y direction
//			point_SP.y=i; // the moved distance (cm)
//			// Center of scanned Area
//			point_CSA.y=Local_parkL/2;
//			point_CSA.x=Local_parkW/2;
//		}
//	}
//
//}

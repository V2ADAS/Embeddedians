#include "Inc/Auto_Parking.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MNVIC/MNVIC_int.h"
#include "../MCAL/MEXTI/MEXTI_Int.h"

#include "../HAL/HLCD/HLCD_Int.h"
#include "../HAL/HMPU/HMPU6050.h"
#include "../HAL/HCOMPASS/HAL_COMPASS.h"
#include "../MCAL/MSTK/MSYSTICK_Int.h"

Internal_Data_ST internal_data = {0} ;



f32 s ,
distanceBet2Points,
deltaX,
deltaY,
angle,
yaw_arc,
yaw_mpu,
yaw_comp,
Heading,
x,y,
slopeAngle,
error;


void LCD_Display();


Position_ST next_point;
void Loc_UpdateOdometryCallBack();

void AutoParking (){

	//	Auto_Update_Odometry();
	internal_data.Motion_Planning.Func_Path = line_path ;
	do{
		HCOMPASS_vSetRowData();
		Heading = HCOMPASS_f32GetHeading();
		HLCD_vPutCur(0,6);
		HLCD_vSendNum((u32)Heading);
		HLCD_vSendString("' ");

	}while(MGPIO_u8GetPinValue(PORTA, PIN0));



	HCOMPASS_SetHeading_Ref( HCOMPASS_f32GetHeading() );

	HMPU_vCalibration(150);

//	LOC_NextLocation (&internal_data.Odometry  , &internal_data.Motion_Planning ,&internal_data.Path_tracking);
//	LOC_DistanceBet2Points(&internal_data.Odometry , &internal_data.Path_tracking);
//	LOC_AngleOfSlope(&internal_data.Odometry , &internal_data.Path_tracking);
//	distanceBet2Points = internal_data.Path_tracking.distanceBet2Points ;
//	angle = internal_data.Path_tracking.angleSlope ;
	CarCtrl_Move(BACKWARD, 300,  0  , 100 );
//	HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 50);

	while(1){
		CarCtrl_UpdateScheduler();
		CarCtrl_Dispatcher();
		CarCtrl_UpdateData(&internal_data.Car_Control);

		yaw_comp = Get_Yaw(COMPASS);
		yaw_mpu = Get_Yaw(MPU);
		yaw_arc = Get_Yaw(ARC);
		s = HAL_MOTOR_GetMovedDistance() ;

		Update_Odometry( &internal_data.Car_Control , &internal_data.Odometry );

		x=internal_data.Odometry.CurrentPoint.x;
		y=internal_data.Odometry.CurrentPoint.y;

		LOC_NextLocation (&internal_data.Odometry  , &internal_data.Motion_Planning ,&internal_data.Path_tracking);
		LOC_DistanceBet2Points(&internal_data.Odometry , &internal_data.Path_tracking);
		LOC_AngleOfSlope(&internal_data.Odometry , &internal_data.Path_tracking);
		angle = internal_data.Path_tracking.angleSlope ;
		slopeAngle = GetSlopeOfFunc(x);
		error = slopeAngle - yaw_mpu ;
		HSERVO_vServoDeg(SERVO1, error);

		HMPU_UpdateYawAngle(); // update MPU
		HCOMPASS_vSetRowData();// update compass


		LCD_Display();
//		for (int i = 0;  i < 1000000; ++i) ;


	}
}


void Auto_Update_Odometry(){
	u8 delta_d = 15 ;
	u8 pulsePerCm = 38 ;
	MTIMER_vEXTCNTClock(TIMER2, CH1, delta_d * pulsePerCm);
	MTIMER_CallBack(TIMER2, Loc_UpdateOdometryCallBack);
}


void Loc_UpdateOdometryCallBack(){
	Update_Odometry( &internal_data.Car_Control , &internal_data.Odometry );
	//	PT_TrackThePath(&internal_data.Odometry , &internal_data.Motion_Planning ,
	//					&internal_data.Path_tracking , &internal_data.Car_Control);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Display(){
	HLCD_vPutCur(0,0);
	HLCD_vSendNum(error);
	HLCD_vSendString("' ");
	HLCD_vPutCur(0,6);
	HLCD_vSendNum((s32)slopeAngle);
	HLCD_vSendString("' ");
	HLCD_vPutCur(0,12);
	HLCD_vSendNum((s32)yaw_mpu);
	HLCD_vSendString("' ");


	HLCD_vPutCur(1,0);
	HLCD_vSendNum(s);
	HLCD_vPutCur(1,5);
	HLCD_vSendString(":");
	HLCD_vPutCur(1,6);
	HLCD_vSendNum(internal_data.Odometry.CurrentPoint.x);
	HLCD_vPutCur(1,11);
	HLCD_vSendString(":");
	HLCD_vSendNum(internal_data.Odometry.CurrentPoint.y);

}

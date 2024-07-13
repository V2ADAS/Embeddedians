#include "Inc/Auto_Parking.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MNVIC/MNVIC_int.h"
#include "../MCAL/MEXTI/MEXTI_Int.h"

#include "../HAL/HLCD/HLCD_Int.h"
#include "../HAL/HMPU/HMPU6050.h"
#include "../HAL/HCOMPASS/HAL_COMPASS.h"


Internal_Data_ST internal_data = {0} ;



volatile f32 Heading;
f64 	x = 0 ,
		y = 0 ,
		yaw_mpu,
		yaw_comp,
		yaw_arc,
		s , d = 0 ;

void LCD_Display();


Position_ST next_point;
void Loc_UpdateOdometryCallBack();

void AutoParking (){

	Auto_Update_Odometry();
	internal_data.Motion_Planning.Func_Path = line_path ;
	do{
		HCOMPASS_vSetRowData();
		Heading = HCOMPASS_f32GetHeading();

		HLCD_vPutCur(0,6);
		HLCD_vSendNum((u32)Heading);
		HLCD_vSendString("' ");
		MSYSTICK_vDelayms(100);

	}while(MGPIO_u8GetPinValue(PORTA, PIN0));

	HCOMPASS_SetHeading_Ref( HCOMPASS_f32GetHeading() );

	HMPU_vCalibration(150);

	CarControl_Move(FORWARD, 100, 0, 30, &internal_data.Car_Control);




	while(1){

		HMPU_UpdateYawAngle(); // updata mpu

		HCOMPASS_vSetRowData();// updata compass

		yaw_comp = Get_Angle(COMPASS);
		yaw_mpu = Get_Angle(MPU);
		yaw_arc = Get_Angle(ARC);
		s = HAL_MOTOR_GetMovedDistance() ;

		LOC_NextLocation (&internal_data.Odometry  , &internal_data.Motion_Planning ,&internal_data.Path_tracking);

		/***************************** print x and y ****************************/
		Position_ST p = internal_data.Odometry.CurrentPoint;
		x = p.x ;
		y = p.y ;

		MEXTI_vSWevent(EXTI1);


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
	PT_TrackThePath(&internal_data.Odometry , &internal_data.Motion_Planning , &internal_data.Path_tracking);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void LCD_Display(){
	HLCD_vPutCur(0,0);
	HLCD_vSendNum(internal_data.Path_tracking.NextPoint.x);
	HLCD_vSendString("' ");
	HLCD_vPutCur(0,6);
	HLCD_vSendNum((s32)yaw_comp);
	HLCD_vSendString("' ");
	HLCD_vPutCur(0,12);
	HLCD_vSendNum((s32)yaw_mpu);
	HLCD_vSendString("' ");

	HLCD_vPutCur(1,0);
	HLCD_vSendNum(x);
	HLCD_vPutCur(1,5);
	HLCD_vSendString(":");
	HLCD_vPutCur(1,7);
	HLCD_vSendNum(y);
	HLCD_vPutCur(1,12);
	HLCD_vSendString(":");
	HLCD_vSendNum(internal_data.Path_tracking.NextPoint.y);

}

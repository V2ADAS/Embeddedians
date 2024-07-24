#include "Inc/Path_Tracking.h"
#include "Inc/Odometry.h"
#include "Inc/Motion_Planing.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "Inc/Car_Control.h"
#include "Inc/Auto_Parking.h"
#include "stdlib.h"


void LOC_NextLocation (Odometry_Data_ST * Odometry_Data ,
		MotionPlanning_Data_ST * MotionPlanning_Data , PathTracking_Data_ST *  PathTracking_Data){
	Position_ST  next_point ;
	f32 delta_x = 5 ;
	f32 x_new , y_new ;
	//get current point to increment its x by delta_x and get y_new by substituting
	x_new = Odometry_Data->CurrentPoint.x + delta_x ;
	//	y_new = Odometry_Data->CurrentPoint.x + delta_x ;

	y_new = MotionPlanning_Data->Func_Path(x_new);
	next_point.x = x_new ;
	next_point.y = y_new ;

	PathTracking_Data->NextPoint = next_point ;

}

void LOC_DistanceBet2Points (Odometry_Data_ST * Odometry_Data,PathTracking_Data_ST *  PathTracking_Data){
	Position_ST point1 , point2 ;
	point1 = Odometry_Data->CurrentPoint ;
	point2 = PathTracking_Data->NextPoint ;
	PathTracking_Data->distanceBet2Points = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));

}


void LOC_AngleOfSlope(Odometry_Data_ST * Odometry_Data,PathTracking_Data_ST *  PathTracking_Data){
	Position_ST point1 , point2 ;
	point1 = Odometry_Data->CurrentPoint ;
	point2 = PathTracking_Data->NextPoint ;
	f32 deltaX = point2.x - point1.x;
	f32 deltaY = point2.y - point1.y;

	// Calculate the angle using arc tangent
	f32 angle = atan2(deltaX, deltaY);

	// Convert the angle from radians to degrees
	angle = angle * (180.0 / PI);
	PathTracking_Data->angleSlope = (s16) angle ;
}

void PT_TrackThePath ( Odometry_Data_ST * Odometry_Data , MotionPlanning_Data_ST * MotionPlanning_Data ,
		PathTracking_Data_ST *  PathTracking_Data , CarControl_Data_ST * CarControl_Data ) {

	f32 distanceBet2Points , angleSlope , yaw , steering = 40 ;
	LOC_NextLocation (Odometry_Data  , MotionPlanning_Data ,PathTracking_Data);
	LOC_DistanceBet2Points(Odometry_Data , PathTracking_Data);
	LOC_AngleOfSlope(Odometry_Data , PathTracking_Data);
	distanceBet2Points = PathTracking_Data->distanceBet2Points ;
	angleSlope = PathTracking_Data->angleSlope ;
	yaw = Get_Yaw(MPU) ;
	if ( (yaw - angleSlope ) <= 5 || (yaw - angleSlope ) >= -5  )
		steering = 0 ;
	else if( yaw > angleSlope )
		steering = -40 ;

	CarCtrl_Move(FORWARD, distanceBet2Points, steering , 50 );
	// condition to check yaw == angleSlope
}

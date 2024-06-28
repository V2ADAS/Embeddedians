#include "Inc/Path_Tracking.h"
#include "Inc/Odometry.h"
#include "Inc/Motion_Planing.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "Inc/Car_Control.h"

#include "stdlib.h"

static Position_ST LOC_GetNextLocation (f32 (*Func_Path)(f32 x)){
	Position_ST current_point , next_point ;
	f32 delta_x = 15 ;
	f32 x_new , y_new ;
	//get current point to increment its x by delta_x and get y_new by substituting
	current_point = *Get_Center();
	x_new = current_point.x + delta_x ;
	y_new = Func_Path(x_new);
	next_point.x = x_new ;
	next_point.y = y_new ;
	return next_point ;
}

static f32 LOC_GetDistanceBet2Points (Position_ST point1 ,Position_ST point2 ){

	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}


static s8 LOC_GetAngleOfSlope(Position_ST point1 ,Position_ST point2){
    f32 deltaX = point2.x - point1.x;
    f32 deltaY = point2.y - point1.y;

    // Calculate the angle using arctangent
    f32 angle = atan2(deltaX, deltaY);

    // Convert the angle from radians to degrees
    angle = angle * (180.0 / PI);

    return (s8) angle;
}

void PT_TrackThePath ( Odometry_Data_ST * Odometry_Data , MotionPlanning_Data_ST * MotionPlanning_Data) {
	f32 distance , angle ;
	s8 sign = 1 ;
	Position_ST next_point ;
//	current_point.x = Internal_Data.currentLoc.x;
//	current_point.y = Internal_Data.currentLoc.y;
//	next_point = LOC_GetNextLocation(Func_Path);
	next_point = LOC_GetNextLocation(MotionPlanning_Data->Func_Path);
	distance = LOC_GetDistanceBet2Points(Odometry_Data->CurrentPoint, next_point);
	angle = LOC_GetAngleOfSlope(Odometry_Data->CurrentPoint, next_point);
	if (angle < 0 )
		sign = -1 ;
	HAL_MOTOR_StopDcAfterDistance(distance);
	HSERVO_vServoDeg(SERVO1, angle);
}

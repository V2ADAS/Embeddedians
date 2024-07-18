#include "Inc/Path_Tracking.h"
#include "Inc/Odometry.h"
<<<<<<< HEAD
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "Inc/Car_Control.h"

static Point_t LOC_GetNextLocation (f32 (*Func_Path)(f32 x)){
	Point_t current_point , next_point ;
	f32 delta_x = 15 ;
	f32 x_new , y_new ;
	//get current point to increment its x by delta_x and get y_new by substituting
	current_point = *Get_Center();
	x_new = current_point.x + delta_x ;
	y_new = Func_Path(x_new);
=======
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
>>>>>>> azza
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


<<<<<<< HEAD
static s8 LOC_GetAngleOfSlope(Point_t point1 ,Point_t point2){
    f32 deltaX = point2.x - point1.x;
    f32 deltaY = point2.y - point1.y;

    // Calculate the angle using arctangent
    f32 angle = atan2(deltaX, deltaY);
=======
void LOC_AngleOfSlope(Odometry_Data_ST * Odometry_Data,PathTracking_Data_ST *  PathTracking_Data){
	Position_ST point1 , point2 ;
	point1 = Odometry_Data->CurrentPoint ;
	point2 = PathTracking_Data->NextPoint ;
	f32 deltaX = point2.x - point1.x;
	f32 deltaY = point2.y - point1.y;

	// Calculate the angle using arc tangent
	f32 angle = atan2(deltaX, deltaY);
>>>>>>> azza

	// Convert the angle from radians to degrees
	angle = angle * (180.0 / PI);
	PathTracking_Data->angleSlope = (s16) angle ;
}

<<<<<<< HEAD
void PT_TrackThePath (f32 (*Func_Path)(f32 x)) {
	f32 distance , angle ;
	s8 sign = 1 ;
	Point_t current_point , next_point ;
	current_point = *Get_Center();
	next_point = LOC_GetNextLocation(Func_Path);
	distance = LOC_GetDistanceBet2Points(current_point, next_point);
	angle = LOC_GetAngleofslope(current_point, next_point);
	if (angle < 0 )
		sign = -1 ;
	CarControl_Move(FORWARD, distance , sign * 40 , 50);
	while (HAL_MOTOR_GetMovedDistance() < 15 ) ;
	HAL_MOTOR_ForceStop(DC_MOTOR);
=======
void PT_TrackThePath ( Odometry_Data_ST * Odometry_Data , MotionPlanning_Data_ST * MotionPlanning_Data ,
		PathTracking_Data_ST *  PathTracking_Data , CarControl_Data_ST * CarControl_Data ) {
>>>>>>> azza

	f32 distanceBet2Points , angleSlope , yaw , steering = 40 ;
	LOC_NextLocation (Odometry_Data  , MotionPlanning_Data ,PathTracking_Data);
	LOC_DistanceBet2Points(Odometry_Data , PathTracking_Data);
	LOC_AngleOfSlope(Odometry_Data , PathTracking_Data);
	distanceBet2Points = PathTracking_Data->distanceBet2Points ;
	angleSlope = PathTracking_Data->angleSlope ;
	yaw = Get_Angle(MPU) ;
	if ( (yaw - angleSlope ) <= 5 || (yaw - angleSlope ) >= -5  )
		steering = 0 ;
	else if( yaw > angleSlope )
		steering = -40 ;

	CarControl_Move(FORWARD, distanceBet2Points, steering , 50 );
	// condition to check yaw == angleSlope
}

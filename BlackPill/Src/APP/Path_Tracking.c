#include "Inc/Path_Tracking.h"
#include "Inc/Odometry.h"
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
	next_point.x = x_new ;
	next_point.y = y_new ;
	return next_point ;
}

static f32 LOC_GetDistanceBet2Points (Point_t point1 ,Point_t point2 ){

	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}


static s8 LOC_GetAngleOfSlope(Point_t point1 ,Point_t point2){
    f32 deltaX = point2.x - point1.x;
    f32 deltaY = point2.y - point1.y;

    // Calculate the angle using arctangent
    f32 angle = atan2(deltaX, deltaY);

    // Convert the angle from radians to degrees
    angle = angle * (180.0 / PI);

    return (s8) angle;
}

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

	//It is expected to pass "distance , angle" to a control function will be finished soon
}

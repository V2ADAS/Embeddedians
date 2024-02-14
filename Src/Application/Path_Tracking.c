#include "Inc/Path_Tracking.h"

static Point_t LOC_GetCurrentLocation (){
	Point_t current_point;
	//code using MPU6050

	//for test
	current_point.x = 3.1 ;
	current_point.y = 9.01 ;
	return current_point ;
}


static Point_t LOC_GetNextLocation (f32 (*Func_Path)(f32 x)){
	Point_t current_point , next_point ;
	f32 delta_x = 0.1 ;
	f32 x_new , y_new ;
	//get current point to increment its x by delta_x and get y_new by substituting
	current_point = LOC_GetCurrentLocation();
	x_new = current_point.x + delta_x ;
	y_new = Func_Path(x_new);
	next_point.x = x_new ;
	next_point.y = y_new ;
	return next_point ;
}

static f32 LOC_GetDistanceBet2Points (Point_t point1 ,Point_t point2 ){

	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}


static s8 LOC_GetAngleofslope(Point_t point1 ,Point_t point2){
    f32 deltaX = point2.x - point1.x;
    f32 deltaY = point2.y - point1.y;

    // Calculate the angle using arctangent
    f32 angle = atan2(deltaY, deltaX);

    // Convert the angle from radians to degrees
    angle = angle * (180.0 / PI);

    return (s8) angle;
}

void PT_TrackThePath (f32 (*Func_Path)(f32 x)) {
	f32 distance , angle ;
	Point_t current_point , next_point ;
	current_point = LOC_GetCurrentLocation();
	next_point = LOC_GetNextLocation(Func_Path);
	distance = LOC_GetDistanceBet2Points(current_point, next_point);
	angle = Get_Angle_of_slope(current_point, next_point);

	//It is expected to pass "distance , angle" to a control function will be finished soon
}

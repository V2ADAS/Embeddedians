#include "Inc/Path_Tracking.h"

Point_t Get_Current_location (){
	Point_t current_point;
	//code using MPU6050

	//for test
	current_point.x = 3.1 ;
	current_point.y = 9.01 ;
	return current_point ;
}


Point_t Get_Next_location (f32 (*Func_Path)(f32 x)){
	Point_t current_point , next_point ;
	f32 delta_x = 0.1 ;
	f32 x_new , y_new ;
	//get current point to increment its x by delta_x and get y_new by substituting
	current_point = Get_Current_location();
	x_new = current_point.x + delta_x ;
	y_new = Func_Path(x_new);
	next_point.x = x_new ;
	next_point.y = y_new ;
	return next_point ;
}

f32 Get_Distance_bet_2Points (Point_t point1 ,Point_t point2 ){

	return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}


f32 Get_Angle_of_slope(Point_t point1 ,Point_t point2){
    f32 deltaX = point2.x - point1.x;
    f32 deltaY = point2.y - point1.y;

    // Calculate the angle using arctangent
    f32 angle = atan2(deltaY, deltaX);

    // Convert the angle from radians to degrees
    angle = angle * (180.0 / PI);

    return angle;
}

void Track_Path () {
	f32 distance , angle ;
	Point_t current_point , next_point ;
	current_point = Get_Current_location();
	next_point = Get_Next_location(PaB_Path);
	distance = Get_Distance_bet_2Points(current_point, next_point);
	angle = Get_Angle_of_slope(current_point, next_point);

	//It is expected to pass "distance , angle" to a control function will be finished soon
}

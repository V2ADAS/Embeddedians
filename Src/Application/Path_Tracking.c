#include "Inc/Path_Tracking.h"

Point_t Get_Current_location (){
	Point_t current_point;
	//code using MPU6050

	//for test
	current_point.x = 3.1 ;
	current_point.y = 4.45 ;
	return current_point ;
}


Point_t Get_Next_location (f32 (*Func_Path)(f32)){
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

void Track_Path () ;

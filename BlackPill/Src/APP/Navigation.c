#include "Inc/Navigation.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../LIB/STD_TYPES.h"

f64 distance_old = 0 ;
//f32 distance_new , delta_distance ;

f64 get_delta_distance(){
	f64 distance_new = HAL_MOTOR_GetMovedDistance();
	f64 delta_distance =  distance_new - distance_old ;
	 distance_old = distance_new ;
	return delta_distance * 1000 ;
}



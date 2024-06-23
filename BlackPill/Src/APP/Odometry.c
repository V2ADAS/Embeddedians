#include "Inc/Odometry.h"

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HMPU/HMPU6050.h"
#include "../HAL/HCOMPASS/HAL_COMPASS.h"
#include "../APP/Inc/Car_Control.h"


f32 alpha_angle = 0.4;
f64 distance_old = 0 ;

//f32 distance_new , delta_distance ;

static Point_t Current_Point;

Point_t* Get_Center(void){
	return &Current_Point;
}

void Set_Center(Point_t Copy_StructXY){
	Current_Point.x = Copy_StructXY.x ;
	Current_Point.y = Copy_StructXY.y ;
}

f64 get_delta_distance(){
	f64 distance_new = HAL_MOTOR_GetMovedDistance();
	f64 delta_distance =  distance_new - distance_old ;
	distance_old = distance_new ;
	delta_distance = delta_distance * 1000;
	return delta_distance;
}

void Update_Odometry(f32 Copy_f32delta_t , f32 Copy_f32Yaw){
	f32 RR = Reduction_Ratio(Copy_f32Yaw);
	Copy_f32delta_t *= RR;
	Copy_f32Yaw = Copy_f32Yaw * PI /180;
	Current_Point.x += Copy_f32delta_t  * sin(Copy_f32Yaw);
	Current_Point.y += Copy_f32delta_t  * cos(Copy_f32Yaw);
}

f32 Get_Angle(Enum_Sensor_t Angle_Select){
	f32 Deg=0;
	switch(Angle_Select){
	case MPU:
		Deg = HMPU_f32GetYawAngle();
		if(Deg > 0)
			Deg += HAL_MOTOR_GetMovedDistance()*(5.0/70.0);
		else
			Deg -= HAL_MOTOR_GetMovedDistance()*(5.0/70.0);
		return Deg;
		break;
	case COMPASS:
		return HCOMPASS_f32GetHeading();
		break;
	case FUSION://TODO: Handle fusion correctly
		return ( ( alpha_angle * HMPU_f32GetYawAngle() ) + ( (1 - alpha_angle) * HCOMPASS_f32GetHeading() ) ) ;
		break;
	default:
		return 0;
	}
}





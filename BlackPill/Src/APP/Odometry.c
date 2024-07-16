#include "Inc/Odometry.h"

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HMPU/HMPU6050.h"
#include "../HAL/HCOMPASS/HAL_COMPASS.h"
#include "Inc/Car_Control.h"


#include "math.h"

f64 distance_old = 0 ;
f32 ArcAngle = 0 ;
f32 R_40 = 63 , R_30 = 80 , R_20 = 116.3 ;

//f32 distance_new , delta_distance ;

Position_ST Current_Point ;

Position_ST* Get_Center(void){
	//	Update_Odometry();
	return &Current_Point;
}

void Set_Center(Position_ST Copy_StructXY){
	Current_Point.x = Copy_StructXY.x ;
	Current_Point.y = Copy_StructXY.y ;
}


f64 get_delta_distance(){
	f64 distance_new = HAL_MOTOR_GetMovedDistance();
	f64 delta_distance =  distance_new - distance_old ;
	distance_old = distance_new ;
	delta_distance = delta_distance  ;
	return delta_distance;
}

f32 Loc_GetAngleOfArc(){
	f32 R , angle  ;
	u8  sign  ;
	s8 steering ;
	if ( getSteering() < 0 )
		sign = -1 ;
	else
		sign = 1 ;

	steering = getSteering() * sign ;

	switch(steering ){
	case 40 :
		R = R_40;
		break ;
	case 30 :
		R = R_30;
		break ;
	case 20 :
		R = R_20;
		break ;
	default :
		break ;
	}

	angle = ( (HAL_MOTOR_GetMovedDistance() * 360)/(2*PI*R) ) * sign ;

	return angle ;
}

f32 Get_Yaw(Enum_Sensor_t Angle_Select){
	f32 Deg=0 , R_40 = 63 , R_30 = 80 , R_20=116.3 , alpha_angle = 0.5 ;

	switch(Angle_Select){
	case MPU:
		Deg = HMPU_f32GetYawAngle();
//		if(Deg > 0)
//			Deg += HAL_MOTOR_GetMovedDistance()*(5.0/70.0);
//		else
//			Deg -= HAL_MOTOR_GetMovedDistance()*(5.0/70.0);
		return Deg * -1.13 ;
		break;
	case COMPASS:
		return HCOMPASS_f32GetHeadingOutRef();
		break;
	case ARC:
		return ((HAL_MOTOR_GetMovedDistance()*360)/(2*PI*R_40)) ;
		break;
	case FUSION:
		Deg = HMPU_f32GetYawAngle();
		if(Deg > 0)
			Deg += HAL_MOTOR_GetMovedDistance()*(5.0/70.0);
		else
			Deg -= HAL_MOTOR_GetMovedDistance()*(5.0/70.0);

		return ( ( alpha_angle * Deg ) + ( (1 - alpha_angle) * HCOMPASS_f32GetHeadingOutRef() ) ) ;
		break;
	default:
		return 0;
	}
}


void Update_Odometry(CarControl_Data_ST * CarControl_Data , Odometry_Data_ST * Odometry_Data ){
	f32 delta_d = get_delta_distance() ;
	f32 yaw = Get_Yaw(MPU);
	f32 RR = CarControl_Data->Reduction_Ratio ;
//	f32 steering = CarControl_Data->Steering ;
	s8 DircOfSteering  = CarControl_Data->DircOfSteering ;
	delta_d *= RR ;
	yaw = yaw * PI /180 ;

	Odometry_Data->CurrentPoint.x += delta_d  * sin(yaw + DircOfSteering*(yaw * 0.25) ) ;
	Odometry_Data->CurrentPoint.y += delta_d  * cos(yaw + DircOfSteering*(yaw * 0.1) ) ;
}



//void Auto_Update_Odometry(){
//	u8 delta_d = 15 ;
//	u8 pulsePerCm = 38 ;
//	MTIMER_vEXTCNTClock(TIMER2, CH1, delta_d * pulsePerCm);
//	MTIMER_CallBack(TIMER2, Update_Odometry);
//}



#include "Inc/Odometry.h"

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HMPU/HMPU6050.h"
#include "../HAL/HCOMPASS/HAL_COMPASS.h"
#include "../APP/Inc/Car_Control.h"

#include "math.h"
f32 alpha_angle = 0.4;

f64 distance_old = 0 ;
f32 ArcAngle = 0 ;
f32 R_40 = 63 , R_30 = 80 , R_20 = 116.3 ;

//f32 distance_new , delta_distance ;

static Point_t Current_Point ;

Point_t* Get_Center(void){
	Update_Odometry();
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
	delta_distance = delta_distance;
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

f32 Get_Angle(Enum_Sensor_t Angle_Select){
	f32 Deg=0 , R_40 = 63 , R_30 = 80 , R_20=116.3 ;
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
		return HCOMPASS_f32GetHeadingOutRef();
		break;
	case ARC:
		return ((HAL_MOTOR_GetMovedDistance()*360)/(2*PI*R_40)) ;
		break;
	case FUSION://TODO: Handle fusion correctly
		return ( ( alpha_angle * HMPU_f32GetYawAngle() ) + ( (1 - alpha_angle) * HCOMPASS_f32GetHeading() ) ) ;
		break;
	default:
		return 0;
	}
}

void Update_Odometry(){
	f32 delta_d = get_delta_distance() ;
	f32 yaw = Get_Angle(COMPASS) ;
	f32 RR = Get_ReductionRatio() ;
	delta_d *= RR ;
	yaw = yaw * PI /180 ;
	Current_Point.x += delta_d  * sin(yaw /*+ (yaw/3)*/) ;
	Current_Point.y += delta_d  * cos(yaw /*+ (yaw/10)*/) ;
}

void Auto_Update_Odometry(Enum_TIMER_NUM Copy_EnumTimerNum , Enum_TIMER_CHs Copy_EnumTimerCH){
	u8 delta_d = 15 ;
	u8 pulsePerCm = 38 ;
	MTIMER_vEXTCNTClock(Copy_EnumTimerNum, Copy_EnumTimerCH, delta_d * pulsePerCm);
	MTIMER_CallBack(Copy_EnumTimerNum, Update_Odometry);
}



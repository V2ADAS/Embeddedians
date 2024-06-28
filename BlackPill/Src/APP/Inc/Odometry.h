#ifndef APP_NAVIGATION_H_
#define APP_NAVIGATION_H_

#include "../../LIB/STD_TYPES.h"
#include "Motion_Planing.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"

typedef struct
{
    f32 x ;
    f32 y ;

}Point_t;

typedef enum{
	MPU,
	COMPASS,
	FUSION,
	ARC
}Enum_Sensor_t;


f32 Loc_GetAngleOfArc();
Point_t* Get_Center(void);

void Set_Center(Point_t Copy_StructXY);

void Auto_Update_Odometry(Enum_TIMER_NUM Copy_EnumTimerNum , Enum_TIMER_CHs Copy_EnumTimerCH);

void Update_Odometry(/*f32 Copy_f32delta_t , f32 Copy_f32Yaw*/);

f32 Get_Angle(Enum_Sensor_t Angle_Select);

f64 get_delta_distance();



#endif /*APP_NAVIGATION_H_*/

#ifndef APP_NAVIGATION_H_
#define APP_NAVIGATION_H_

#include "../../LIB/STD_TYPES.h"
#include "Motion_Planing.h"


typedef enum{
	MPU,
	COMPASS,
	FUSION,
}Enum_Sensor_t;



Point_t* Get_Center(void);

void Set_Center(Point_t Copy_StructXY);

void Update_Odometry(f32 Copy_f32delta_t , f32 Copy_f32Yaw);

f32 Get_Angle(Enum_Sensor_t Angle_Select);



#endif /*APP_NAVIGATION_H_*/

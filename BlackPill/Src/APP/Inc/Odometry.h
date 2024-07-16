#ifndef APP_NAVIGATION_H_
#define APP_NAVIGATION_H_

#include "../../LIB/STD_TYPES.h"
#include "Motion_Planing.h"
#include "../../MCAL/MTIMER/MTIMER_Int.h"
#include "Car_Control.h"


typedef struct
{
    f32 x ;
    f32 y ;

}Position_ST;

typedef struct {
	Position_ST CurrentPoint ;

}Odometry_Data_ST;


typedef enum{
	MPU,
	COMPASS,
	FUSION,
	ARC
} Enum_Sensor_t ;


f32 Loc_GetAngleOfArc();

Position_ST* Get_Center(void);

void Set_Center(Position_ST Copy_StructXY);

void Auto_Update_Odometry(/*Shared_Area_t * Internal_Data */);

void Update_Odometry(CarControl_Data_ST * CarControl_Data , Odometry_Data_ST * Odometry_Data );

f32 Get_Yaw(Enum_Sensor_t Angle_Select);

f64 get_delta_distance();



#endif /*APP_NAVIGATION_H_*/

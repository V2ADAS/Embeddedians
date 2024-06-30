#ifndef AUTO_PARKING_H_
#define AUTO_PARKING_H_

#include "Car_Control.h"
#include "Motion_Planing.h"
#include "Odometry.h"
#include "Path_Tracking.h"


typedef struct  {
	Odometry_Data_ST Odometry ;
	PathTracking_Data_ST Path_tracking ;
	MotionPlanning_Data_ST Motion_Planning ;
	CarControl_Data_ST Car_Control ;
}Internal_Data_ST;

Internal_Data_ST internal_data  ;
void AutoParking ();

void LCD_Display();

void Loc_UpdateOdometryCallBack();


#endif /*AUTO_PARKING_H_*/

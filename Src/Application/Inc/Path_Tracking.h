#ifndef PATH_TRACKING_
#define PATH_TRACKING_

#include "../../LIB/STD_TYPES.h"
#include "../Inc/Motion_Planing.h"

u16 Distance ;
s8 Angle ;

u16 Get_Distance_bet_2Points (Point_t point1 ,Point_t point2 );
s8 Get_Angle_of_slope(Point_t point1 ,Point_t point2);

#endif /*PATH_TRACKING_*/
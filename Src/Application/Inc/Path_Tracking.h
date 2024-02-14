#ifndef PATH_TRACKING_
#define PATH_TRACKING_

#include "../../LIB/STD_TYPES.h"
#include "../Inc/Motion_Planing.h"
#include "../../LIB/BIT_MATH.h"


Point_t Get_Current_location ();


/******************************************************************************************************/
/*                                       Get_Next_location                                            */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Get the next point from the path by substitute in the mathematical      */
/*							  function 																  */
/* 2- Function Input       -> @param Func_Path() = PaB_Path() , PeB_Path() , PeF_Path()                 */
/* 3- Function Return      -> return the next point                                                                    */
/******************************************************************************************************/
Point_t Get_Next_location (f32 (*Func_Path)(f32 x));

f32 Get_Distance_bet_2Points (Point_t point1 ,Point_t point2 );

f32 Get_Angle_of_slope(Point_t point1 ,Point_t point2);

void Track_Path () ;


#endif /*PATH_TRACKING_*/

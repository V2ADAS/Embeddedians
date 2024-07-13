#ifndef PATH_TRACKING_
#define PATH_TRACKING_

#include "../../LIB/STD_TYPES.h"
#include "../Inc/Motion_Planing.h"
#include "../../LIB/BIT_MATH.h"
#include "Odometry.h"

typedef struct{
	Position_ST CurrentPoint ;
	Position_ST NextPoint ;
	f32 distanceBet2Points ;
	s16 angleSlope ;

}PathTracking_Data_ST;
/******************************************************************************************************/
/*                                       LOC_GetCurrentLocation                                       */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Get current location from imu sensor and return it as a point (x,y)     */
/* 2- Function Input       -> void													                  */
/* 3- Function Return      -> return Point_t >> the current poin                                      */
/******************************************************************************************************/
//static Point_t LOC_GetCurrentLocation ();



/******************************************************************************************************/
/*                                       LOC_GetNextLocation                                          */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Get the next point from the path by substitute in the mathematical      */
/*							  function 																  */
/* 2- Function Input       -> @param Func_Path() = PaB_Path , PeB_Path , PeF_Path                     */
/* 3- Function Return      -> return Point_t >> the next point                                        */
/******************************************************************************************************/

void LOC_NextLocation (Odometry_Data_ST * Odometry_Data ,
		MotionPlanning_Data_ST * MotionPlanning_Data , PathTracking_Data_ST *  PathTracking_Data);



/******************************************************************************************************/
/*                                       LOC_GetDistanceBet2Points                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Get the distance between two points  									  */
/* 2- Function Input       -> @param point1 >> current point                                          */
/*  					   	  @param point2 >> next point								              */
/* 3- Function Return      -> return float distance in cm unit                                        */
/******************************************************************************************************/
void LOC_DistanceBet2Points (Odometry_Data_ST * Odometry_Data,PathTracking_Data_ST *  PathTracking_Data);



/******************************************************************************************************/
/*                                       LOC_GetAngleofslope                                          */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Get the slope of line made by two points current and next points 	      */
/* 2- Function Input       -> @param point1 >> current point                                          */
/*  					   	  @param point2 >> next point								              */
/* 3- Function Return      -> return signed integer                                                   */
/******************************************************************************************************/
void LOC_AngleOfSlope(Odometry_Data_ST * Odometry_Data,PathTracking_Data_ST *  PathTracking_Data);


/******************************************************************************************************/
/*                                       PT_TrackThePath                                              */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> tracking the path by getting the current point and next point   	      */
/* 2- Function Input       -> @param Func_Path() = PaB_Path , PeB_Path , PeF_Path                     */
/* 3- Function Return      -> void                                                                    */
/******************************************************************************************************/
void PT_TrackThePath ( Odometry_Data_ST * Odometry_Data , MotionPlanning_Data_ST * MotionPlanning_Data ,
						PathTracking_Data_ST *  PathTracking_Data) ;
#endif /*PATH_TRACKING_*/

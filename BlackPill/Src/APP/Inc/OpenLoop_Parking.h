/*
 * OL_Auto_Parking.h
 *
 *  Created on: Jul 11, 2024
 *      Author: Hardware
 */

#ifndef APP_INC_OPENLOOP_PARKING_H_
#define APP_INC_OPENLOOP_PARKING_H_

#include "Motion_Planing.h"
#include "Path_Tracking.h"
#include "Odometry.h"

#define Path_Array_Size 	150

Position_ST	OpenLoop_Points[Path_Array_Size];

void OpenLoop_PlotPathPoints();

void OpenLoop_MovingCar();



#endif /* APP_INC_OPENLOOP_PARKING_H_ */

/*
 * OpenLoop_PathTracking.h
 *
 *  Created on: Jul 23, 2024
 *      Author: Omar
 */

#ifndef APP_INC_OPENLOOP_PATHTRACKING_H_
#define APP_INC_OPENLOOP_PATHTRACKING_H_

#include"math.h"
#include"Odometry.h"


#define OP_PT_DELTA_X			2
#define FORWORD					1

void OP_PT_StartTracking(f32 (*Path_Func)(f32 x));

void OP_PT_GetNextPoint( f32 (*Path_Func)(f32 x) , f32 CurrentX,Position_ST* NextPoint  );  // takes function , current x

f32 OP_PT_GetSlopeOfFunc(f32 (*Path_Func)(f32 x),f32 x);

f32 OP_PT_GetDistBet2Points(Position_ST* Point1 , Position_ST* Point2 ); //  takes 2 points return distance

f32 OP_PT_GetArcAngle_Bet2Points(f32 (*Path_Func)(f32 x), f32 x1 , f32 x2);   // takes 2 points return angle

f32 OP_PT_CalculateSteering(f32 SegmentLength , f32 ArcAngle);   // takes distance and angle return steering

f32 OP_PT_CalculateArcLen(f32 SegmentLength , f32 ArcAngle);    // takes angle and radius return arclen



#endif /* APP_INC_OPENLOOP_PATHTRACKING_H_ */

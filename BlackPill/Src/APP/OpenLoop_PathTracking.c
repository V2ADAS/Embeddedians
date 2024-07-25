/*
 * OpenLoop_PathTracking.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Omar
 */

#include"Inc/OpenLoop_PathTracking.h"

Position_ST CurrentPoint = {0};
Position_ST NextPoint = {0} ;

void OP_PT_StartTracking(f32 (*Path_Func)(f32 x)){

	/* get next point --> x2,y2 */
	OP_PT_GetNextPoint(Path_Func, CurrentPoint.x, &NextPoint);
	/* get length of segment  --> h */
	f32 SegmentLength = OP_PT_GetDistBet2Points(&CurrentPoint, &NextPoint);
	/* get arc angle -->  theta */
	f32 Arc_Angle = OP_PT_GetArcAngle_Bet2Points(Path_Func, CurrentPoint.x, NextPoint.x);
	/* get angle steering */
	f32 Steering_Angle = OP_PT_CalculateSteering(SegmentLength, Arc_Angle);
	/* get distance to move --> s */
	f32 Arc_Length = OP_PT_CalculateArcLen(SegmentLength, Arc_Angle);

	// TODO : determine the direction ??
	CarCtrl_Move(FORWORD, Arc_Length, Steering_Angle, 50);

	/* Update Current Point */
	CurrentPoint.x = NextPoint.x ;
	CurrentPoint.y = NextPoint.y ;



}

void OP_PT_GetNextPoint( f32 (*Path_Func)(f32 x) , f32 CurrentX,Position_ST* NextPoint  ){

	NextPoint->x = CurrentX + OP_PT_DELTA_X;
	NextPoint->y = Path_Func(NextPoint->x);

}

f32 OP_PT_GetSlopeOfFunc(f32 (*Path_Func)(f32 x) , f32 x){

	f32 deltaY = Path_Func(x + 0.01) - Path_Func(x - 0.01) ;
	f32 deltaX = 0.02 ;

	// Calculate the angle using arc tangent
	f32 angle = atan2(deltaY, deltaX);

//	// Convert the angle from radians to degrees
//	angle = angle * (180.0 / PI);
	return angle ;
}

f32 OP_PT_GetDistBet2Points(Position_ST* Point1 , Position_ST* Point2 ){ //  takes 2 points return distance

	return sqrt( pow(Point2->x - Point1->x , 2) + pow(Point2->y - Point1->y , 2) );
}

f32 OP_PT_GetArcAngle_Bet2Points(f32 (*Path_Func)(f32 x), f32 x1 , f32 x2){// takes 2 points return angle

	f32 tangent1 = OP_PT_GetSlopeOfFunc(Path_Func, x1);
	f32 tangent2 = OP_PT_GetSlopeOfFunc(Path_Func, x2);

	return (tangent1 - tangent2) ;
}

f32 OP_PT_CalculateSteering(f32 SegmentLength , f32 ArcAngle){  // takes distance and angle return steering

	f32 Radius = (SegmentLength/2) / sin(ArcAngle/2) ;
	// TODO : Calculate steering from Radius
	f32 Steering = 0 ;
	return Steering ;
}

f32 OP_PT_CalculateArcLen(f32 SegmentLength , f32 ArcAngle){   // takes angle and radius return arclen

	// s = r*theata
	f32 Radius = (SegmentLength/2) / sin(ArcAngle/2) ;
	return (Radius * ArcAngle) ;
}





/*
 * OL_Auto_Parking.c
 *
 *  Created on: Jul 11, 2024
 *      Author: Amr Elmaghraby
 *
 */


#include "Inc/OpenLoop_Parking.h"

u16 Current_Location=0;

void OpenLoop_PlotPathPoints(){
	f32 Step_size = ( End_Point().x - Start_Point().x ) / Path_Array_Size;
	OpenLoop_Points[0].x = Start_Point().x;
	OpenLoop_Points[0].y = Start_Point().y;
	for(u16 i=1;i<Path_Array_Size;i++){
		OpenLoop_Points[i].x = OpenLoop_Points[0].x + Step_size;
		OpenLoop_Points[i].y = Test_Func(OpenLoop_Points[i].x);
	}
}

void OpenLoop_MovingCar(){
	u16 Dist = sqrt(   pow( OpenLoop_Points[Current_Location].x - OpenLoop_Points[Current_Location+1].x, 2 )
			+ pow( OpenLoop_Points[Current_Location].y - OpenLoop_Points[Current_Location+1].y, 2 )   );

	f32 deltaX = OpenLoop_Points[Current_Location+1].x - OpenLoop_Points[Current_Location].x;
	f32 deltaY = OpenLoop_Points[Current_Location+1].y - OpenLoop_Points[Current_Location].y;

	// Calculate the angle using arctangent
	f32 angle = atan2(deltaX, deltaY);

	// Convert the angle from radians to degrees
	angle = angle * (180.0 / PI);


}


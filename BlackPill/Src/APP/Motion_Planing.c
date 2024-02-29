#include "Inc/Motion_Planing.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MGPIO/MGPIO_int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"

// TODO: replace math.h with implementations as needed
#include <math.h>

Point_t point_CSA,point_SP,point_EP;   // Center point of the parking space
u8 GInit_D; // The distance between our car and the surrounding car, measured at the start point.

f32 _param_a = 0;
f32 _param_b = 0;

void Set_Param_A(f32 new_value) { _param_a = new_value; }
void Set_Param_B(f32 new_value) { _param_b = new_value; }

/*
  uses _param_a as the radius of the two circles.
  uses _param_b as the x-coord of the saddle point.
 */
f32 PaB_Path(f32 x) {
	f32 y;

	// check if given x-coord is in the first circle
	if (x <= _param_b) {
		// x-coord is on the first circle
		y = -sqrt(pow(_param_a, 2) - pow(x - _param_a, 2));
	} else {
		// x-coord is on the second circle

		// theta is the angle between the two centers and the vertical axis
		f32 sin_theta = 1 - _param_b / _param_a;

		// x_2 is the x-coord of the center of the second circle
		f32 x_2 = _param_a - 2 * _param_a * sin_theta;

		// y_2 is the y-coord of the center of the second circle
		f32 y_2 = - 2 * _param_a * sqrt(1 - pow(sin_theta, 2));

		y = sqrt(pow(_param_a, 2) - pow(x - x_2, 2)) + y_2;
	}

	return y;
}

// Perpendicular backward Path
f32 PeB_Path(f32 x) {
	// TODO: implement this.
	return -1;
}

// Perpendicular forward Path
f32 PeF_Path(f32 x) {
	// TODO: implement this.
	return -1;
}
void MP_PaB_Scan ()
{
	f64 Local_Distance=0;
	u8 Local_parkL, Local_parkW;
	static int i=0;
	static int count=0;
	HULTRA_vSendTrigger(PORTB, PIN12);
	HULTRA_vGetDistance(ULTRA_SONIC1,&Local_Distance);
	Scanned_Area[i++]=(u8)Local_Distance;

	if ((u8)Local_Distance > (Car_Width + Safety_Margin + GInit_D))
	{
		count++;
		if (count > 10) // back axis of the car point
		{
			point_EP.x =(Car_Width/2)+ GInit_D + (Local_Distance - (GInit_D )/2);
			point_EP.y = i; // no. of cm passed by the car starting from point(0,0)
		}
	}
	else
	{
		GInit_D=Local_Distance;
		count = 0;
		point_EP.y=0;
		point_EP.x=0;
	}
	if (count > Vth_Parallel)
	{
		Local_parkW = (u8)Local_Distance - GInit_D;
		Local_parkL = count ;
		// WE FOUND A PARKING SPACE
		// Start point of parking
		point_SP.x=0; // the car is moving on the y direction
		point_SP.y=i; // the moved distance (cm)
		// Center of scanned Area
		point_CSA.y=Local_parkL/2;
		point_CSA.x=Local_parkW/2;
	}
	//	MSYSTICK_vDelayms(1000);  // Wait for a second

}

void Scan(u8 Scanned_Area[])
{
	static int i=0;
	f64 Local_Distance=0;
	HULTRA_vSendTrigger(PORTB, PIN12);
	HULTRA_vGetDistance(ULTRA_SONIC1,&Local_Distance);
	Scanned_Area[i++]=(u8)Local_Distance;
}
void Process(u8 Scanned_Area[])
{
	u8 count=0;
	u8 Local_parkL, Local_parkW;
	for (int i=0;i<100;i++)
	{

		if ((u8)Scanned_Area[i] > (Car_Width + Safety_Margin + GInit_D))
		{
			count++;
			if (count > 10) // back axis of the car point
			{
				point_EP.x =(Car_Width/2)+ GInit_D + (Scanned_Area[i] - (GInit_D )/2);
				point_EP.y = i; // no. of cm passed by the car starting from point(0,0)
			}
		}
		else
		{
			GInit_D=Scanned_Area[i];
			count = 0;
			point_EP.y=0;
			point_EP.x=0;
		}
		if (count > Vth_Parallel)
		{
			Local_parkW = (u8)Scanned_Area[i] - GInit_D;
			Local_parkL = count ;
			// WE FOUND A PARKING SPACE
			// Start point of parking
			point_SP.x=0; // the car is moving on the y direction
			point_SP.y=i; // the moved distance (cm)
			// Center of scanned Area
			point_CSA.y=Local_parkL/2;
			point_CSA.x=Local_parkW/2;
		}
	}

}


void Plot_The_Path(Scenario_t Scenario , .../*path */ );


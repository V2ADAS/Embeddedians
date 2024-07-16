#include "Inc/Motion_Planing.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MGPIO/MGPIO_int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"
#include "Inc/Odometry.h"
// TODO: replace math.h with implementations as needed
#include <math.h>

Position_ST point_CSA,point_SP,point_EP;   // Center point of the parking space
u8 GInit_D; // The distance between our car and the surrounding car, measured at the start point.

f32 _param_a = 0;
f32 _param_b = 0;
f32 _param_c = 0;
f32 _param_d = 0;

void Set_Param_A(f32 new_value) { _param_a = new_value; }
void Set_Param_B(f32 new_value) { _param_b = new_value; }
void Set_Param_C(f32 new_value) { _param_c = new_value; }
void Set_Param_D(f32 new_value) { _param_d = new_value; }



/*
  uses _param_a as the x-coordinate of the final point (relative to the starting point)
  uses _param_b as the y-coordinate of the final point (relative to the starting point)
    > this is expected to be negative
  uses _param_c as the maximum radius, i.e. the radius of the final circle
  uses _param_d as the angle theta (in degrees)
    > this is the angle between the positive x-axis,
    > and the radius connecting the tangential point on the final circle.
    > this is also the angle of the car with the y-axis as it enters the second circle.
*/
 f32 circleLineCircle(f32 x) {
	f32 y;

	#define X_F _param_a
	#define Y_F _param_b
	#define R_M _param_c
	#define THETA (_param_d * M_PI / 180)

	// the x-coord of the second tangential point
	f32 x_2 = X_F - R_M + R_M * cos(THETA);

	// the y-coord of the second tangential point
	f32 y_2 = Y_F + R_M * sin(THETA);

	// the point at which the tangential line cuts the y-axis
	f32 c = x_2 / tan(THETA) + y_2;

	// the x-coord of the first tangential point
	f32 x_1 = - c * sin(THETA);

	// the radius of the first circle
	f32 R_1 = - c * (sin(THETA) + 1 / tan(THETA) + cos(THETA) / tan(THETA));

	if ((x >= 0) && (x < x_1)) {
		// first circle
		y = - sqrt(pow(R_1, 2) - pow(x - R_1, 2));
	} else if (x <= x_2) {
		// tangential line
		y = (x_2 - x) / tan(THETA) + Y_F + R_M * sin(THETA);
	} else if (x <= X_F) {
		// final circle
		y = sqrt(pow(R_M, 2) - pow(x - X_F + R_M, 2)) + Y_F;
	} else {
		return 1;
	}

	#undef X_F
	#undef Y_F
	#undef R_M
	#undef THETA

	return y;
}
/*
  uses _param_a as the radius of the two circles.
  uses _param_b as the x-coord of the saddle point.
 */

f32 line_path (f32 x){
	 f32 y = x ;
	 return y ;
}


f32 twoCircles(f32 x) {
	f32 y;

	#define R _param_a
	#define X_S _param_b

	// check if given x-coord is in the first circle
	if (x <= X_S) {
		// x-coord is on the first circle
		y = -sqrt(pow(R, 2) - pow(x - R, 2));
	} else {
		// x-coord is on the second circle

		// theta is the angle between the two centers and the vertical axis
		f32 sin_theta = 1 - X_S / R;

		// x_2 is the x-coord of the center of the second circle
		f32 x_2 = R - 2 * R * sin_theta;

		// y_2 is the y-coord of the center of the second circle
		f32 y_2 = - 2 * R * sqrt(1 - pow(sin_theta, 2));

		y = sqrt(pow(R, 2) - pow(x - x_2, 2)) + y_2;
	}

	#undef R
	#undef X_S

	return y;
}

// Parallel backward Path
f32 PaB_Path(f32 x) {
	return circleLineCircle(x);
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


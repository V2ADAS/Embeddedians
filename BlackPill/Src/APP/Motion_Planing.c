#include "Inc/Motion_Planing.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MGPIO/MGPIO_int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"

// TODO: replace math.h with implementations as needed
#include <math.h>

Point_t point_c;   // Center point of the parking space
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
void MP_ParallelScanProcess ()
{
	f64 Local_Distance=0;
	u8 Local_parkL, Local_parkW;
//	static int i=0;
	static int count=0;
	HULTRA_vSendTrigger(PORTB, PIN12);
	HULTRA_vGetDistance(ULTRA_SONIC1,&Local_Distance);
//	Scanned_Area[i]=(u8)Local_Distance;
//	i++;
	if (((u8)Local_Distance > Car_Width) )
	{
		count++;
	}
	else
	{
		count = 0;
	}
	if (count > Vth_Parallel)
	{
		Local_parkW = (u8)Local_Distance;
		Local_parkL = count ;
		// WE FOUND A PARKING SPACE
		point_c.y=Local_parkL/2;
		point_c.x=Local_parkW/2;
	}
	//	MSYSTICK_vDelayms(1000);  // Wait for a second

}

void Scan(u8 Scanned_Area[])
{
	static int i=0;
	f64 Local_Distance=0;
	HULTRA_vSendTrigger(PORTB, PIN12);
	HULTRA_vGetDistance(ULTRA_SONIC1,&Local_Distance);
	Scanned_Area[i]=(u8)Local_Distance;
	i++;
}
void Process(u8 Scanned_Area[])
{
	u8 count=0;
	u8 Local_parkL, Local_parkW;
	for (int i=0;i<100;i++)
	{
		if ((Scanned_Area[i] > Car_Width))
		{
			count++;
		}
		else
		{
			count=0;
		}

		if (count > Vth_Parallel)
		{
			Local_parkW = Scanned_Area[i];
			Local_parkL = count ;
			// WE FOUND A PARKING SPACE
			point_c.y=Local_parkL/2;
			point_c.x=Local_parkW/2;
		}
	}

}


void Plot_The_Path(Scenario_t Scenario , .../*path */ );


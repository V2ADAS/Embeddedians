#include "Inc/Motion_Planing.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MGPIO/MGPIO_int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"

// TODO: replace math.h with implementations as needed
#include <math.h>

f64 Distance1=0;
u8 speed,Car_Length=50,Car_width=35;
u8 vth,vth_pl,vth_pd,count=0;
u8 park_length, park_width;

Point_t point_c;
Scenario_t scenario;

u8 Scanned_Area[100];

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

void Scan_Process (u8 Scanned_Area[], u8 speed)
{
	vth_pl=Car_Length/speed; // parallel parking
	vth_pd=Car_width/speed; // perpendicular parking
	for (int i=0;i<100;i++)
	{
		HULTRA_vSendTrigger(PORTB, PIN12);
		HULTRA_vGetDistance(&Distance1, TIMER1, CH2);
		Scanned_Area[i]=(u8)Distance1;
		if (((u8)Distance1 > Car_width) && ((u8)Distance1 < Car_Length) )
		{
			scenario =PaB;
			vth=vth_pl;
			count++;
		}
		else if (((u8)Distance1 > Car_Length))
		{
			scenario =PeB;
			vth=vth_pd;
			count++;
		}
		if (count > vth)
		{
			park_length = (u8)Distance1;
			park_width = count * speed;
			// WE FOUND A PARKING SPACE
			// if the car moves 5cm per sec , then vth should be > 7 sec
			// if we are parking parallel & vth > 10 if prependicular
		}
		//	MSYSTICK_vDelayms(1000);  // Wait for a second
	}
	point_c.y=park_length/2;
	point_c.x=park_width/2;
}

void Scan(u8 Scanned_Area[])
{
	for (int i=0;i<100;i++)
	{
		HULTRA_vSendTrigger(PORTB, PIN12);
		HULTRA_vGetDistance(&Distance1, TIMER1, CH2);
		Scanned_Area[i]=(u8)Distance1;
	}
}
void Process(u8 Scanned_Area[])
{
	for (int i=0;i<100;i++)
	{
		if ((Scanned_Area[i] > Car_width) && (Scanned_Area[i] < Car_Length) )
		{
			scenario =PaB;
			vth=vth_pl;
			count++;
		}
		else if ((Distance1 > Car_Length))
		{
			scenario =PeB;
			vth=vth_pd;
			count++;
		}
		if (count > vth)
		{
			park_length = Distance1;
			park_width = count * speed;
			// WE FOUND A PARKING SPACE
			// if the car moves 5cm per sec , then vth should be > 7 sec
			// if we are parking parallel & vth > 10 if prependicular
		}
	}
	point_c.y=park_length/2;
	point_c.x=park_width/2;
}

void Plot_The_Path(Scenario_t Scenario , .../*path */ );


#include "Inc/Motion_Planing.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/MTIMER/MTIMER_Int.h"
#include "../MCAL/MGPIO/MGPIO_int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"
f64 Distance1=0;
u8 speed,Car_Length=50,Car_width=35;
u8 vth,vth_pl,vth_pd,count=0;
u8 park_length, park_width;

Point_t point_c;
Scenario_t scenario;

//parallel Backward Path
f32 PaB_Path (f32 x ){
	f32 y , a=1  , b=0 ;
	y = a * (x)*(x) + b ;
	return y ;
}


//Perpendicular backward Path
f32 PeB_Path (f32 x ){

}

//perpendicular forward Path
f32 PeF_Path (f32 x ){

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


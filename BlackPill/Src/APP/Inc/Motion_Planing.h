#ifndef MOTION_PLANNING_
#define MOTION_PLANNING_

#include "../../LIB/STD_TYPES.h"
#include "../Inc/Scenario_Select.h"


typedef struct 
{
    f32 x ;
    f32 y ;

}Point_t;


#define Car_Length  50
#define Car_Width   35
#define Safety_Margin 5
#define Vth_Parallel (1.5*Car_Length)
#define Array_Length  100
u8 Scanned_Area [Array_Length];
/*
    Parameter setter functions.
    
    These parameters must be set as needed before using any path function.

    Each function should define how it uses each parameter,
    and what values are expected.
*/
void Set_Param_A(f32 new_value);
void Set_Param_B(f32 new_value);

/*
    In Parallel Backwards Parking, returns the y-coordinate given 
    a specific x-coordinate on the parking motion path.

    The origin is assumed to be the starting point of the path.

    The car is represented using the center of the rear axle.

    The method used for parking is the two circles method.

    The Radius is the same for each circle,
    and should be set using Set_Param_A.

    The Saddle point is defined as the x-coordinate at which
    the path transitions from circle 1 to circle 2.
    and should be set using Set_Param_B.

    NOTE: all required parameters should be set before using this function
*/
f32 PaB_Path (f32 x);

//Perpendicular backward Path
f32 PeB_Path (f32 x);

//perpendicular forward Path
f32 PeF_Path (f32 x);

void MP_PaB_Scan();
void Scan(u8 Scanned_Area[]);
void Process(u8 Scanned_Area[]);

void Plot_The_Path(Scenario_t Scenario , .../*path */ );


#endif /*MOTION_PLANNING_*/

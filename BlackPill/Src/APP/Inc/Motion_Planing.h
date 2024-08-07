#ifndef MOTION_PLANNING_
#define MOTION_PLANNING_

#include "../../LIB/STD_TYPES.h"
#include "Scenario_Select.h"
#include "Odometry.h"

#define Car_Length  50
#define Car_Width   35
#define Safety_Margin 5
#define Vth_Parallel (1.5*Car_Length)
#define Array_Length  100
extern u8 Scanned_Area [Array_Length];

 typedef struct{
		f32 (*Func_Path)(f32 x) ;
 }MotionPlanning_Data_ST;
/*
    Parameter setter functions.

    These parameters must be set as needed before using any path function.

    Each function should define how it uses each parameter,
    and what values are expected.
*/
void Set_Param_A(f32 new_value);
void Set_Param_B(f32 new_value);
void Set_Param_C(f32 new_value);
void Set_Param_D(f32 new_value);

/*
    In Parallel Backwards Parking, returns the y-coordinate given
    a specific x-coordinate on the parking motion path.

    The origin is assumed to be the starting point of the path.

    The car is represented using the center of the rear axle.

    The current method used for parking is the Circle-Line-Circle method.

    - Two Circles Method:
        - The Radius is the same for each circle,
          and should be set using Set_Param_A.

        - The Saddle point is defined as the x-coordinate at which
          the path transitions from circle 1 to circle 2.
          and should be set using Set_Param_B.

    - Circle Line Circle Method:
        - The x-coordinate of the End-Point (relative to the starting point)
          should be set using Set_Param_A.

        - The y-coordinate of the End-Point (relative to the starting point)
          should be set using Set_Param_B (Expected to be negative).

        - The Radius of circle 2 is fixed as the minimum radius the car can handle.
          this is obtained by using the maximum steering angle.
          should be set using Set_Param_C.

        - The Angle (in degrees) at which the car starts moving on circle 2 is defined as
          the angle of the tangential point between the line and circle 2
          measured from the positive x-axis counter-clockwise.
          (this also the angle of the tangential line with the positive y-axis).
          sould be set using Set_Param_D.

    NOTES:
        - all required parameters should be set before using this function
        - all algorithms assume parking to the right.
*/
f32 line_path (f32 x);

f32 PaB_Path (f32 x);

//Perpendicular backward Path
f32 PeB_Path (f32 x);

//perpendicular forward Path
f32 PeF_Path (f32 x);
f32 GetSlopeOfFunc(f32 x);
void MP_PaB_Scan();
void Scan(u8 Scanned_Area[]);
void Process(u8 Scanned_Area[]);

void Plot_The_Path(Scenario_t Scenario , .../*path */ );


Position_ST Start_Point();

Position_ST End_Point();

f32 Test_Func(f32 x);

#endif /*MOTION_PLANNING_*/

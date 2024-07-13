#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../HAL/HMOTOR/HMOTOR.h"
#include "../../HAL/HSERVO/HSERVO_Int.h"

typedef struct {
	u8 Direction;
	s8 Steering ;
	u8 Speed;
	f32 Reduction_Ratio ;
}CarControl_Data_ST;
// Function to control the car movement and steering angle

void CarControl_Move(u8 Direction, f32 distance, s8 Steering , u8 speed , CarControl_Data_ST * CarControl_Data);

// The "distance & direction" are paremeters that must be specified in the path tracking!
// distance to move in cm 
/* dirction if his target point is greater than the currect point -> send FORWARD
            if his target point is smaller than the currect point -> send BACKWARD */ 
// The "angle" is a parameter that must be specified in the path tracking!


void Set_ReductionRatio(f32 Copy_f32Yaw);

void CarCtrl_UpdateScheduler();
void CarCtrl_Dispatcher();

f32 Get_ReductionRatio(void);
s8 getSteering ();

u8* getPrevDirection(); // return the previous direction of the car.
u8* getprevDegree();   // return the previous degree of the servo.

#endif // CAR_CONTROL_H

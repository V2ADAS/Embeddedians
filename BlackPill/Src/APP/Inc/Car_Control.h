#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../HAL/HMOTOR/HMOTOR.h"
#include "../../HAL/HSERVO/HSERVO_Int.h"


// Function to control the car movement and steering angle

void CarControl_Move(u8 Direction, f32 Distance, s8 Steering , u8 speed );

// The "distance & direction" are paremeters that must be specified in the path tracking!
// distance to move in cm 
/* dirction if his target point is greater than the currect point -> send FORWARD
            if his target point is smaller than the currect point -> send BACKWARD */ 
// The "angle" is a parameter that must be specified in the path tracking!


void Set_ReductionRatio(f32 Copy_f32Yaw);

f32 Get_ReductionRatio(void);
s8 getSteering ();
u8 GetSpeed();
u8* getPrevDirection(); // return the previous direction of the car.
u8* getprevDegree();   // return the previous degree of the servo.

#endif // CAR_CONTROL_H

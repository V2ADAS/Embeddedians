#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "../../HAL/HMOTOR/HMOTOR.h"
#include "../../HAL/HSERVO/HSERVO_Int.h"
#include "../../LIB/STD_TYPES.h"

// Function to control the car movement and steering angle

void CAR_CONTROL(u8 Direction, f32 Distance, s8 Degree);

// The "distance & direction" are paremeters that must be specified in the path tracking!
// distance to move in cm 
/* dirction if his target point is greater than the currect point -> send FORWARD
            if his target point is smaller than the currect point -> send BACKWARD */ 
// The "angle" is a parameter that must be specified in the path tracking!


u8* getPrevDirection(); // return the previous direction of the car.
u8* getprevDegree();   // return the previous degree of the servo.

#endif // CAR_CONTROL_H

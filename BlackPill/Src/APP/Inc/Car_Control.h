#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "../../HAL/HMOTOR/HMOTOR.h"
#include "../../HAL/HSERVO/HSERVO_Int.h"
#include "../../LIB/STD_TYPES.h"

// Function to control the car movement and steering angle

void CAR_CONTROL(u8 direction, f32 distance, s8 degree)

// The "distance & direction" are paremeters that must be specified in the path tracking!
// distance to move in cm 
/* dirction if his target point is greater than the currect point -> send FORWARD
            if his target point is smaller than the currect point -> send BACKWARD */ 
// The "angle" is a parameter that must be specified in the path tracking!


#endif // CAR_CONTROL_H

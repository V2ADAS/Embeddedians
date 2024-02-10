#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "../../HAL/HMOTOR/HMOTOR.h"
#include "../../HAL/HSERVO/HSERVO_Int.h"
#include "../../LIB/STD_TYPES.h"

// Function to initialize car control
void CAR_CONTROL_Init();

// Function to control the car movement
void CAR_CONTROL_Move(f32 distance, s8 direction);

// The "distance & direction" are paremeters that must be specified in the path tracking!
// distance to move in cm 
/* dirction if his target point is greater than the currect point -> send 1
            if his target point is smaller than the currect point -> send -1 */ 

// Function to control the steering angle of the car
void CAR_CONTROL_Steer(s8 angle);

// The "angle" is a parameter that must be specified in the path tracking!

#endif // CAR_CONTROL_H

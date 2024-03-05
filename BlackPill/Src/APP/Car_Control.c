#include "Inc/CAR_CONTROL.h"

// Define static variables to store previous values
static u8 prevDirection = FORWARD;
static u8 prevDegree = 0;

void CAR_CONTROL(u8 Direction, f32 Distance, s8 Degree){

    // Control the movement of the DC motor

    /*
        Specifing the speed! This can be determined by:
            - Obtaining information about the speed limitations of the DC motor (HW & SW).
            - Knowing the current operation, such as parking (low speed) or driving (high speed) - but defer this consideration for later.
            - Considering the size of the Distance: low speed for a short Distance and high speed for a long Distance - but defer this consideration for later.

        Also, specify the time for this speed, which can be easily calculated using the equation: Distance / speed.
    */ 

    // Steer the servo motor

    /*
        Positive value: Rotate clockwise
        Negative value: Rotate counterclockwise
        Note: The steering angle is limited to +- 45 Degrees.

        Due to the current mechanical design constraints, direct angle setting is not possible. 
        So, Gradual adjustments are required for steering control.
    */

    // Save the current direction and angle

    prevDirection = Direction;
    prevDegree = Degree;
    u8 speed = 50;


    HSERVO_vServoDeg(SERVO1, Degree);

    HAL_MOTOR_MOVE(Direction, speed, Distance);
}

// Access the static variables using pointers
u8* getPrevDirection() {
    return &prevDirection;
}

u8* getprevDegree() {
    return &prevDegree;
}
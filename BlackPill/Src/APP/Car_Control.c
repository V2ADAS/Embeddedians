#include "Inc/Car_Control.h"

// Define static variables to store previous values
static u8 prevDirection = FORWARD;
static u8 prevDegree = 0;

void CarControl_Move(u8 Direction, f32 distance, s8 Steering , u8 speed ){

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
    prevDegree = Steering;

    f32 RR = Reduction_Ratio(Steering);
    f32 Motor_distance = distance / RR ;


    HSERVO_vServoDeg(SERVO1, Steering);
    MSYSTICK_vDelayms(500);

    HAL_MOTOR_MOVE(DC_MOTOR,Direction, speed, Motor_distance);
}


f32 Reduction_Ratio(f32 Copy_f32Yaw){
//	f32 RR = 4.16 * pow(10, -8) * pow(Copy_f32Yaw, 4)
//                  - 7.5 * pow(10, -6) * pow(Copy_f32Yaw, 3)
//        		  + 0.00019 * pow(Copy_f32Yaw, 2)
//        		  - 0.00225 * Copy_f32Yaw + 1;
	return 0.85 ;
}




// Access the static variables using pointers
u8* getPrevDirection() {
    return &prevDirection;
}

u8* getprevDegree() {
    return &prevDegree;
}

#include "Inc/CAR_CONTROL.h"


void CAR_CONTROL_Move(f32 distance, s8 direction) {
    // Control the movement of the DC motor

    /*
        Specifing the speed! This can be determined by:
            - Obtaining information about the speed limitations of the DC motor (HW & SW).
            - Knowing the current operation, such as parking (low speed) or driving (high speed) - but defer this consideration for later.
            - Considering the size of the distance: low speed for a short distance and high speed for a long distance - but defer this consideration for later.

        Also, specify the time for this speed, which can be easily calculated using the equation: distance / speed.
    */ 

    u8 speed = 0;

    // HAL_MOTOR_MOVE(direction, speed);
}
 
void CAR_CONTROL_Steer(s8 angle) {
    // Steer the servo motor

    /*
        Positive value: Rotate clockwise
        Negative value: Rotate counterclockwise
        Note: The steering angle is limited to +- 45 degrees.

        Due to the current mechanical design constraints, direct angle setting is not possible. 
        So, Gradual adjustments are required for steering control.
    */


   if (angle > 0)
   {
        if (angle > 45)
        {
            angle = 45;
        }
        for (u8 i = 5; i < angle; i+5)
        {
            angle = 85 + i;
            // HSERVO_vServoDeg(angle,angle,angle);
        }
   }
   else
   {
        if (angle < -45)
        {
            angle = -45;
        }
        for (u8 i = -5; i > angle; i-5)
        {
            angle = 85 + i;
            // HSERVO_vServoDeg(angle,angle,angle);
        }
   }
   
}

*/
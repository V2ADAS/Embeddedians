/*
 *      File     :  Collision_Avoidance.c
 *      Layer    :  APP
 *  Created on   :  Feb 11, 2023
 *      Author   :  Mariam Hossam
 *      Brief    :  This file contains the implementation of the Collision_Avoidance module APIs
 */
#include "Inc/Collision_Avoidance.h"

static collisionAvoidanceFlag CA_Flag;

collisionAvoidanceFlag InitCollisionAvoidance(ULTRASONIC_ID_t ultrasonic_ID){
    u8 prevDirection = *(getPrevDirection());
	u8 prevAngle = *(getprevDegree());
	CA_Flag = STD_HIGH;
	HAL_MOTOR_STOP();
	switch(ultrasonic_ID){
	case F_US || FR_US || FL_US || B_US || BR_US || BL_US :
	    CAR_CONTROL(!prevDirection,5,-prevAngle);
	    CA_Flag = STD_LOW;
		break;
	case R_US:
		/*
	     * Implementation of scenario to avoid the collision from Right direction
	     */
		CA_Flag = STD_LOW;
		break;
	case L_US:
		/*
	     * Implementation of scenario to avoid the collision from Left direction
	     */
		CA_Flag = STD_LOW;
		break;
	}

    return CA_Flag;
}

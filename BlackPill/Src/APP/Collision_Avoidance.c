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
    CA_Flag = STD_HIGH;
	HAL_MOTOR_STOP();
	switch(ultrasonic_ID){
	case FR_US:
		FR_CA_Scenario();
		break;
	case FL_US:
		FL_CA_Scenario();
		break;
	case BR_US:
		BR_CA_Scenario();
		break;
	case BL_US:
		BL_CA_Scenario();
		break;
	case RF_US:
		RF_CA_Scenario();
		break;
	case RB_US:
		RB_CA_Scenario();
		break;
	case LF_US:
		LF_CA_Scenario();
		break;
	case LB_US:
		LB_CA_Scenario();
		break;
	}

    return CA_Flag;
}

void FR_CA_Scenario(){

	/*
	 * Implementation of scenario to avoid the collision from FR direction
	 */
	CA_Flag = STD_LOW;
}

void FL_CA_Scenario(){
	/*
	 * Implementation of scenario to avoid the collision from FL direction
	 */
	CA_Flag = STD_LOW;
}

void BR_CA_Scenario(){
	/*
	 * Implementation of scenario to avoid the collision from BR direction
     */
	CA_Flag = STD_LOW;

}

void BL_CA_Scenario(){
	/*
	 * Implementation of scenario to avoid the collision from BL direction
	 */
	CA_Flag = STD_LOW;
}

void RF_CA_Scenario(){
	/*
     * Implementation of scenario to avoid the collision from RF direction
	 */
	CA_Flag = STD_LOW;

}

void RB_CA_Scenario(){
	/*
	 * Implementation of scenario to avoid the collision from RB direction
	 */
	CA_Flag = STD_LOW;
}

void LF_CA_Scenario(){
	/*
	 * Implementation of scenario to avoid the collision from LF direction
	 */
	CA_Flag = STD_LOW;
}

void LB_CA_Scenario(){
	/*
	 * Implementation of scenario to avoid the collision from LB direction
	 */
	CA_Flag = STD_LOW;
}

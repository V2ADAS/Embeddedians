/*
 *      File     :  Collision_Avoidance.h
 *      Layer    :  APP
 *  Created on   :  Feb 11, 2023
 *      Author   :  Mariam Hossam
 *      Brief    :  This file contains all prototypes for the interfaces can be used In The Main Application to use the Collision_Avoidance module
 *
 *        ============================================================
 *      ||         -----------                      -----------       ||
 *      ||        |    U.S    |                    |    U.S    |      ||
 *      ||        |    F_L    |                    |    F_R    |      ||
 *      ||         -----------                      -----------       ||
 *      ||                                                            ||
 *      ||    -------                                     -------     ||
 *      ||   |       |                                   |       |    ||
 *      ||   |  U.S  |                                   |  U.S  |    ||
 *      ||   |  L_F  |                                   |  R_F  |    ||
 *      ||   |       |                                   |       |    ||
 *      ||    -------                                     -------     ||
 *      ||                                                            ||
 *      ||                                                            ||
 *      ||                        The Car Kit                         ||
 *      ||                                                            ||
 *      ||                                                            ||
 *      ||    -------                                     -------     ||
 *      ||   |       |                                   |       |    ||
 *      ||   |  U.S  |                                   |  U.S  |    ||
 *      ||   |  L_B  |                                   |  R_B  |    ||
 *      ||   |       |                                   |       |    ||
 *      ||    -------                                     -------     ||
 *      ||                                                            ||
 *      ||         -----------                    -----------         ||
 *      ||        |    U.S    |                  |    U.S    |        ||
 *      ||        |    B_L    |                  |    B_R    |        ||
 *      ||         -----------                    -----------         ||
 *        ============================================================
 *
 */

/*************************************************************************************************************************/
/*                                                    File Guard                                                         */
/*************************************************************************************************************************/

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../HAL/HMOTOR/HMOTOR.h"

typedef u8 collisionAvoidanceFlag;
/*************************************************************************************************************************/
/*                                             Enum for Ultrasonic ID                                                    */
/*************************************************************************************************************************/
typedef enum{
	FR_US=0,         /* FR for Forward_Right Ultrasonic  */
	FL_US,           /* FL for Forward_Left Ultrasonic   */
	BR_US,           /* BR for Backward_Right Ultrasonic */
	BL_US,           /* BL for Backward_Left Ultrasonic  */
	RF_US,           /* RF for Right_Forward Ultrasonic  */
	RB_US,           /* RB for Right_Backward Ultrasonic */
	LF_US,           /* LF for Left_Forward Ultrasonic   */
	LB_US            /* LB for Left_Backward Ultrasonic  */
}ULTRASONIC_ID_t;

/*************************************************************************************************************************/
/*                                                        APIs                                                           */
/*************************************************************************************************************************/

/*************************************************************************************************************************/
/*                                                01-InitCollisionAvoidance                                              */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    stops the motors and starts the collision avoidance scenario                               */
/*                            according to the selected ultrasonic                                                       */
/* @ Input parameters    :   @Param ultrasonic_ID :                                                                      */
/*                                       the ultrasonic ID to select which scenario to avoid collision                   */
/*                                       optioins :                                                                      */
/*                                       FR_US for Forward_Right Ultrasonic,  FL_US for Forward_Left Ultrasonic          */
/*                                       BR_US for Backward_Right Ultrasonic, BL_US for Backward_Left Ultrasonic         */
/*                                       RF_US for Right_Forward Ultrasonic,  RB_US for Right_Backward Ultrasonic        */
/*	                                     LF_US for Left_Forward Ultrasonic,   LB_US  for Left_Backward Ultrasonic        */
/* @ Return              :    collisionAvoidanceFlag  : Flag indicating if Collision Avoidance is Active                 */
/*                                       STD_LOW  if the selected scenario if finished                                   */
/*                                       STD_HIGH if the selected scenario if not finished                               */
/*************************************************************************************************************************/
collisionAvoidanceFlag InitCollisionAvoidance(ULTRASONIC_ID_t ultrasonic_ID);

/*************************************************************************************************************************/
/*                                                  02-FR_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Forward Right ultrasonic                    */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void FR_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  03-FL_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Forward Left ultrasonic                     */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void FL_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  04-BR_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Backward Right ultrasonic                   */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void BR_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  05-BL_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Backward Left ultrasonic                    */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void BL_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  06-RF_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Right Forward ultrasonic                    */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void RF_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  07-RB_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Right Backward ultrasonic                   */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void RB_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  08-LF_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Left Forward ultrasonic                     */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void LF_CA_Scenario();

/*************************************************************************************************************************/
/*                                                  09-LB_CA_Scenario                                                    */
/*-----------------------------------------------------------------------------------------------------------------------*/
/* @ Description         :    starts the collision avoidance scenario of the Left Backward ultrasonic                    */
/* @ Input parameters    :    void                                                                                       */
/* @ Return              :    void                                                                                       */
/*************************************************************************************************************************/
void LB_CA_Scenario();

#endif /*COLLISION_AVOIDANCE_H_*/

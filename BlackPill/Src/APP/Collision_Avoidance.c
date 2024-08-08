/*
 *      File     :  Collision_Avoidance.c
 *      Layer    :  APP
 *  Created on   :  Feb 11, 2023
 *      Author   :  Mariam Hossam
 *      Brief    :  This file contains the implementation of the Collision_Avoidance module APIs
 */
#include "Inc/Collision_Avoidance.h"
#include "Inc/App_Connection.h"
#include "../HAL/HMOTOR/HMOTOR.h"

static collisionAvoidanceFlag CA_Flag;

void LOC_Periodic_Update(void);
void LOC_Check(void);

void CollisionAvoidance_vInit(Enum_TIMER_NUM copy_u8TimerNum, u16 Copy_u16Periodic_msec){

	MTIMER_vPeriodicMS(copy_u8TimerNum, Copy_u16Periodic_msec);
	MTIMER_CallBack(copy_u8TimerNum, LOC_Periodic_Update);

}




//collisionAvoidanceFlag Enable_Collision_Avoidance(Enum_ULTRA_SONIC_NUM ultrasonic_ID){
//    u8 prevDirection = *(getPrevDirection());
//	u8 prevAngle = *(getprevDegree());
//	CA_Flag = STD_HIGH;
//	HAL_MOTOR_ForceStop(DC_MOTOR);
//	switch(ultrasonic_ID){
//	case F_US || FR_US || FL_US || B_US || BR_US || BL_US :
//	    CAR_CONTROL(!prevDirection,5,-prevAngle);
//	    CA_Flag = STD_LOW;
//		break;
//	case R_US:
//		/*
//	     * Implementation of scenario to avoid the collision from Right direction
//	     */
//		CA_Flag = STD_LOW;
//		break;
//	case L_US:
//		/*
//	     * Implementation of scenario to avoid the collision from Left direction
//	     */
//		CA_Flag = STD_LOW;
//		break;
//	}
//
//    return CA_Flag;
//}

void LOC_Periodic_Update(){

	//	HULTRA_vSendTrigger(PORTB, PIN12);

	HULTRA_vGetDistance(US_RF, &UltraSonics_ST.RF);
	HULTRA_vGetDistance(US_CF, &UltraSonics_ST.CF);
	HULTRA_vGetDistance(US_LF, &UltraSonics_ST.LF);

	HULTRA_vGetDistance(US_RC, &UltraSonics_ST.RC);
	HULTRA_vGetDistance(US_LC, &UltraSonics_ST.LC);

	HULTRA_vGetDistance(US_RB, &UltraSonics_ST.RB);
	HULTRA_vGetDistance(US_CB, &UltraSonics_ST.CB);
	HULTRA_vGetDistance(US_LB, &UltraSonics_ST.LB);

	LOC_Check();
}

//flag indicator to know whether it entered while or not
u8 flg =0;
void LOC_Check(void){
	s8 dir = internal_data.Car_Control.Direction;
	u8 spd = internal_data.Car_Control.Speed;
#if	CA_DYNAMIC
	u8 COLLISION_THRESHOLD = spd / SPD_THRESHOLD_RATIO;
#endif
	switch(dir){
	case FORWARD:
		while(UltraSonics_ST.CF <= COLLISION_THRESHOLD || UltraSonics_ST.RF <= COLLISION_THRESHOLD
				|| UltraSonics_ST.LF <= COLLISION_THRESHOLD){
			MGPIO_vSetPinAtomic(DC_Motor.PORT_N2, DC_Motor.PIN_N2, LOW);

			//			HULTRA_vSendTrigger(PORTB, PIN12);

			HULTRA_vGetDistance(US_CF, &UltraSonics_ST.CF);
			HULTRA_vGetDistance(US_RF, &UltraSonics_ST.RF);
			HULTRA_vGetDistance(US_LF, &UltraSonics_ST.LF);

			App_UpdateUltrasonicData();
			App_Tx_Data();

			flg = 1;
		}
		if(flg && spd){
			MGPIO_vSetPinAtomic(DC_Motor.PORT_N2, DC_Motor.PIN_N2, HIGH);
			flg=0;
		}
		break;
	case BACKWARD:
		while(UltraSonics_ST.CB <= COLLISION_THRESHOLD || UltraSonics_ST.RB <= COLLISION_THRESHOLD
				|| UltraSonics_ST.LB <= COLLISION_THRESHOLD){
			MGPIO_vSetPinAtomic(DC_Motor.PORT_N1, DC_Motor.PIN_N1, LOW);

			//			HULTRA_vSendTrigger(PORTB, PIN12);

			HULTRA_vGetDistance(US_CB, &UltraSonics_ST.CB);
			HULTRA_vGetDistance(US_RB, &UltraSonics_ST.RB);
			HULTRA_vGetDistance(US_LB, &UltraSonics_ST.LB);

			App_UpdateUltrasonicData();
			App_Tx_Data();


			flg=1;
		}
		if(flg && spd){
			MGPIO_vSetPinAtomic(DC_Motor.PORT_N1, DC_Motor.PIN_N1, HIGH);
			flg=0;
		}
		break;
	}
}


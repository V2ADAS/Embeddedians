/*
 * Personal_Parking.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Omar
 */

#ifndef APP_INC_PERSONAL_PARKING_H_
#define APP_INC_PERSONAL_PARKING_H_

#include"Car_History.h"
#include"../../HAL/HEPROM/MEPROM_Int.h"


typedef struct {

	u8 Parking_Buffer[CARHIST_BUFFER_SIZE][CARHIST_NEEDED_STATES];
	u16 Start_PTR;
	u16 End_PTR;
	Car_Histort_ST* Global_CarHistory_ST_PTR  ;

}PersonalParking_Data_ST;

void PersonalParking_StartSaving();
void PersonalParking_EndSaving();
void PersonalParking_Apply();



#endif /* APP_INC_PERSONAL_PARKING_H_ */

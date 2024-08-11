/*
 * Parking_Scanner.h
 *
 *  Created on: Aug 8, 2024
 *      Author: Hardware
 */

#ifndef APP_INC_PARKING_SCANNER_H_
#define APP_INC_PARKING_SCANNER_H_

#include "../../LIB/STD_TYPES.h"
#include "Auto_Parking.h"
#include "Scenario_Select.h"
#include "Odometry.h"

#define Car_Length  50
#define Car_Width   35
#define Safety_Margin 5
#define Vth_Parallel (1.5*Car_Length)
#define Vth_Perpendicular (1.5*Car_Width)
#define Array_Length  100
extern u8 Scanned_Area [2][Array_Length];


typedef enum{
	PaF,
	PaB,
	PeF,
	PeB,
}Enum_Parking_Scenarios;

typedef enum{
	Scan_Both,
	Scan_Right,
	Scan_Left,
}Enum_Scanning_Dir;

void Scanning_vInit(Enum_TIMER_NUM Copy_EnumTimerNum);


void Scanning_vStart(Enum_Parking_Scenarios Copy_EnumParkingScenario,Enum_Scanning_Dir Copy_EnumParkingScanningPos,
		Enum_TIMER_NUM Copy_enumTimerNum, Enum_TIMER_CHs Copy_enumTimerCh);



void PaF_Scan();
void PaB_Scan();
void PeF_Scan();
void PeB_Scan();

void Scan(u8 Scanned_Area[]);
void Process(u8 Scanned_Area[]);

#endif /* APP_INC_PARKING_SCANNER_H_ */

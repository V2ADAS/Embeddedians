#ifndef MOTION_PLANNING_
#define MOTION_PLANNING_

#include "../../LIB/STD_TYPES.h"
#include "../Inc/Scenario_Select.h"
typedef struct 
{
    u8 x ;
    u8 y ;

}Point_t;


u8 Scanned_Area [100] = {0};

Point_t Get_Current_location ();

Point_t Get_Next_location ();

void Scan(u8 Scanned_Area );

void Plot_The_Path(Scenario_t Scenario , .../*path */ );


#endif /*MOTION_PLANNING_*/
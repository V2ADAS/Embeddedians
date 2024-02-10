#ifndef MOTION_PLANNING_
#define MOTION_PLANNING_

#include "../../LIB/STD_TYPES.h"
#include "../Inc/Scenario_Select.h"


typedef struct 
{
    f32 x ;
    f32 y ;

}Point_t;



u8 Scanned_Area [100] ;
//parallel Backward Path
f32 PaB_Path (f32 x );

//Perpendicular backward Path
f32 PeB_Path (f32 x );

//perpendicular forward Path
f32 PeF_Path (f32 x );


void Scan(u8 Scanned_Area );

void Plot_The_Path(Scenario_t Scenario , .../*path */ );


#endif /*MOTION_PLANNING_*/

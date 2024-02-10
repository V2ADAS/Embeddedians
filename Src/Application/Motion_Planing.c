#include "Inc/Motion_Planing.h"


//parallel Backward Path
f32 PaB_Path (f32 x ){
	f32 y , a=1  , b=0 ;
	y = a * (x)*(x) + b ;
	return y ;
}


//Perpendicular backward Path
f32 PeB_Path (f32 x ){

}

//perpendicular forward Path
f32 PeF_Path (f32 x ){

}


void Scan(u8 Scanned_Area );

void Plot_The_Path(Scenario_t Scenario , .../*path */ );


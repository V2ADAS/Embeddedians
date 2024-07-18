#include "Inc/Car_Control.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "../MCAL/MSTK/MSYSTICK_Int.h"
#include "math.h"

// Define static variables to store previous values
u8 Direction = FORWARD;
s8 Steering = 0;
f32 RR = 0;


typedef struct{
	u8 direction ;
	s8 steering ;
	f32 distance ;
	u8 speed ;
	u8 isDone ;
	u8 isExcuted ;
	f32 totalDistance ;
}Process_TS;

Process_TS scheduler [100] = {
		{0 , 0 , 0 , 0 , 1 , 1 }
};

void CarCtrl_UpdateScheduler(){
	int i ;
	for (i = 1; i <( sizeof(scheduler)/sizeof(scheduler[0]) ); ++i) {
		scheduler[i].totalDistance = scheduler[i].distance + scheduler[i-1].totalDistance ;
		scheduler[i].isDone = (HAL_MOTOR_GetMovedDistance() >= scheduler[i].totalDistance );
	}
}

void CarCtrl_Dispatcher(CarControl_Data_ST * CarControl_Data){
	int i ;
	for (i = 1; i < ( sizeof(scheduler)/sizeof(scheduler[0]) ) ; ++i) {
		if ( !scheduler[i].isDone && !scheduler[i].isExcuted && scheduler[i-1].isDone){
			// Update CarControl Internal Data
			Set_ReductionRatio(Steering);
			CarControl_Data->Direction = scheduler[i].direction;
			CarControl_Data->Steering = scheduler[i].steering ;
			CarControl_Data->Speed = scheduler[i].speed ;
			CarControl_Data->Reduction_Ratio = Get_ReductionRatio();
			scheduler[i].distance = scheduler[i].distance / CarControl_Data->Reduction_Ratio  ;
			if(scheduler[i].steering > scheduler[i-1].steering)
				CarControl_Data->DircOfSteering = 1;
			else
				CarControl_Data->DircOfSteering = -1;
			// Start Car Control
			HSERVO_vServoDeg(SERVO1, scheduler[i].steering);
			for(u32 i=0 ; i<1000000 ; ++i);//delay
			HAL_MOTOR_StopDcAfterDistance(scheduler[i].distance);
			HAL_MOTOR_MOVE(DC_MOTOR, scheduler[i].direction, scheduler[i].speed);
			scheduler[i].isExcuted = 1 ;
		}
	}
}
void setSteering (u8 steering){
	Steering = steering ;
}

s8 getSteering (){
	return Steering ;
}

void CarControl_Move(u8 Direction, f32 distance, s8 Steering , u8 speed){

	static u8 iterator = 1 ;
	scheduler[iterator].direction = Direction;
	scheduler[iterator].steering = Steering ;
	scheduler[iterator].speed = speed ;
	scheduler[iterator].distance = distance ;
	iterator++ ;

}


void Set_ReductionRatio(f32 Copy_f32Yaw){
	if (Copy_f32Yaw < 0 ){
		Copy_f32Yaw *= -1 ;
	}
	RR = 4.16 * pow(10, -8) * pow(Copy_f32Yaw, 4)
         - 7.5 * pow(10, -6) * pow(Copy_f32Yaw, 3)
		 + 0.00019 * pow(Copy_f32Yaw, 2)
		 - 0.00225 * Copy_f32Yaw + 1;
}

f32 Get_ReductionRatio(void){
	return RR;
}

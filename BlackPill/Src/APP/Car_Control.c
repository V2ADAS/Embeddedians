#include "Inc/Car_Control.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "../MCAL/MSTK/MSYSTICK_Int.h"
#include "math.h"

// Define static variables to store previous values
s8 direction = FORWARD;
u8 speed ;
u8 dircOfSteering ;
s8 steering ;
f32 ReductionRatio = 1 ;


typedef struct{
	s8 direction ;
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


void Set_ReductionRatio(f32 Copy_f32Yaw){
	if (Copy_f32Yaw < 0 ){
		Copy_f32Yaw *= -1 ;
	}
	ReductionRatio = 4.16 * pow(10, -8) * pow(Copy_f32Yaw, 4)
        		 - 7.5 * pow(10, -6) * pow(Copy_f32Yaw, 3)
				 + 0.00019 * pow(Copy_f32Yaw, 2)
	- 0.00225 * Copy_f32Yaw + 1;
}

f32 Get_ReductionRatio(void){
	return ReductionRatio;
}

void setSteering (s8 copySteering){
	steering = copySteering ;
	Set_ReductionRatio(copySteering);

	if (copySteering > -5 || copySteering < 5 )
		dircOfSteering = 0 ;
	else if (copySteering < 0 )
		dircOfSteering = -1 ;
	else
		dircOfSteering = 1 ;


}

s8 getSteering (){
	return steering ;
}

void setSpeed (u8 copySpeed){
	speed = copySpeed ;
}

u8 getSpeed (){
	return speed ;
}

void setDirection (s8 copyDirection){
	direction = copyDirection ;
}

u8 getDirction (){
	return direction ;
}

void CarCtrl_UpdateScheduler(){
	int i ;
	for (i = 1; i <( sizeof(scheduler)/sizeof(scheduler[0]) ); ++i) {
		scheduler[i].totalDistance = scheduler[i].distance + scheduler[i-1].totalDistance ;
		scheduler[i].isDone = (HAL_MOTOR_GetMovedDistance() >= scheduler[i].totalDistance );
	}
}

void CarCtrl_Dispatcher(){
	int i ;
	for (i = 1; i < ( sizeof(scheduler)/sizeof(scheduler[0]) ) ; ++i) {
		if ( !scheduler[i].isDone && !scheduler[i].isExcuted && scheduler[i-1].isDone){
			// Start Car Control
			HSERVO_vServoDeg(SERVO1, scheduler[i].steering);
			for(u32 i=0 ; i<1000000 ; ++i);//delay
			HAL_MOTOR_StopDcAfterDistance(scheduler[i].distance);
			HAL_MOTOR_MOVE(DC_MOTOR, scheduler[i].direction, scheduler[i].speed);
			scheduler[i].isExcuted = 1 ;
		}
	}
}

void CarCtrl_UpdateData (CarControl_Data_ST * CarControl_Data){
	// Update CarControl Internal Data
	CarControl_Data->Direction = getDirction();
	CarControl_Data->Steering = getSteering() ;
	CarControl_Data->Speed = getSpeed();
	CarControl_Data->Reduction_Ratio = Get_ReductionRatio();
	CarControl_Data->DircOfSteering =  dircOfSteering ;
}

void CarCtrl_Move(s8 Direction, f32 distance, s8 Steering , u8 speed){

	static u8 iterator = 1 ;
	scheduler[iterator].direction = Direction;
	scheduler[iterator].steering = Steering ;
	scheduler[iterator].speed = speed ;
	scheduler[iterator].distance = distance / Get_ReductionRatio() ;
	iterator++ ;

}



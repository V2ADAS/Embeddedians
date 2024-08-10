#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../HAL/HMOTOR/HMOTOR.h"
#include "../../HAL/HSERVO/HSERVO_Int.h"

typedef struct {
	s8 Direction;
	s8 Steering ;
	s8 DircOfSteering ;
	u8 Speed;
	f32 Reduction_Ratio ;

}CarControl_Data_ST;


void Set_ReductionRatio(f32 Copy_f32Yaw);
f32 Get_ReductionRatio(void);

void setSteering (s8 copySteering);
s8 getSteering ();

void setSpeed (u8 copySpeed);
u8 getSpeed ();

void setDirection (s8 copyDirection);
s8 getDirction ();


void CarCtrl_UpdateScheduler();
void CarCtrl_Dispatcher();
void CarCtrl_UpdateData (CarControl_Data_ST * CarControl_Data);
void CarCtrl_Move(s8 Direction, f32 distance, s8 Steering , u8 speed);

u8* getPrevDirection(); // return the previous direction of the car.
u8* getprevDegree();   // return the previous degree of the servo.

#endif // CAR_CONTROL_H

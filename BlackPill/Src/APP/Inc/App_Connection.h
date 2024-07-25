/*
 * App_Connection.h
 *
 *  Created on: Jul 24, 2024
 *      Author: Hardware
 */

#ifndef APP_INC_APP_CONNECTION_H_
#define APP_INC_APP_CONNECTION_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/MUART/MUSART_Interface.h"

typedef struct{
	u8 start ;

	u16 US_RightForward ;
	u16 US_CenterForward ;
	u16 US_LeftForward ;
	u16 US_RightCenter ;
	u16 US_LeftCenter ;
	u16 US_RightBackward ;
	u16 US_CenterBackward ;
	u16 US_LeftBackward ;

	u32 TotalMovedDistance ;

	s16 Yaw_Compass ;
	s16 Yaw_MPU ;

	f32 var1 ;
	f32 var2 ;
	f32 var3 ;
	f32 var4 ;
	f32 var5 ;
}Data_ST ;

extern Data_ST App_Tx;

void App_Start_Connect(u8 Copy_u8UART_Num);

void App_Tx_Data();



#endif /* APP_INC_APP_CONNECTION_H_ */

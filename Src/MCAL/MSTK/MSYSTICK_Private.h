/*
 * MSTK_Private.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Hardware
 */

#ifndef MCAL_MSTK_MSYSTICK_PRIVATE_H_
#define MCAL_MSTK_MSYSTICK_PRIVATE_H_

#include"../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#define STK_BASE_ADD	0xE000E010


#define CLR				0
#define COUNT_FLAG		16
#define STK_EN			0
#define STK_INT			1
#define STK_CLK_SOURCE	2		//Clock Source Pin Number

typedef struct{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}STK_MemMap_t;


#define STK			((volatile STK_MemMap_t*) (STK_BASE_ADD))



#endif /* MCAL_MSTK_MSYSTICK_PRIVATE_H_ */

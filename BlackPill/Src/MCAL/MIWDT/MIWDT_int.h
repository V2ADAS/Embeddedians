/*
 * MIWDT_int.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Omar
 */

#ifndef MCAL_MIWDT_MIWDT_INT_H_
#define MCAL_MIWDT_MIWDT_INT_H_

/*************** PRESCALERS OPTIONS ***********************/

#define	HALF_SEC			0
#define _1_SEC				1
#define _2_SEC				2
#define _4_SEC				3
#define _8_SEC				4
#define _16_SEC				5
#define _32_SEC				6



/**************** Functions Prototypes *********************/

void MIWDG_vStart( u8 Local_u8TimeOut);

void MIWDG_vReload();


#endif /* MCAL_MIWDT_MIWDT_INT_H_ */

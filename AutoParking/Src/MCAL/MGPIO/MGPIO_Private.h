/*
 * MGPIO_Private.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Omar
 */

#ifndef MCAL_MGPIO_MGPIO_PRIVATE_H_
#define MCAL_MGPIO_MGPIO_PRIVATE_H_

#include"../../LIB/STD_TYPES.h"

/*************** ADDRESSES AND REGISTERS *****************************/

#define GPIOA_BASE_ADDR			0x40020000
#define GPIOB_BASE_ADDR			0x40020400
#define GPIOC_BASE_ADDR			0x40020800


/************** GPIO REIGISTERS ******************/


typedef struct {

	u32 MODER ;
	u32 OTYPER ;
	u32 OSPEEDR ;
	u32 PUPDR ;
	u32 IDR  ;
	u32 ODR ;
	u32 BSRR ;
	u32 LCKR ;
	u32 AFRL ;
	u32 AFRH ;

} GPIO_Mem_Map_t;

/*********** GPIO Registers Pointers ***************/

#define GPIOA			((volatile GPIO_Mem_Map_t*)(GPIOA_BASE_ADDR))
#define GPIOB			((volatile GPIO_Mem_Map_t*)(GPIOB_BASE_ADDR))
#define GPIOC			((volatile GPIO_Mem_Map_t*)(GPIOC_BASE_ADDR))


#endif /* MCAL_MGPIO_MGPIO_PRIVATE_H_ */

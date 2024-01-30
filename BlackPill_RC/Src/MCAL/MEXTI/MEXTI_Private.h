/*
 * MEXTI_Private.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Hardware
 */

#ifndef MCAL_MEXTI_MEXTI_PRIVATE_H_
#define MCAL_MEXTI_MEXTI_PRIVATE_H_

#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES.h"

#define EXTI_BASE_ADD		0x40013C00
#define SYSCFG_BASE_ADD		0x40013800

#define PIN_PER_REG		4
#define	BIT_PER_PIN		4
#define MASK4			15

typedef struct{
	u32 IMR;
	u32	EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}	EXTI_MemMap_t;

typedef struct{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 Reserved[2];
	u32 CMPCR;
} SYSCFG_MemMap_t;


#define EXTI		((volatile EXTI_MemMap_t *) EXTI_BASE_ADD)
#define SYSCFG		((volatile SYSCFG_MemMap_t *) SYSCFG_BASE_ADD)


#endif /* MCAL_MEXTI_MEXTI_PRIVATE_H_ */

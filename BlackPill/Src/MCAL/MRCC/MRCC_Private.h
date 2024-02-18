/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                   */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/* Description       : RCC_Prog.c --> implementations                                                  */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MRCC_MRCC_PRIVATE_H_
#define MCAL_MRCC_MRCC_PRIVATE_H_

/*******************************************************************************************************/
/*                                       LIB                                                           */
/*******************************************************************************************************/
#include"../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/***************************************************************************/
/*                      Base Address Of RCC Register                       */
/***************************************************************************/
#define RCC_Base_Add	0x40023800

/********************************************************************************************************/
/*                                            macros of RCC                                             */
/********************************************************************************************************/

#define RCC_HSE			0
#define RCC_HSI			1
#define RCC_PLL			2

/* CR: Clock Control Register */
#define HSEON	16
#define HSEBYP	18
#define CSSON	19
#define HSION	0
#define PLLON	24
#define HSIRDY	1
#define HSERDY	17
#define PLLRDY	25

/*CFGR: Clock Configuration Register*/
#define SW0			0
#define SW1			1
#define SWS0		2
#define SWS1		3
#define SWS_HSI		0
#define SWS_HSE		1
#define SWS_PLL		2

/**************************************************************************/
/* Register Definition :-                                                 */
/* Features    : Private File Can`t Be Edit By User                       */
/* Description :-                                                         */
/*               - #define :      YES                                     */
/*               - union   :      NO                                      */
/*               - struct  :      YES                                     */
/**************************************************************************/
typedef struct{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;
}RCC_MemMap_t;
/***************************************************************************/
/*                     Struct Macro Base Address Of RCC                    */
/***************************************************************************/
#define RCC		((volatile RCC_MemMap_t*) (RCC_Base_Add))


#endif /* MCAL_MRCC_MRCC_PRIVATE_H_ */

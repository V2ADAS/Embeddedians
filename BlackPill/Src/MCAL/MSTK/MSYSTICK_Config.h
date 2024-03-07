/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                   */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MSTK_MSYSTICK_CONFIG_H_
#define MCAL_MSTK_MSYSTICK_CONFIG_H_

/********************************************************************************************************/
/*                                            macros of systick                                         */
/********************************************************************************************************/

/*Define System Clock Speed in MHz*/
#define CLOCK	16

/*Initialize SysTick Clock Source*/
#define CLK_SOURCE		MSYSTICK_AHB8

#define MAX_LOAD_VALUE		16777215 //2^24 - 1

/*Clock Source ===> STK_CTRL bit 2 */
#define MSYSTICK_AHB	1
#define MSYSTICK_AHB8	0

#if CLK_SOURCE == MSYSTICK_AHB8
	#define STK_CLOCK		CLOCK/8.0
#elif CLK_SOURCE == MSYSTICK_AHB
	#define STK_CLOCK		CLOCK
#endif

#endif /* MCAL_MSTK_MSYSTICK_CONFIG_H_ */


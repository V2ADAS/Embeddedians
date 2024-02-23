/*************************************************************************************************************/
/* Author            : Amr Elmaghraby                                                               	     */
/* Version           : V1.0.6                                                                       	     */
/* Data              : 5 nov 2023                                                                  	         */
/* Module  Features  :                                                                                       */
/*      01- void MSYSTICK_vInit(void);                                                                       */
/*      02- void MSYSTICK_vStartTime(void);                                                                  */
/*      03- MSYSTICK_vCntTimer(Enum_Timer_Cont Copy_u8TimerCont)	                                         */
/*      04- void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay);                                                    */
/*      05- void MSYSTICK_vDelayms(u32 Copy_u32Delay);                                                       */
/*      06- f32 MSYSTICK_f32GetElapsedTime(void);                                                            */
/*      07- f32 MSYSTICK_f32GetRemainingTime(void);                                                          */
/*      08- void MSYSTICK_vStop(void);                                                                       */
/*      09- MSYSTICK_vCallBack(void (*ptr)(void))															 */
/*************************************************************************************************************/

    
/*************************************************************************************************************/
/*                                   guard of file will call on time in .c                            		 */
/*************************************************************************************************************/
#ifndef MCAL_MSTK_MSYSTICK_INT_H_
#define MCAL_MSTK_MSYSTICK_INT_H_

#include"../MTIMER/MTIMER_Int.h" //Include timer 'mainly for Enum_Timer_Cont'

/*************************************************************************************************************/
/*                                      01- MSYSTICK_vInit                                                   */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Initialize SYSTICK                                                    */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vInit(void);
/*************************************************************************************************************/

/*************************************************************************************************************/
/*                            	 		02- MSYSTICK_vStartTime 		                                     */
/*-----------------------------------------------------------------------------------------------------------*/
/**
 * @Description 	Starts or enables the SysTick timer for time keeping or other time-dependent operations.
 * @Note       		The SysTick timer is typically used for time-related operations in microcontroller systems.
 * @return 			void
 */
void MSYSTICK_vStartTime(void);
/************************************************************************************************************/

/************************************************************************************************************/
/*                    			 		03- MSYSTICK_vCntTimer			                                    */
/*----------------------------------------------------------------------------------------------------------*/
/**
 * @brief Controls the continuation or stopping of the SysTick timer.
 * @param Copy_u8TimerCont: The desired action for the SysTick timer.
 *                          Expected to be Enum_Timer_Cont ==> { StopTimer, ContinueTimer }
 * @return void
 */
void MSYSTICK_vCntTimer(Enum_Timer_Cont Copy_u8TimerCont);
/************************************************************************************************************/


/*************************************************************************************************************/
/*                                      04- MSYSTICK_vPeriodicMS                                             */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function with millisecond delay using interrupt                                */
/* 2- Function Input       -> @param Copy_u32Delay = desired delay in millisecond                            */                                                                                  
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay);
/*************************************************************************************************************/

/*************************************************************************************************************/
/*                                      05- MSYSTICK_vDelayms                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function with millisecond delay using polling                                  */
/* 2- Function Input       -> @param Copy_u32Delay = desired delay in millisecond                            */                                                                                   
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vDelayms(u32 Copy_u32Delay);
/*************************************************************************************************************/

/*************************************************************************************************************/
/*                                      06- MSYSTICK_f32GetElapsedTime                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to get the time passed since the systick started                      */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> Elapsed time (float)                                                           */
/*************************************************************************************************************/
f32 MSYSTICK_f32GetElapsedTime(void);
/*************************************************************************************************************/

/*************************************************************************************************************/
/*                                      07- MSYSTICK_f32GetRemainingTime                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to get the remaining time until the desired delay                     */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> Remaining time (float)                                                                          */
/*************************************************************************************************************/
f32 MSYSTICK_f32GetRemainingTime(void);
/*************************************************************************************************************/

/*************************************************************************************************************/
/*                                      08- MSYSTICK_vStop                                                   */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to stop systick                                                       */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vStop(void);
/*************************************************************************************************************/

/*************************************************************************************************************/
/*                          		   09- MSYSTICK_vCallBack 		                                         */
/*-----------------------------------------------------------------------------------------------------------*/
/**
 * @Description Sets a callback function to be executed when the SysTick timer expires.
 * @param ptr: Pointer to the callback function.
 * @Note        The callback function should have a void return type and no parameters.
 * @return void
 */
void MSYSTICK_vCallBack(void (*ptr)(void));
/*************************************************************************************************************/



#endif /* MCAL_MSTK_MSYSTICK_INT_H_ */

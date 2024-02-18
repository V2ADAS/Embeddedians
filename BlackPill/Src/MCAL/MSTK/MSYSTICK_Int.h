/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                   */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/* Module  Features  :                                                                                 */
/*      01- void MSYSTICK_vInit(void);                                                                 */
/*      02- void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay);                                              */
/*      03- void MSYSTICK_vDelayms(u32 Copy_u32Delay);                                                 */
/*      04- f32 MSYSTICK_u32GetElapsedTime(void);                                                      */
/*      05- f32 MSYSTICK_u32GetRemainingTime(void);                                                    */
/*      06- void MSYSTICK_vStop(void);                                                                 */
/*******************************************************************************************************/

    
/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MCAL_MSTK_MSYSTICK_INT_H_
#define MCAL_MSTK_MSYSTICK_INT_H_

/******************************************************************************************************/
/*                                      01- MSYSTICK_vInit                                                   */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Initialize SYSTICK                                                    */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vInit(void);
/*************************************************************************************************************/

/******************************************************************************************************/
/*                                      02- MSYSTICK_vPeriodicMS                                              */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function with millisecond delay using interrupt                                */
/* 2- Function Input       -> @param Copy_u32Delay = desired delay in millisecond                            */                                                                                  
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay);
/*************************************************************************************************************/

/******************************************************************************************************/
/*                                      03- MSYSTICK_vDelayms                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function with millisecond delay using polling                                  */
/* 2- Function Input       -> @param Copy_u32Delay = desired delay in millisecond                            */                                                                                   
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vDelayms(u32 Copy_u32Delay);
/*************************************************************************************************************/

/******************************************************************************************************/
/*                                      04- MSYSTICK_u32GetElapsedTime                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to get the time passed since the systick started                      */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> Elapsed time (float)                                                           */
/*************************************************************************************************************/
f32 MSYSTICK_u32GetElapsedTime(void);
/*************************************************************************************************************/

/******************************************************************************************************/
/*                                      05- MSYSTICK_u32GetRemainingTime                                                */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to get the remaining time until the desired delay                     */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> Remaining time (float)                                                                          */
/*************************************************************************************************************/
f32 MSYSTICK_u32GetRemainingTime(void);
/*************************************************************************************************************/

/******************************************************************************************************/
/*                                      06- MSYSTICK_vStop                                                   */
/*-----------------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function to stop systick                                                       */
/* 2- Function Input       -> void                                                                           */                   
/* 3- Function Return      -> void                                                                           */
/*************************************************************************************************************/
void MSYSTICK_vStop(void);
/******************************************************************************************************/

void MSYSTICK_vCallBack(void(*ptr) (void));


#endif /* MCAL_MSTK_MSYSTICK_INT_H_ */
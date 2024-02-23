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
/*                           				MCAL Components				                            	     */
/*************************************************************************************************************/
#include"MSYSTICK_Private.h"
#include"MSYSTICK_Config.h"
#include"MSYSTICK_Int.h"

/*************************************************************************************************************/
/*                        					Functions Implementations                                        */
/*************************************************************************************************************/

//Global Pointer to be used for SYSTICK IRQ Call back function
static void (*GLOBAL_SYSTICK_CallBack) (void)= STD_NULL;

/*************************************************************************************************************/
/**
 * @Description Initializes the SysTick timer.
 *
 * @Note        This function configures the SysTick timer's clock source and clears its enable flag.
 *
 * @return void
 */
void MSYSTICK_vInit(void) {
    // Configure the SysTick timer's clock source based on the selected CLK_SOURCE
    #if CLK_SOURCE == MSYSTICK_AHB8
        CLR_BIT(STK->CTRL, STK_CLK_SOURCE);
    #elif CLK_SOURCE == MSYSTICK_AHB
        SET_BIT(STK->CTRL, STK_CLK_SOURCE);
    #endif

    // Clear the SysTick timer enable flag
    CLR_BIT(STK->CTRL, STK_EN);
}
/*************************************************************************************************************/


/*************************************************************************************************************/
/**
 * @brief Starts or enables the SysTick timer for time keeping or other time-dependent operations.
 *
 * @note  This function loads the reload value, clears the current value register,
 * 			 and enables the SysTick timer.
 *
 * @return void
 */
void MSYSTICK_vStartTime(void) {
    // Load the reload value
    STK->LOAD = MAX_LOAD_VALUE;

    // Clear the current value register
    STK->VAL = 0;

    // Enable the SysTick timer
    SET_BIT(STK->CTRL, STK_EN);
}
/*************************************************************************************************************/
/**
 * @brief Controls the continuation or stopping of the SysTick timer.
 * @param Copy_u8TimerCont: The desired action for the SysTick timer.
 *                          Expected to be Enum_Timer_Cont ==> { StopTimer, ContinueTimer }
 * @return void
 */
void MSYSTICK_vCntTimer(Enum_Timer_Cont Copy_u8TimerCont) {
    // Check the desired action for the SysTick timer
    switch (Copy_u8TimerCont) {
        case StopTimer:
            // Disable the SysTick timer
            CLR_BIT(STK->CTRL, STK_EN);
            break;
        case ContinueTimer:
            // Enable the SysTick timer
            SET_BIT(STK->CTRL, STK_EN);
            break;
    }
}
/*************************************************************************************************************/

/**
 * @brief Configures the SysTick timer for generating periodic interrupts
 * 			with a specified delay in milliseconds.
 *
 * @param Copy_u32Delay: The delay in milliseconds for the periodic interrupt.
 *
 * @note  This function calculates the reload value based on the provided delay, loads the reload value,
 *        clears the current value register, sets the interrupt enable bit, and enables the SysTick timer.
 *        The provided delay is adjusted to prevent exceeding the maximum load value.
 *
 * @return void
 */
void MSYSTICK_vPeriodicMS(u32 Copy_u32Delay) {
    // Calculate the reload value in milliseconds
    if ((Copy_u32Delay * 1000 * STK_CLOCK) >= MAX_LOAD_VALUE) {
        Copy_u32Delay = MAX_LOAD_VALUE;
    } else {
        Copy_u32Delay = Copy_u32Delay * 1000 * STK_CLOCK;
    }

    // Load the reload value
    STK->LOAD = Copy_u32Delay - 1;

    // Clear the current value register
    STK->VAL = CLR;

    // Set the interrupt enable bit
    SET_BIT(STK->CTRL, STK_INT);

    // Enable the SysTick timer
    SET_BIT(STK->CTRL, STK_EN);
}
/*************************************************************************************************************/


/*************************************************************************************************************/
/**
 * @brief Delays the program execution for the specified duration in milliseconds using the SysTick timer.
 *
 * @param Copy_u32Delay: The delay duration in milliseconds.
 *
 * @note  This function disables the SysTick interrupt, calculates the reload value based on
 * 		  the provided delay,loads the reload value, clears the current value register,
 *		  enables the SysTick timer, waits for the
 *        SysTick timer to reach zero (polling), and finally disables the SysTick timer.
 *        The provided delay is adjusted to prevent exceeding the maximum load value.
 *
 * @return void
 */
void MSYSTICK_vDelayms(u32 Copy_u32Delay) {
    /* MAX Delay: ((1 or 8) / SYS_CLOCK) * 2^24 "1.04 sec for HSI" */

    // Disable SysTick interrupt
    CLR_BIT(STK->CTRL, STK_INT);

    // Calculate the reload value in milliseconds
    if ((Copy_u32Delay * 1000 * STK_CLOCK) >= MAX_LOAD_VALUE) {
        Copy_u32Delay = MAX_LOAD_VALUE;
    } else {
        Copy_u32Delay = Copy_u32Delay * 1000 * STK_CLOCK;
    }

    // Load the reload value
    STK->LOAD = Copy_u32Delay;

    // Clear the current value register
    STK->VAL = CLR;

    // Enable the SysTick timer
    SET_BIT(STK->CTRL, STK_EN);

    // Wait for the SysTick timer to reach zero (polling)
    while (!GET_BIT(STK->CTRL, COUNT_FLAG));

    // Disable the SysTick timer
    CLR_BIT(STK->CTRL, STK_EN);
}
/*************************************************************************************************************/

/*************************************************************************************************************/
/**
 * @brief Retrieves the elapsed time in milliseconds using the SysTick timer.
 * @note  This function calculates the elapsed time based on the difference between the SysTick LOAD and VAL registers.
 * @return f32: The elapsed time in milliseconds.
 */
f32 MSYSTICK_f32GetElapsedTime(void) {
    // Return time in milliseconds
    f32 Elapsed = (STK->LOAD - STK->VAL) * (1 / (STK_CLOCK * 1000.0));
    return Elapsed;
}
/*************************************************************************************************************/


/*************************************************************************************************************/
/**
 * @brief Retrieves the remaining time in milliseconds until the SysTick timer reaches zero.
 * @note  This function calculates the remaining time based on the current value in the SysTick VAL register.
 * @return f32: The remaining time in milliseconds.
 */
f32 MSYSTICK_f32GetRemainingTime(void) {
    // Return time in milliseconds
    return (STK->VAL) * (1 / (STK_CLOCK * 1000.0));
}
/*************************************************************************************************************/


/*************************************************************************************************************/
/**
 * @brief Stops or disables the SysTick timer.
 * @note  This function clears the SysTick timer enable bit, effectively stopping the timer.
 * @return void
 */
void MSYSTICK_vStop(void) {
    // Clear the SysTick timer enable bit to stop the timer
    CLR_BIT(STK->CTRL, STK_EN);
}
/*************************************************************************************************************/

/*************************************************************************************************************/
/**
 * @brief Sets a callback function to be executed when the SysTick timer expires.
 * @param ptr: Pointer to the callback function.
 * @note  The callback function should have a void return type and no parameters.
 * @return void
 */
void MSYSTICK_vCallBack(void (*ptr)(void)) {
    // Set the provided callback function pointer
    GLOBAL_SYSTICK_CallBack = ptr;
}

/*************************************************************************************************************/
/**
 * @brief SysTick Timer Interrupt Handler.
 * @note  Calls the callback function if it has been set.
 * @return void
 */
void SysTick_Handler(void) {
    // Check if a callback function is set and call it
    if (GLOBAL_SYSTICK_CallBack != STD_NULL) {
        GLOBAL_SYSTICK_CallBack();
    }
}
/*************************************************************************************************************/


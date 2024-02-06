/*
 * MTIMER_Int.h
 *
 *  Created on: Dec 19, 2023
 *      Author: Hardware
 */

#ifndef MCAL_MTIMER_MTIMER_INT_H_
#define MCAL_MTIMER_MTIMER_INT_H_
/*Timers*/
typedef enum{
	TIMER1=1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER9,
	TIMER10,
	TIMER11,
}Enum_TIMER_NUM;


/*Channels*/
typedef enum{
	CH1=1,
	CH2,
	CH3,
	CH4,
}Enum_TIMER_CHs;


/**
 * @brief Configures the specified timer for generating periodic interrupts with a delay in milliseconds.
 * @param Copy_u8TimerNum: The timer number to configure.
 * @param Copy_u32Delay: The delay in milliseconds for the periodic interrupt.
 */
void MTIMER_vPeriodicMS(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delay);


/**
 * @brief Configures the specified timer in PWM mode on a specific channel.
 * @param Copy_u8TimerNum: The timer number to configure.
 * @param Copy_u8Channel: The channel on which PWM is configured.
 * @param Copy_u16TotalTime_uSec: The total time period for the PWM signal in microseconds.
 * @param Copy_u16PositiveDutyCycle_uSec: The positive duty cycle of the PWM signal in microseconds.
 */
void MTIMER_vPWM(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel, u16 Copy_u16TotalTime_uSec, u16 Copy_u16PositiveDutyCycle_uSec);

/**
 * @brief Configures the specified timer to work as an Input Capture Unit (ICU) on a specific channel.
 * @param Copy_u8TimerNum: The timer number to configure.
 * @param Copy_u8Channel: The channel on which the Input Capture Unit is configured.
 */
void MTIMER_vICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel);


/**
 * @brief Retrieves the captured time value from an Input Capture event on the specified timer and channel.
 * @param Copy_u8TimerNum: The timer number from which to retrieve the captured time.
 * @param Copy_u8Channel: The channel on which the Input Capture event occurred.
 * @return The captured time value.
 */
u32 MTIMER_GET_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel);


/**
 * @brief Registers a callback function to be executed when the specified timer generates an interrupt.
 * @param Copy_u8TimerNum: The timer number for which the callback is registered.
 * @param ptr: A function pointer to the callback function.
 */
void MTIMER_CallBack(Enum_TIMER_NUM Copy_u8TimerNum, void (*ptr)(void));


#endif /* MCAL_MTIMER_MTIMER_INT_H_ */

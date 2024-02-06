/*
 * HULTRA_SONIC_Int.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Hardware
 */

#ifndef HAL_HULTRA_SONIC_HULTRA_SONIC_INT_H_
#define HAL_HULTRA_SONIC_HULTRA_SONIC_INT_H_

/**
 * @brief   Initialize ultrasonic sensor parameters including GPIO and timer configurations.
 *
 * @param   Copy_u8TimerNum: The timer number used for ultrasonic sensor measurement.
 * 			Should be one of the Timer Enum values {TIMER1,TIMER2,TIMER3,TIMER4,TIMER5,
 * 														 TIMER9,TIMER10,TIMER11}
 * @param   Copy_u8ChannelNum: The timer channel number used for ultrasonic sensor measurement.
 * 			Should be {CH1,CH2,CH3,CH4}
 *
 * @note    This function sets up the GPIO pins and configures the specified timer for ultrasonic sensor interfacing.
 *          The ultrasonic sensor parameters are stored in the ULTRA_NUM array based on the timer and channel numbers.
 */
void HULTRA_vInitialize(Enum_TIMER_NUM Copy_u8TimerNum, u8 Copy_u8ChannelNum);

/**
 * @brief   Send a trigger signal to an ultrasonic sensor.
 *
 * @param   Copy_u8Port: The GPIO port of the ultrasonic sensor trigger pin.
 * 			e.g..  {GPIOA, GPIOB, GPIOC}
 * @param   Copy_u8Pin: The GPIO pin of the ultrasonic sensor trigger.
 *			e.g..  {PIN1 , . . . , PIN15}
 * @note    This function sets the specified pin as an OUTPUT, raises it to HIGH for a short duration,
 *          then brings it back to LOW. It is typically used to initiate distance measurements in ultrasonic sensors.
 */
void HULTRA_vSendTrigger(u8 Copy_u8Port, u8 Copy_u8Pin);

/**
 * @brief   Get the distance measurement from an ultrasonic sensor.
 *
 * @param   Copy_f64Distance: Pointer to a variable to store the calculated distance.
 * @param   Copy_u8TimerNum: The timer number used for ultrasonic sensor measurement.
 * 			e.g.. 		TIMER1, ... , TIMER5,TIMER9,...,TIMER11
 * @param   Copy_u8ChannelNum: The timer channel number used for ultrasonic sensor measurement.
 *			e.g..		CH1, . . . , CH4
 * @note    This function calculates the distance based on the input from a specified timer channel.
 *          The calculated distance is stored in the variable pointed to by Copy_f64Distance.
 *          The formula used for the calculation assumes a speed of sound of 343 meters per second.
 *          The timer values are expected to represent the time taken for the ultrasonic signal to travel
 *          to an object and back, divided by 2 to get the one-way distance.
 */
void HULTRA_vGetDistance(f64* Copy_f64Distance, u8 Copy_u8TimerNum, u8 Copy_u8ChannelNum);


#endif /* HAL_HULTRA_SONIC_HULTRA_SONIC_INT_H_ */

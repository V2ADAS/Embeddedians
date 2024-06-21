/*******************************************************************************************************/
/* Author            : Amr ElMaghraby "ControllersTech"                                                */
/* Version           : V1.0.3                                                                          */
/* Data              : 17 Feb 2024                                                                     */
/* Description       : HLCD_Config.h --> implementations                                               */
/*******************************************************************************************************/

#ifndef HAL_HLCD_HLCD_CONFIG_H_
#define HAL_HLCD_HLCD_CONFIG_H_

// Define the slave address for the LCD. Change this according to your setup.
#define SLAVE_ADDRESS_LCD 0x27

// Define the total length of the LCD. Adjust this according to the requirements.
#define TOT_LCD_LENGTH 70

// Number of decimal places to consider when converting floating-point numbers to strings for LCD display
#define LCD_FLOAT_PRECISION	1

#endif /* HAL_HLCD_HLCD_CONFIG_H_ */

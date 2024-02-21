/*
 * MI2C_Config.h
 *
 *  Created on: Jan 28, 2024
 *      Author: Omar
 */

#ifndef MCAL_MI2C_MI2C_CONFIG_H_
#define MCAL_MI2C_MI2C_CONFIG_H_

/*The peripheral input clock frequency must be at least:
• 2 MHz in Sm mode
• 4 MHz in Fm mode
*/
#define I2C_PCLK	16  // in MHZ

#define SDA_PORT		PORTB
#define SCL_AF			MGPIO_ALTFUNC_I2C13

//#define I2C1_SDA		PIN7
//#define I2C1_SCL		PIN6
//
//
//#define I2C2_SDA		PIN3    // AF9 -> I2C2_3
//#define I2C2_SCL		PIN10
//
//
//#define I2C3_SDA		PIN4	// AF9 -> I2C2_3
//#define I2C3_SCL		PIN8	// -> PORTA

typedef enum {
    I2C1_SDA = PIN7,
    I2C1_SCL = PIN6,

    I2C2_SDA = PIN3,
    I2C2_SCL = PIN10,

    I2C3_SDA = PIN4,
    I2C3_SCL = PIN8
} I2C_GPIOConfig;



#endif /* MCAL_MI2C_MI2C_CONFIG_H_ */

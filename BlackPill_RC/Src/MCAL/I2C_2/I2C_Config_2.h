/*
 * I2C_Config.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef I2C_I2C_CONFIG_H_
#define I2C_I2C_CONFIG_H_

#define I2C1_SCL_PIN	6	// Could be 6 or 8 (configure it as you like)
#define I2C1_SDA_PIN	7	// Could be 7 or 9 (configure it as you like)

// Write the frequency in MHz
#define I2C_FREQ	16
// Write the time in microseconds
#define I2C_T_SCL	10 // TL and TH recommended to be 5

typedef struct{
	u8 speedMode;
	u8 addressSize;
	u8 speed;
	u16 address;
	u8 ACK;
}I2C_Config_t;

/* Speed Modes */
#define I2C_STANDARD	0
#define I2C_FAST		1

/* Address Sizes */
#define I2C_7_BIT		0
#define I2C_10_BIT		1

/* ACK */
#define I2C_ACK_DIS		0
#define I2C_ACK_EN		1


typedef struct{
	u8* data;
	u8 len;
	u8 slaveAddress;
	u8 repeatedStart;
	u8 TxOrRx;
	u8 index;
	u8 runningState;
}I2C_HandleIT_t;

/* TX or RX */
#define I2C_TX_MODE	0
#define I2C_RX_MODE 1

/* Running State */
#define I2C_FINISHED		0
#define I2C_RUNNING			1
#define I2C_ERROR_BERR		2
#define I2C_ERROR_ARLO		3
#define I2C_ERROR_AF		4
#define I2C_ERROR_OVR		5
#define I2C_ERROR_PECERR	6
#define I2C_ERROR_TIMEOUT	7

#endif /* I2C_I2C_CONFIG_H_ */

/*
 * HAL_COMPASS.h
 *
 *  Created on: Dec 19, 2023
 *      Author: Omar
 */

#ifndef HAL_COMPASS_HAL_COMPASS_H_
#define HAL_COMPASS_HAL_COMPASS_H_

/* The register pointer will be incremented by 1 automatically after the current register has been read
successfully.*/

/*The bus bit format is an 8-bit Data/Address
send and a 1-bit acknowledge bit*/

/*Negative binary values will be in two’s complement form*/

/*The HMC5883L Serial Clock (SCL) and Serial Data (SDA) lines require resistive pull-ups (Rp) between the master device
(usually a host microprocessor) and the HMC5883L*/

/******************* Compass 7-bit Address ********************/
#define HAL_COMPASS_ADDRESS				(0x1E)

#define ADDRESS_PLUS_READ				(0x3D)
#define ADDRESS_PLUS_WRITE				(0x3C)

/* Defined in I2C bus Specs */
#define STD_SPEED					/*100k*/
#define FAST_SPEED					/*400k*/

#define CMP_ERROR_VAL				4096

typedef enum{

	ConfigREGA=0x00,/* Sampled Avreage , Data out rate , measure config*/
	ConfigREGB=0x01, /* gain */
	ModREG=0x02, /* operation mode */
	X_MSB=0x03, /*A*/
	X_LSB=0x04, /*B*/
	Z_MSB=0x05,
	Z_LSB=0x06,
	Y_MSB=0x07,
	Y_LSB=0x08,
	SR=0x09, /* LOCK , RDY */
	IdentREGA=0x0A,
	IdentREGB=0x0B,
	IdentREGC=0x0C,
} CMP_Mem_Map_t;

void HAL_CMP_vInit();
void HAL_CMP_GetReading();

#endif /* HAL_COMPASS_HAL_COMPASS_H_ */

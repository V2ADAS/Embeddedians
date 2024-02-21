/*
 * HAL_COMPASS.h
 *
 *  Created on: Dec 19, 2023
 *      Author: Omar
 */

#ifndef HAL_COMPASS_HAL_COMPASS_H_
#define HAL_COMPASS_HAL_COMPASS_H_

#include"../../LIB/STD_TYPES.h"
#include"../../MCAL/MI2C/MI2C_int.h"

/* The register pointer will be incremented by 1 automatically after the current register has been read
successfully.*/

/*The bus bit format is an 8-bit Data/Address
send and a 1-bit acknowledge bit*/

/*Negative binary values will be in two’s complement form*/

/*The HMC5883L Serial Clock (SCL) and Serial Data (SDA) lines require resistive pull-ups (Rp) between the master device
(usually a host microprocessor) and the HMC5883L*/

/******************* Compass 7-bit Address ********************/
#define COMPASS_ADDRESS					(0x0D)

#define COMPASS_I2C						I2C1

typedef enum{

	X_LSB = 0x00,
	X_MSB = 0x01,
	Y_LSB = 0x02,
	Y_MSB = 0x03,
	Z_LSB = 0x04,
	Z_MSB = 0x05,
	DOR_OVL_DRDY = 0x06,
	TOUT_LSB = 0x07,
	TOUT_MSB = 0x08,
	OSR_RNG_ODR_MODE = 0x09,
	SOFT_RST_ROL_INT = 0x0A,
	SET_RESET_PERIOD = 0x0B,
	RESERVED = 0x0C,
	CHIP_ID = 0x0D
} CMP_Mem_Map_t;



void HCOMPASS_vInit();
void HCOMPASS_vReadRowData(s16* PTR_RxRowData);
void HCOMPASS_vSetRowData();

f32 HCOMPASS_f32GetPitch();
f32 HCOMPASS_f32GetRoll() ;
f32 HCOMPASS_f32GetHeading();

void HCOMPASS_ApplyCalibration(s16 *raw, f32* calibrated);
void HCOMPASS_Calibrate(unsigned long calibrationDuration);
void HCOMPASS_SetCalibration(s16 x_min, s16 x_max, s16 y_min, s16 y_max, s16 z_min, s16 z_max);
void HCOMPASS_SetCalibrationOffsets(f32 x_offset, f32 y_offset, f32 z_offset);
void HCOMPASS_SetCalibrationScales(f32 x_scale, f32 y_scale, f32 z_scale);
f32 HCOMPASS_GetCalibrationOffset(u8 index);
f32 HCOMPASS_GetCalibrationScale(u8 index);
void HCOMPASS_ClearCalibration();


#endif /* HAL_COMPASS_HAL_COMPASS_H_ */

/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                                  */
/* Version           : V1.0.3                                                                          */
/* Data              : 28 March 2024                                                                   */
/* Description       : HMPU6050.h --> implementations                                                  */
/* Module  Features  :                                                                                 */
/*      01- HMPU_Init                                                                         		   */
/*      02- HMPU_Calibration                                                                           */
/*      03- HMPU_s16ReadRowData                                                                        */
/*      04- HMPU_s16GetYawAngle                                                                        */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef HAL_HMPU_MPU6050_T_H_
#define HAL_HMPU_MPU6050_T_H_

/*******************************************************************************************************/
/*                                    Include files needed for HSERVO_Int.h 		                   */
/*******************************************************************************************************/
#include"../../LIB/STD_TYPES.h" //Standard Types Lib
#include"../../MCAL/MTIMER/MTIMER_Int.h" //TIMER Control

//Define to enable all the readings from the mpu
// or to just read wanted data "Gyro z , Yaw"
#define MPU_ALL_READINGS	0

#define MPU_Add				0x68

#define FS_GYRO_250			0x00
#define FS_GYRO_500			0x08
#define FS_GYRO_1000		0x10
#define FS_GYRO_2000		0x18

#define FS_ACC_2G			0x00
#define FS_ACC_4G			0x08
#define FS_ACC_8G			0x10
#define FS_ACC_16G			0x18

#define REG_CONFIG_GYRO		27
#define REG_CONFIG_ACC		28
#define REG_PWR_MGMT_1		107
#define REG_INT_PIN			55
#define REG_INT_ENABLE		56
#define REG_INT_STATUS		58
#define REG_DATA			59
#define REG_GYRO_Z_DATA		71

#define REG_CONFIG_DLPF		0x1A
#define DLPF_CFG_0			0x00
#define DLPF_CFG_1			0x01
#define DLPF_CFG_2			0x02
#define DLPF_CFG_3			0x03
#define DLPF_CFG_4			0x04
#define DLPF_CFG_5			0x05
#define DLPF_CFG_6			0x06
#define DLPF_CFG_7			0x07

/*******************************************************************************************************/
/*                                          APIs                                                       */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      01- HMPU_vInit                                                 */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Initializing the MPU.
 *
 * Initializing the MPU device by configuring its various settings.
 * These settings include configuring the sensitivity of the gyroscope and accelerometer,
 * setting the Digital Low Pass Filter (DLPF) mode, and managing power settings.
 *
 * @param Copy_u8TiemrNum The enumeration representing the TIMER to be used for measuring elapsed time.
 *                         Expected to be Enum_TIMER_NUM.
 */
void HMPU_vInit(Enum_TIMER_NUM Copy_u8MPU_Timer);
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                    02- HMPU_vCalibration                                            */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Perform calibration for MPU (Motion Processing Unit) sensors.
 *
 * This function performs calibration for MPU sensors by averaging the sensor readings over
 *  	a specified number of iterations.
 * The calibration process aims to determine the offset values for accelerometer and gyroscope readings.
 *
 * @param num_iterations The number of iterations to perform for calibration.
 *                       A higher number of iterations may result in more accurate calibration but will
 *                       take longer to complete.
 */
void HMPU_vCalibration(u16 itr);
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                   03- HMPU_s16ReadRowData                                           */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Reads raw sensor data from the MPU (Motion Processing Unit).
 *
 * This function reads raw sensor data from the MPU device, including accelerometer, gyroscope,
 *  				and temperature data.
 * The raw data is then processed and converted to meaningful units before being stored
 * 				 in the provided array.
 *
 * @param ptr_RowData Pointer to an array where the sensor data will be stored.
 *                    The array must have a length of at least 7 elements to store all sensor readings.
 */
void HMPU_s16ReadRowData(s16 *ptr_RowData);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                 04- HMPU_f32GetYawAngle                                             */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Calculates the yaw angle using gyroscope data and elapsed time.
 *
 * This function integrates gyroscope data over time to calculate the yaw angle.
 * Gyroscope data is obtained from the MPU (Motion Processing Unit).
 *
 * @return The calculated yaw angle in degrees (floating-point value).
 */
void HMPU_UpdateYawAngle();
/*******************************************************************************************************/
f32 HMPU_f32GetYawAngle();

/******************************************TEST FUNCTIONS***********************************************/
void HMPU_vDMPtest();
void HMPU_tt(u8 * ptr_buffer);
void HMPU_r();
#endif /* HAL_HMPU_MPU6050_T_H_ */

















//
///*
// * MPU6050_t.h
// *
// *  Created on: Feb 22, 2024
// *      Author: Hardware
// */
//
//#ifndef HAL_HMPU_MPU6050_T_H_
//#define HAL_HMPU_MPU6050_T_H_
//
//#define MPU_Add				0x68
//
//#define FS_GYRO_250			0x00
//#define FS_GYRO_500			0x08
//#define FS_GYRO_1000		0x10
//#define FS_GYRO_2000		0x18
//
//#define FS_ACC_2G			0x00
//#define FS_ACC_4G			0x08
//#define FS_ACC_8G			0x10
//#define FS_ACC_16G			0x18
//
//#define REG_CONFIG_GYRO		27
//#define REG_CONFIG_ACC		28
//#define REG_PWR_MGMT_1		107
//#define REG_DATA			59
//
//#define REG_CONFIG_DLPF		0x1A
//#define DLPF_CFG_0			0x00
//#define DLPF_CFG_1			0x01
//#define DLPF_CFG_2			0x02
//#define DLPF_CFG_3			0x03
//#define DLPF_CFG_4			0x04
//#define DLPF_CFG_5			0x05
//#define DLPF_CFG_6			0x06
//#define DLPF_CFG_7			0x07
//
//void HMPU_vInit();
//
//void HMPU_u16Read(s16 *ptr_buffer);
//
//void HMPU_RPW();
//
//void HMPU_vCalibration();
//
//void HMPU_vtest();
//void HMPU_tt(u8 * ptr_buffer);
//void HMPU_r();
//#endif /* HAL_HMPU_MPU6050_T_H_ */

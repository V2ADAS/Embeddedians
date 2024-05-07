/*
 * MPU6050_t.h
 *
 *  Created on: Feb 22, 2024
 *      Author: Hardware
 */

#ifndef HAL_HMPU_MPU6050_T_H_
#define HAL_HMPU_MPU6050_T_H_

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
#define REG_DATA			59

#define REG_CONFIG_DLPF		0x1A
#define DLPF_CFG_0			0x00
#define DLPF_CFG_1			0x01
#define DLPF_CFG_2			0x02
#define DLPF_CFG_3			0x03
#define DLPF_CFG_4			0x04
#define DLPF_CFG_5			0x05
#define DLPF_CFG_6			0x06
#define DLPF_CFG_7			0x07

void HMPU_vInit();

void HMPU_u16Read(s16 *ptr_buffer);

void HMPU_RPW();

void HMPU_vCalibration();

void HMPU_vtest();
void HMPU_tt(u8 * ptr_buffer);
void HMPU_r();
#endif /* HAL_HMPU_MPU6050_T_H_ */

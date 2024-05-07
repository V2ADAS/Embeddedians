/*
 * MPU6050_t.c
 *
 *  Created on: Feb 22, 2024
 *      Author: Hardware
 */

#include"../../MCAL/MI2C/MI2C_int.h"
#include"../../MCAL/MTIMER/MTIMER_Int.h"
#include"../HLCD/HLCD_Int.h"
#include<stdio.h>
#include "math.h"

#include"MPU6050_t.h"

#define clk 8000000
#define DEG_TO_RAD 0.017453292519943295 // This is approximately pi/180

u8 Data1;
s16 buf[7];
u8 data[6];
s16 Accel_X_RAW = 0;
s16 Accel_Y_RAW = 0;
s16 Accel_Z_RAW = 0;

s16 TEMP_RAW=0;

s16 Gyro_X_RAW = 0;
s16 Gyro_Y_RAW = 0;
s16 Gyro_Z_RAW = 0;

s16 OFFSET_ACCEL_X=0;
s16 OFFSET_ACCEL_Y=0;
s16 OFFSET_ACCEL_Z=0;

s16 OFFSET_GYRO_X=0;
s16 OFFSET_GYRO_Y=0;
s16 OFFSET_GYRO_Z=0;

u16 Counter=0;

u8 fifoBuffer[64];

float GxL, GyL, GzL, Gx, Gy, Gz;

float velocityX = 0; // Initial velocity
float positionX = 0; // Initial position

float velocityY = 0; // Initial velocity
float positionY = 0; // Initial position

float elapsedTime=0.015, currentTime, previousTime;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ,yaw,roll,pitch;
// Assuming sensitivity is 8192 LSB/g, adjust this based on your sensor's datasheet
#define ACCEL_SENSITIVITY 16384.0
// Assuming sensitivity values for gyroscope (adjust based on your sensor's datasheet)
#define GYRO_SENSITIVITY 65.5
void HMPU_vInit(){
	u8 data[2] = {REG_CONFIG_GYRO,FS_GYRO_500};
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);

	data[0] = REG_CONFIG_ACC;
	data[1] = FS_ACC_2G;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);

	data[0] = REG_CONFIG_DLPF;
	data[1] = DLPF_CFG_4;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);

	data[0] = REG_PWR_MGMT_1;
	data[1] = 0;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
}

void HMPU_u16Read(s16 *ptr_buffer) {
	u8 data[] = {REG_DATA};
	u8 dat[14] = {0};

	// Send the register address to initiate the data read
	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);

	// Read 14 bytes of data from the MPU
	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 14);

	// Process the received data and store it in the ptr_buffer array
	ptr_buffer[0] = (s16)((dat[0] << 8) | dat[1]);
	ptr_buffer[1] = (s16)((dat[2] << 8) | dat[3]);
	ptr_buffer[2] = (s16)((dat[4] << 8) | dat[5]);
	ptr_buffer[3] = (s16)((dat[6] << 8) | dat[7]);
	ptr_buffer[4] = (s16)((dat[8] << 8) | dat[9]);
	ptr_buffer[5] = (s16)((dat[10] << 8) | dat[11]);
	ptr_buffer[6] = (s16)((dat[12] << 8) | dat[13]);

	// Convert accelerometer data to g-force (assuming sensitivity of 8192 LSB/g)
	ptr_buffer[0] = (	ptr_buffer[0] / ACCEL_SENSITIVITY	)	*	9.81;
	ptr_buffer[1] = (	ptr_buffer[1] / ACCEL_SENSITIVITY	)	*	9.81;
	ptr_buffer[2] = (	ptr_buffer[2] / ACCEL_SENSITIVITY	)	*	9.81;

	// Convert temperature data to degrees Celsius
	ptr_buffer[3] = (	(	ptr_buffer[3] / 340.0	) + 36.53	);

	// Convert gyroscope data to degrees per second (assuming sensitivity of 65.5 LSB/°/s)
	ptr_buffer[4] = (	ptr_buffer[4] / GYRO_SENSITIVITY	);
	ptr_buffer[5] = (	ptr_buffer[5] / GYRO_SENSITIVITY	);
	ptr_buffer[6] = (	ptr_buffer[6] / GYRO_SENSITIVITY	);
}

void HMPU_RPW(){

	// Read acceleration data from MPU
	HMPU_u16Read(buf);

	// Extract raw accelerometer data
	Accel_X_RAW = (buf[0] - OFFSET_ACCEL_X);
	Accel_Y_RAW = (buf[1] - OFFSET_ACCEL_Y);
	Accel_Z_RAW = (buf[2] - OFFSET_ACCEL_Z);

	// Calculate pitch and roll angles using accelerometer data
	accAngleX = (atan(Accel_Y_RAW / sqrt(pow(Accel_X_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error() custom function for more details
	accAngleY = (atan(-1 * Accel_X_RAW / sqrt(pow(Accel_Y_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) + 1.58; // AccErrorY ~(-1.58)

	// Extract raw gyroscope data
	Gyro_X_RAW = (buf[4] - OFFSET_GYRO_X);
	Gyro_Y_RAW = (buf[5] - OFFSET_GYRO_Y);
	Gyro_Z_RAW = (buf[6] - OFFSET_GYRO_Z);
	Gx = Gyro_X_RAW;
	Gy = Gyro_Y_RAW;
	Gz = Gyro_Z_RAW;

	// Calculate the time elapsed using a timer
	elapsedTime = MTIMER_f32GetElapsedTime(TIMER2, sec); // timer off
	MTIMER_vCntTimer(TIMER2, StopTimer);

	// Integrate gyroscope data to obtain angle changes
	gyroAngleX = gyroAngleX + Gx * elapsedTime; // deg/s * s = deg
	gyroAngleY = gyroAngleY + Gy * elapsedTime;
	yaw = yaw +  Gz * elapsedTime; //1.23
	velocityY=0;
	// Calculate velocity using acceleration data from accelerometer
	velocityX = Accel_X_RAW * elapsedTime;

	// Integrate velocity to get position
	positionX += velocityX * elapsedTime;

	// Turn on the timer
	MTIMER_vStartTime(TIMER2);

	// Combine accelerometer and gyroscope angles using a complementary filter
	roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
	pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

	// Display the yaw angle on the LCD
	HLCD_vPutCur(0, 4);
	HLCD_vSendNum(yaw);

	HLCD_vPutCur(1, 3);
	HLCD_vSendNum(positionX);

}

void HMPU_vCalibration(int num_iterations) {
	for (u16 i = 0; i < num_iterations; i++) {
		Counter=i;
		HMPU_u16Read(buf);
		OFFSET_ACCEL_X  += 	buf[0];
		OFFSET_ACCEL_Y  += 	buf[1];
		OFFSET_ACCEL_Z  += 	buf[2];
		OFFSET_GYRO_X   += 	buf[4];
		OFFSET_GYRO_Y   += 	buf[5];
		OFFSET_GYRO_Z   += 	buf[6];
		MSYSTICK_vDelayms(15);
	}
	OFFSET_ACCEL_X /= num_iterations;
	OFFSET_ACCEL_Y /= num_iterations;
	OFFSET_ACCEL_Z /= num_iterations;
	OFFSET_GYRO_X /= num_iterations;
	OFFSET_GYRO_Y /= num_iterations;
	OFFSET_GYRO_Z /= num_iterations;

}


void HMPU_vtest(){
	//Functions
	//9) Start Using DMP Hardware Features
	//Once the MPU and DMP have been set up and configured to use DMP hardware features, the DMP is ready
	//to process data and output the results into the FIFO.
	//To start using the DMP hardware features, please perform the following steps:
	//9.1) Reset and Enable FIFO & DMP:
	//
	u8 LPF[2]={0x1A,0x04};
	MI2C_vMasterTx(I2C1, MPU_Add, LPF, 2, WithStop);
	u8 data[2] = {0x23,0x78};
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
	//Write {0x40} bit 6 to USER_CTRL (0x6A)
	//Write {0x04} bit 2 to USER_CTRL (0x6A)
	//Write {0x80} bit 7 to USER_CTRL (0x6A)
	//Write {0x08} bit 3 to USER_CTRL (0x6A)
	data[0]=0x6A;
	data[1]=0xCC;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
	//9.2) Enable DMP Interrupt
	//Write {0x02} bit 1 to INT_ENABLE (0x38)
	data[0] = 0x37;
	data[1] = 0x00;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
	data[0] = 0x38;
	data[1] = 0x32;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
	//Interrupts will be sent from the DMP at the configured output rate.
	//Note that the bits auto-clear after one clock cycle.

}

void HMPU_tt(u8 * ptr_buffer){
	u8 data[] = {0x74};

	// Send the register address to initiate the data read
	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);

	// Read 14 bytes of data from the MPU
	MI2C_u8MasterRx(I2C1, MPU_Add, fifoBuffer, 64);

	Accel_X_RAW = fifoBuffer[28]<<8 | fifoBuffer[29];
	Accel_Y_RAW = fifoBuffer[32]<<8 | fifoBuffer[33];
	Accel_Z_RAW = fifoBuffer[36]<<8 | fifoBuffer[37];
	Gyro_X_RAW = fifoBuffer[16]<<8 | fifoBuffer[17];
	Gyro_Y_RAW = fifoBuffer[20]<<8 | fifoBuffer[21];
	Gyro_Z_RAW = fifoBuffer[24]<<8 | fifoBuffer[25];

	// Convert accelerometer data to g-force (assuming sensitivity of 8192 LSB/g)
	Accel_X_RAW = (Accel_X_RAW / ACCEL_SENSITIVITY)*9.81;
	Accel_Y_RAW = (Accel_Y_RAW / ACCEL_SENSITIVITY)*9.81;
	Accel_Z_RAW = (Accel_Z_RAW / ACCEL_SENSITIVITY)*9.81;

}
u16 Count;
void HMPU_r(){
	u8 data[] = {0x3A};
	u8 dat[]={0};
	HMPU_tt(buf);
	// Send the register address to initiate the data read
	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
	// Read 14 bytes of data from the MPU
	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 1);
	data[0] = 0x72;
	u8 dd[2] = {0};
	// Send the register address to initiate the data read
	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
	// Read 14 bytes of data from the MPU
	MI2C_u8MasterRx(I2C1, MPU_Add, dd, 2);
	Count = dd[0]<<8 | dd[1];

}









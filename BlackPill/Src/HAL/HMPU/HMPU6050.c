/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                                  */
/* Version           : V1.0.3                                                                          */
/* Data              : 28 March 2024                                                                   */
/* Description       : HMPU6050.h --> implementations                                                  */
/* Module  Features  :                                                                                 */
/*      01- HMPU_Init                                                                         		   */
/*      02- HMPU_Calibration                                                                           */
/*      02- HMPU_s16ReadRowData                                                                        */
/*      02- HMPU_s16GetYawAngle                                                                        */
/*******************************************************************************************************/

//Used for use of round
// #include<stdio.h>

#include "math.h"

#include"../../MCAL/MTIMER/MTIMER_Int.h"
#include"../../MCAL/MSTK/MSYSTICK_Int.h"
#include"../../MCAL/MI2C/MI2C_int.h"
#include"HMPU6050.h"

#define DEG_TO_RAD 0.017453292519943295 // This is approximately pi/180


#if MPU_ALL_READINGS
	s16 buf[7];
#else
	s16 buf[1];
#endif

#if MPU_ALL_READINGS
s16 Accel_X_RAW = 0;
s16 Accel_Y_RAW = 0;
s16 Accel_Z_RAW = 0;

s16 TEMP_RAW=0;
s16 Gyro_X_RAW = 0;
s16 Gyro_Y_RAW = 0;
#endif
s16 Gyro_Z_RAW = 0;

#if MPU_ALL_READINGS
s16 OFFSET_ACCEL_X=0;
s16 OFFSET_ACCEL_Y=0;
s16 OFFSET_ACCEL_Z=0;

s16 OFFSET_GYRO_X=0;
s16 OFFSET_GYRO_Y=0;
#endif
s16 OFFSET_GYRO_Z=0;

#if MPU_ALL_READINGS
float Gx;
float Gy;
#endif
float Gz;

float MPU_Yaw;
float elapsedTime;

u8 MPU_TIMER = 0;

// Assuming sensitivity is 8192 LSB/g, adjust this based on your sensor's datasheet
#define ACCEL_SENSITIVITY 16384.0
// Assuming sensitivity values for gyroscope (adjust based on your sensor's datasheet)
#define GYRO_SENSITIVITY 65.5

/*******************************************************************************************************/
/**
 * @brief Initializing the MPU.
 *
 * Initializing the MPU device by configuring its various settings.
 * These settings include configuring the sensitivity of the gyroscope and accelerometer,
 * setting the Digital Low Pass Filter (DLPF) mode, and managing power settings.
 */
void HMPU_vInit(Enum_TIMER_NUM Copy_u8MPU_Timer){

	MI2C_vMasterInit(I2C1);
	// Data array to hold register addresses and configuration values
	u8 data[2];

	// Configure gyroscope sensitivity to 500 degrees per second
	data[0] = REG_CONFIG_GYRO;  // Register address for gyroscope configuration
	data[1] = FS_GYRO_500;      // Gyroscope sensitivity configuration (500 degrees per second)
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C

	// Configure accelerometer sensitivity to 2G
	data[0] = REG_CONFIG_ACC;   // Register address for accelerometer configuration
	data[1] = FS_ACC_2G;        // Accelerometer sensitivity configuration (2G)
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C

	// Configure Digital Low Pass Filter (DLPF) mode
	data[0] = REG_CONFIG_DLPF;  // Register address for DLPF configuration
	data[1] = DLPF_CFG_4;       // DLPF mode configuration (Mode 4)
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C

	// Configure Interrupt
	data[0] = REG_INT_PIN;
	data[1] = 0b00010100;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C

	data[0] = 31;
	data[1] = 0x01;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C
	data[0] = REG_INT_ENABLE;
	//data[1] = 0b01011001;
	data[1] = 0b00000001;
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C

	//data[0] = REG_INT_STATUS;
	//data[1] = 0x00;

	// Set power management to default (wake up the device)
	data[0] = REG_PWR_MGMT_1;   // Register address for power management configuration
	data[1] = 0;                 // Default value (no sleep mode)
	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);  // Transmit configuration data over I2C

	//Set timer to be used with mpu
	MPU_TIMER = Copy_u8MPU_Timer;
}
/******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @brief Perform calibration for MPU (Motion Processing Unit) sensors.
 *
 * This function performs calibration for MPU sensors by averaging the sensor readings over
 *  				a specified number of iterations.
 * The calibration process aims to determine the offset values for accelerometer and gyroscope readings.
 *
 * @param itr The number of iterations to perform for calibration.
 *                       A higher number of iterations may result in more accurate calibration but
 *                        will take longer to complete.
 */
void HMPU_vCalibration(u16 itr) {
	// Loop for the specified number of iterations
	for (u16 i = 0; i < itr; i++) {
		// Read sensor data and accumulate values for calibration
		HMPU_s16ReadRowData(buf); // Read raw sensor data
		#if MPU_ALL_READINGS
		OFFSET_ACCEL_X += buf[0]; // Accumulate X-axis accelerometer readings
		OFFSET_ACCEL_Y += buf[1]; // Accumulate Y-axis accelerometer readings
		OFFSET_ACCEL_Z += buf[2]; // Accumulate Z-axis accelerometer readings
		OFFSET_GYRO_X += buf[4];  // Accumulate X-axis gyroscope readings
		OFFSET_GYRO_Y += buf[5];  // Accumulate Y-axis gyroscope readings
		OFFSET_GYRO_Z += buf[6];  // Accumulate Z-axis gyroscope readings
		#else
		OFFSET_GYRO_Z += buf[0];  // Accumulate Z-axis gyroscope readings
		#endif

		// Delay for stabilization before next iteration
		MSYSTICK_vDelayms(15);
	}

	// Calculate average offset values by dividing accumulated values by the number of iterations
	#if MPU_ALL_READINGS
	OFFSET_ACCEL_X /= itr; // Calculate average X-axis accelerometer offset
	OFFSET_ACCEL_Y /= itr; // Calculate average Y-axis accelerometer offset
	OFFSET_ACCEL_Z /= itr; // Calculate average Z-axis accelerometer offset
	OFFSET_GYRO_X /= itr;  // Calculate average X-axis gyroscope offset
	OFFSET_GYRO_Y /= itr;  // Calculate average Y-axis gyroscope offset
	#endif
	OFFSET_GYRO_Z /= itr;  // Calculate average Z-axis gyroscope offset
}
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
void HMPU_s16ReadRowData(s16 *ptr_RowData) {
	#if MPU_ALL_READINGS
	// Array to hold the register address to read data from
	u8 data[] = {REG_DATA};

	// Array to hold the received raw sensor data
	u8 dat[14] = {0};

	// Send the register address to initiate the data read
	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);

	// Read 14 bytes of data from the MPU
	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 14);

	// Process the received data and store it in the ptr_RowData array
	ptr_RowData[0] = (s16)((dat[0] << 8) | dat[1]); // Accelerometer X-axis
	ptr_RowData[1] = (s16)((dat[2] << 8) | dat[3]); // Accelerometer Y-axis
	ptr_RowData[2] = (s16)((dat[4] << 8) | dat[5]); // Accelerometer Z-axis
	ptr_RowData[3] = (s16)((dat[6] << 8) | dat[7]); // Temperature
	ptr_RowData[4] = (s16)((dat[8] << 8) | dat[9]); // Gyroscope X-axis
	ptr_RowData[5] = (s16)((dat[10] << 8) | dat[11]); // Gyroscope Y-axis
	ptr_RowData[6] = (s16)((dat[12] << 8) | dat[13]); // Gyroscope Z-axis

	// Convert accelerometer data to g-force (assuming sensitivity of 8192 LSB/g)
	ptr_RowData[0] = (ptr_RowData[0] / ACCEL_SENSITIVITY) * 9.81;
	ptr_RowData[1] = (ptr_RowData[1] / ACCEL_SENSITIVITY) * 9.81;
	ptr_RowData[2] = (ptr_RowData[2] / ACCEL_SENSITIVITY) * 9.81;

	// Convert temperature data to degrees Celsius
	ptr_RowData[3] = ((ptr_RowData[3] / 340.0) + 36.53);

	// Convert gyroscope data to degrees per second (assuming sensitivity of 65.5 LSB/°/s)
	ptr_RowData[4] = (ptr_RowData[4] / GYRO_SENSITIVITY);
	ptr_RowData[5] = (ptr_RowData[5] / GYRO_SENSITIVITY);
	ptr_RowData[6] = (ptr_RowData[6] / GYRO_SENSITIVITY);

	#else
//	MI2C_vMasterInit(I2C1);
	// Array to hold the register address to read data from
	u8 data[] = {REG_GYRO_Z_DATA};

	// Array to hold the received raw sensor data
	u8 dat[2] = {0};

	// Send the register address to initiate the data read
	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);

	// Read 6 bytes of data from the MPU
	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 2);

	// Process the received data and store it in the ptr_RowData array
	ptr_RowData[0] = (s16)((dat[0] << 8) | dat[1]); // Gyroscope Z-axis

	// Convert gyroscope data to degrees per second (assuming sensitivity of 65.5 LSB/°/s)
	ptr_RowData[0] = (ptr_RowData[0] / GYRO_SENSITIVITY);

	#endif

//	data[0] = REG_INT_STATUS;
//	// Send the register address to initiate reading int status reg
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//
//	// Read int status reg to clear all int
//	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 1);

}
/*******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @brief Calculates the yaw angle using gyroscope data and elapsed time.
 *
 * This function integrates gyroscope data over time to calculate the yaw angle.
 * Gyroscope data is obtained from the MPU (Motion Processing Unit).
 *
 * @param Copy_u8TiemrNum The enumeration representing the TIMER to be used for measuring elapsed time.
 *                         Expected to be Enum_TIMER_NUM.
 *
 * @return The calculated yaw angle in degrees (floating-point value).
 */
f32 accel_angle = 0;
f32 alpha = 0.5;
void HMPU_UpdateYawAngle() {

	// Read acceleration data from MPU
	HMPU_s16ReadRowData(buf);

	// Extract raw accelerometer data
	//Accel_X_RAW = (buf[0] - OFFSET_ACCEL_X);
	//Accel_Y_RAW = (buf[1] - OFFSET_ACCEL_Y);
	//Accel_Z_RAW = (buf[2] - OFFSET_ACCEL_Z);
	//accel_angle = atan2(Accel_X_RAW, Accel_Y_RAW);

	// Calculate pitch and roll angles using accelerometer data
	//accAngleX = (atan(Accel_Y_RAW / sqrt(pow(Accel_X_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error() custom function for more details
	//accAngleY = (atan(-1 * Accel_X_RAW / sqrt(pow(Accel_Y_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) + 1.58; // AccErrorY ~(-1.58)

	// Extract raw gyroscope data
	//Gyro_X_RAW = (buf[4] - OFFSET_GYRO_X);
	//Gyro_Y_RAW = (buf[5] - OFFSET_GYRO_Y);
	//Gz = (buf[6] - OFFSET_GYRO_Z);
	//Gx = Gyro_X_RAW;
	//Gy = Gyro_Y_RAW;

	// Integrate gyroscope data to obtain angle changes
	//gyroAngleX = gyroAngleX + Gx * elapsedTime; // deg/s * s = deg
	//gyroAngleY = gyroAngleY + Gy * elapsedTime;

	//velocityY=0;
	// Calculate velocity using acceleration data from accelerometer
	//velocityX = Accel_X_RAW * elapsedTime;

	// Integrate velocity to get position
	//positionX += velocityX * elapsedTime;

	// Extract Gyro Z Raw Data
	#if MPU_ALL_READINGS
		Gz = (buf[6] - OFFSET_GYRO_Z);
	#else
		Gz = (buf[0] - OFFSET_GYRO_Z);
	#endif
	// Calculate the time elapsed using a timer
	elapsedTime = MTIMER_f32GetElapsedTime(MPU_TIMER, sec); // timer off
	MTIMER_vCntTimer(MPU_TIMER, StopTimer);

	// Integrate gyroscope data to obtain angle changes
	//gyroAngleX = gyroAngleX + Gx * elapsedTime; // deg/s * s = deg
	//gyroAngleY = gyroAngleY + Gy * elapsedTime;
	MPU_Yaw = (MPU_Yaw +  Gz * elapsedTime) + (alpha * accel_angle); //1.23
	//velocityY=0;
	// Calculate velocity using acceleration data from accelerometer
	//velocityX = Accel_X_RAW * elapsedTime;

	// Integrate velocity to get position
	//positionX += velocityX * elapsedTime;

	// Turn on the timer
	MTIMER_vStartTime(MPU_TIMER);

	// Combine accelerometer and gyroscope angles using a complementary filter
	//roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
	//pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

	// Display the yaw angle on the LCD
	//HLCD_vPutCur(0, 4);
	//HLCD_vSendNum(yyaw);

	//HLCD_vPutCur(1, 3);
	//HLCD_vSendNum(positionX);
}
/*******************************************************************************************************/

f32 HMPU_f32GetYawAngle(){
	return MPU_Yaw;
}
/*******************************************************************************************************/



/*****************************************TEST Functions************************************************/
void HMPU_vDMPtest(){
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


//void HMPU_tt(u8 * ptr_RowData){
//	u8 data[] = {0x74};
//
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, fifoBuffer, 64);
//
//	Accel_X_RAW = fifoBuffer[28]<<8 | fifoBuffer[29];
//	Accel_Y_RAW = fifoBuffer[32]<<8 | fifoBuffer[33];
//	Accel_Z_RAW = fifoBuffer[36]<<8 | fifoBuffer[37];
//	Gyro_X_RAW = fifoBuffer[16]<<8 | fifoBuffer[17];
//	Gyro_Y_RAW = fifoBuffer[20]<<8 | fifoBuffer[21];
//	Gyro_Z_RAW = fifoBuffer[24]<<8 | fifoBuffer[25];
//
//	// Convert accelerometer data to g-force (assuming sensitivity of 8192 LSB/g)
//	Accel_X_RAW = (Accel_X_RAW / ACCEL_SENSITIVITY)*9.81;
//	Accel_Y_RAW = (Accel_Y_RAW / ACCEL_SENSITIVITY)*9.81;
//	Accel_Z_RAW = (Accel_Z_RAW / ACCEL_SENSITIVITY)*9.81;
//
//}
//u16 Count;
//void HMPU_r(){
//	u8 data[] = {0x3A};
//	u8 dat[]={0};
//	HMPU_tt(buf);
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 1);
//	data[0] = 0x72;
//	u8 dd[2] = {0};
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, dd, 2);
//	Count = dd[0]<<8 | dd[1];
//
//}






//
//
//
///*
// * MPU6050_t.c
// *
// *  Created on: Feb 22, 2024
// *      Author: Hardware
// */
//
//#include"../../MCAL/MI2C/MI2C_int.h"
//#include"../../MCAL/MTIMER/MTIMER_Int.h"
//#include"../HLCD/HLCD_Int.h"
//#include<stdio.h>
//#include "math.h"
//
//#include"HMPU6050.h"
//
//#define clk 8000000
//#define DEG_TO_RAD 0.017453292519943295 // This is approximately pi/180
//
//u8 Data1;
//s16 buf[7];
//u8 data[6];
//s16 Accel_X_RAW = 0;
//s16 Accel_Y_RAW = 0;
//s16 Accel_Z_RAW = 0;
//
//s16 TEMP_RAW=0;
//
//s16 Gyro_X_RAW = 0;
//s16 Gyro_Y_RAW = 0;
//s16 Gyro_Z_RAW = 0;
//
//s16 OFFSET_ACCEL_X=0;
//s16 OFFSET_ACCEL_Y=0;
//s16 OFFSET_ACCEL_Z=0;
//
//s16 OFFSET_GYRO_X=0;
//s16 OFFSET_GYRO_Y=0;
//s16 OFFSET_GYRO_Z=0;
//
//u16 Counter=0;
//
//u8 fifoBuffer[64];
//
//float GxL, GyL, GzL, Gx, Gy, Gz;
//
//float velocityX = 0; // Initial velocity
//float positionX = 0; // Initial position
//
//float velocityY = 0; // Initial velocity
//float positionY = 0; // Initial position
//
//float elapsedTime=0.015, currentTime, previousTime;
//float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ,yaw,roll,pitch;
//// Assuming sensitivity is 8192 LSB/g, adjust this based on your sensor's datasheet
//#define ACCEL_SENSITIVITY 16384.0
//// Assuming sensitivity values for gyroscope (adjust based on your sensor's datasheet)
//#define GYRO_SENSITIVITY 65.5
//void HMPU_vInit(){
//	u8 data[2] = {REG_CONFIG_GYRO,FS_GYRO_500};
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//
//	data[0] = REG_CONFIG_ACC;
//	data[1] = FS_ACC_2G;
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//
//	data[0] = REG_CONFIG_DLPF;
//	data[1] = DLPF_CFG_4;
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//
//	data[0] = REG_PWR_MGMT_1;
//	data[1] = 0;
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//}
//
//void HMPU_u16Read(s16 *ptr_buffer) {
//	u8 data[] = {REG_DATA};
//	u8 dat[14] = {0};
//
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 14);
//
//	// Process the received data and store it in the ptr_buffer array
//	ptr_buffer[0] = (s16)((dat[0] << 8) | dat[1]);
//	ptr_buffer[1] = (s16)((dat[2] << 8) | dat[3]);
//	ptr_buffer[2] = (s16)((dat[4] << 8) | dat[5]);
//	ptr_buffer[3] = (s16)((dat[6] << 8) | dat[7]);
//	ptr_buffer[4] = (s16)((dat[8] << 8) | dat[9]);
//	ptr_buffer[5] = (s16)((dat[10] << 8) | dat[11]);
//	ptr_buffer[6] = (s16)((dat[12] << 8) | dat[13]);
//
//	// Convert accelerometer data to g-force (assuming sensitivity of 8192 LSB/g)
//	ptr_buffer[0] = (	ptr_buffer[0] / ACCEL_SENSITIVITY	)	*	9.81;
//	ptr_buffer[1] = (	ptr_buffer[1] / ACCEL_SENSITIVITY	)	*	9.81;
//	ptr_buffer[2] = (	ptr_buffer[2] / ACCEL_SENSITIVITY	)	*	9.81;
//
//	// Convert temperature data to degrees Celsius
//	ptr_buffer[3] = (	(	ptr_buffer[3] / 340.0	) + 36.53	);
//
//	// Convert gyroscope data to degrees per second (assuming sensitivity of 65.5 LSB/°/s)
//	ptr_buffer[4] = (	ptr_buffer[4] / GYRO_SENSITIVITY	);
//	ptr_buffer[5] = (	ptr_buffer[5] / GYRO_SENSITIVITY	);
//	ptr_buffer[6] = (	ptr_buffer[6] / GYRO_SENSITIVITY	);
//}
//
//void HMPU_RPW(){
//
//	// Read acceleration data from MPU
//	HMPU_u16Read(buf);
//
//	// Extract raw accelerometer data
//	Accel_X_RAW = (buf[0] - OFFSET_ACCEL_X);
//	Accel_Y_RAW = (buf[1] - OFFSET_ACCEL_Y);
//	Accel_Z_RAW = (buf[2] - OFFSET_ACCEL_Z);
//
//	// Calculate pitch and roll angles using accelerometer data
//	accAngleX = (atan(Accel_Y_RAW / sqrt(pow(Accel_X_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error() custom function for more details
//	accAngleY = (atan(-1 * Accel_X_RAW / sqrt(pow(Accel_Y_RAW, 2) + pow(Accel_Z_RAW, 2))) * 180 / 3.14) + 1.58; // AccErrorY ~(-1.58)
//
//	// Extract raw gyroscope data
//	Gyro_X_RAW = (buf[4] - OFFSET_GYRO_X);
//	Gyro_Y_RAW = (buf[5] - OFFSET_GYRO_Y);
//	Gyro_Z_RAW = (buf[6] - OFFSET_GYRO_Z);
//	Gx = Gyro_X_RAW;
//	Gy = Gyro_Y_RAW;
//	Gz = Gyro_Z_RAW;
//
//	// Calculate the time elapsed using a timer
//	elapsedTime = MTIMER_f32GetElapsedTime(TIMER2, sec); // timer off
//	MTIMER_vCntTimer(TIMER2, StopTimer);
//
//	// Integrate gyroscope data to obtain angle changes
//	gyroAngleX = gyroAngleX + Gx * elapsedTime; // deg/s * s = deg
//	gyroAngleY = gyroAngleY + Gy * elapsedTime;
//	yaw = yaw +  Gz * elapsedTime; //1.23
//	velocityY=0;
//	// Calculate velocity using acceleration data from accelerometer
//	velocityX = Accel_X_RAW * elapsedTime;
//
//	// Integrate velocity to get position
//	positionX += velocityX * elapsedTime;
//
//	// Turn on the timer
//	MTIMER_vStartTime(TIMER2);
//
//	// Combine accelerometer and gyroscope angles using a complementary filter
//	roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
//	pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
//
//	// Display the yaw angle on the LCD
//	HLCD_vPutCur(0, 4);
//	HLCD_vSendNum(yaw);
//
//	//HLCD_vPutCur(1, 3);
//	//HLCD_vSendNum(positionX);
//
//}
//
//void HMPU_vCalibration(int num_iterations) {
//	for (u16 i = 0; i < num_iterations; i++) {
//		Counter=i;
//		HMPU_u16Read(buf);
//		OFFSET_ACCEL_X  += 	buf[0];
//		OFFSET_ACCEL_Y  += 	buf[1];
//		OFFSET_ACCEL_Z  += 	buf[2];
//		OFFSET_GYRO_X   += 	buf[4];
//		OFFSET_GYRO_Y   += 	buf[5];
//		OFFSET_GYRO_Z   += 	buf[6];
//		//HLCD_vPutCur(1, 5);
//		//HLCD_vSendNum(i);
//		MSYSTICK_vDelayms(15);
//	}
//	OFFSET_ACCEL_X /= num_iterations;
//	OFFSET_ACCEL_Y /= num_iterations;
//	OFFSET_ACCEL_Z /= num_iterations;
//
//	OFFSET_GYRO_X /= num_iterations;
//	OFFSET_GYRO_Y /= num_iterations;
//	OFFSET_GYRO_Z /= num_iterations;
//
//}
//
//
//void HMPU_vtest(){
//	//Functions
//	//9) Start Using DMP Hardware Features
//	//Once the MPU and DMP have been set up and configured to use DMP hardware features, the DMP is ready
//	//to process data and output the results into the FIFO.
//	//To start using the DMP hardware features, please perform the following steps:
//	//9.1) Reset and Enable FIFO & DMP:
//	//
//	u8 LPF[2]={0x1A,0x04};
//	MI2C_vMasterTx(I2C1, MPU_Add, LPF, 2, WithStop);
//	u8 data[2] = {0x23,0x78};
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//	//Write {0x40} bit 6 to USER_CTRL (0x6A)
//	//Write {0x04} bit 2 to USER_CTRL (0x6A)
//	//Write {0x80} bit 7 to USER_CTRL (0x6A)
//	//Write {0x08} bit 3 to USER_CTRL (0x6A)
//	data[0]=0x6A;
//	data[1]=0xCC;
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//	//9.2) Enable DMP Interrupt
//	//Write {0x02} bit 1 to INT_ENABLE (0x38)
//	data[0] = 0x37;
//	data[1] = 0x00;
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//	data[0] = 0x38;
//	data[1] = 0x32;
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 2, WithStop);
//	//Interrupts will be sent from the DMP at the configured output rate.
//	//Note that the bits auto-clear after one clock cycle.
//
//}
//
//void HMPU_tt(u8 * ptr_buffer){
//	u8 data[] = {0x74};
//
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, fifoBuffer, 64);
//
//	Accel_X_RAW = fifoBuffer[28]<<8 | fifoBuffer[29];
//	Accel_Y_RAW = fifoBuffer[32]<<8 | fifoBuffer[33];
//	Accel_Z_RAW = fifoBuffer[36]<<8 | fifoBuffer[37];
//	Gyro_X_RAW = fifoBuffer[16]<<8 | fifoBuffer[17];
//	Gyro_Y_RAW = fifoBuffer[20]<<8 | fifoBuffer[21];
//	Gyro_Z_RAW = fifoBuffer[24]<<8 | fifoBuffer[25];
//
//	// Convert accelerometer data to g-force (assuming sensitivity of 8192 LSB/g)
//	Accel_X_RAW = (Accel_X_RAW / ACCEL_SENSITIVITY)*9.81;
//	Accel_Y_RAW = (Accel_Y_RAW / ACCEL_SENSITIVITY)*9.81;
//	Accel_Z_RAW = (Accel_Z_RAW / ACCEL_SENSITIVITY)*9.81;
//
//}
//u16 Count;
//void HMPU_r(){
//	u8 data[] = {0x3A};
//	u8 dat[]={0};
//	HMPU_tt(buf);
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, dat, 1);
//	data[0] = 0x72;
//	u8 dd[2] = {0};
//	// Send the register address to initiate the data read
//	MI2C_vMasterTx(I2C1, MPU_Add, data, 1, WithoutStop);
//	// Read 14 bytes of data from the MPU
//	MI2C_u8MasterRx(I2C1, MPU_Add, dd, 2);
//	Count = dd[0]<<8 | dd[1];
//
//}
//
//
//
//
//
//
//


















/*
 * HAL_COMPASS.c
 *
 *  Created on: Dec 19, 2023
 *      Author: Omar
 */




#include"HAL_COMPASS.h"
#include"math.h"

#include"../../MCAL/MSTK/MSYSTICK_Int.h"
#include"../../MCAL/MSTK/MSYSTICK_Private.h"
#include"../../MCAL/MTIMER/MTIMER_Int.h"
#include"../../MCAL/MGPIO/MGPIO_int.h"
#include"../../MCAL/MEXTI/MEXTI_Int.h"
#include"../../MCAL/MNVIC/MNVIC_int.h"
#include"../../HAL/HEPROM/MEPROM_Int.h"

#define CalibrationSize			12

struct Compass_struct {
	s16 X;
	s16 Y;
	s16 Z;
} CompassData;

// Calibration variables
static s16 calibrationData[3][2] = {{32767, -32768}, {32767, -32768}, {32767, -32767}};

f32 Heading_Ref = 0;

f32 _offset[3] = {0.0, 0.0, 0.0};
f32 _scale[3] = {1.0, 1.0, 1.0};

void HCOMPASS_SetHeading_Ref(f32 Copy_f32Heading_Ref){
	Heading_Ref = Copy_f32Heading_Ref;
}

void HCOMPASS_RSTCalibration(void){

	calibrationData[0][0]=32767;
	calibrationData[0][1]=-32767;
	calibrationData[1][0]=32767;
	calibrationData[1][1]=-32767;
	calibrationData[2][0]=32767;
	calibrationData[2][1]=-32767;

	HEPROM_vWriteData(CMP_EPROM_PAGE, CMP_EPROM_PAGE_OFFSET, calibrationData, CalibrationSize);
	SET_BIT(STK->CTRL, STK_EN);
}

// Function to apply calibration to raw data
void HCOMPASS_ApplyCalibration(s16 *raw, f32* calibrated) {

	calibrated[0] = (raw[0] - _offset[0]) * _scale[0];
	calibrated[1] = (raw[1] - _offset[1]) * _scale[1];
	calibrated[2] = (raw[2] - _offset[2]) * _scale[2];
}

// Function to perform magnetometer calibration
void HCOMPASS_Calibrate(unsigned long calibrationDuration) {

	MSYSTICK_vInit();
	HCOMPASS_ClearCalibration();
	s16 raw[3];

	//s16 calibrationData[3][2] = {{32767, -32768}, {32767, -32768}, {32767, -32768}};
	s16 calibrationData[3][2] = {{-1043, 643}, {-1135, 326}, {0, 706}};
	//s16 calibrationData[3][2] = {{-1000, 600}, {-1100, 1000}, {-850, 1000}};
	//unsigned long startTime = millis();
	MSYSTICK_vPeriodicMS(8300);
	//MTIMER_vStartTime(TIMER2);
	MGPIO_vSetPinMode(PORTA,PIN10, OUTPUT);
	MGPIO_vSetPinValue(PORTA, PIN10, HIGH);
	u8 Exit_flag = 2;
	while (Exit_flag) {

		if(MSYSTICK_f32GetElapsedTime() > calibrationDuration){
			MSYSTICK_vPeriodicMS(8300);
			Exit_flag--;
		}
		HCOMPASS_vSetRowData();
		HCOMPASS_vReadRowData(raw);

		for (u8 i = 0; i < 3; ++i) {
			if (raw[i] < calibrationData[i][0]) {
				calibrationData[i][0] = raw[i];
			}
			if (raw[i] > calibrationData[i][1]) {
				calibrationData[i][1] = raw[i];
			}
		}
	}

	//MTIMER_vCntTimer(TIMER2, StopTimer);
	MSYSTICK_vStop();
	MGPIO_vSetPinValue(PORTA, PIN10, LOW);
	HCOMPASS_SetCalibration(
			calibrationData[0][0], calibrationData[0][1],
			calibrationData[1][0], calibrationData[1][1],
			calibrationData[2][0], calibrationData[2][1]
	);
}


void HCOMPASS_vInit(){

	MI2C_vMasterInit(COMPASS_I2C);

	/* SET/RESET Period : It is recommended that the register 0BH is written by 0x01*/
	/* Write Register 0BH by 0x01 (Define Set/Reset period) */
	u8 Local_TxData[]={SET_RESET_PERIOD,0x01};
	MI2C_vMasterTx(COMPASS_I2C,COMPASS_ADDRESS,Local_TxData,2,WithStop);

	/* Write Register 09H by 0x1D
	 * (Define OSR = 512, Full Scale Range = 8 Gauss, ODR = 200Hz,
	 *  set continuous measurement mode)
	 */
	Local_TxData[0]=OSR_RNG_ODR_MODE;
	Local_TxData[1]=0x1D;
	MI2C_vMasterTx(COMPASS_I2C,COMPASS_ADDRESS,Local_TxData,2,WithStop);

	//HCOMPASS_Calibrate(8000);
	u8 EPROM_CalibratingData[CalibrationSize];
	HEPROM_vReadData(CMP_EPROM_PAGE,CMP_EPROM_PAGE_OFFSET,EPROM_CalibratingData ,CalibrationSize);
	/* x min */
	calibrationData[0][0]= (s16)(EPROM_CalibratingData[1]<<8) | EPROM_CalibratingData[0] ;
	/* x max */
	calibrationData[0][1]= (s16)(EPROM_CalibratingData[3]<<8) | EPROM_CalibratingData[2] ;
	/* y min */
	calibrationData[1][0]= (s16)(EPROM_CalibratingData[5]<<8) | EPROM_CalibratingData[4] ;
	/* y max */
	calibrationData[1][1]= (s16)(EPROM_CalibratingData[7]<<8) | EPROM_CalibratingData[6] ;
	/* z min */
	calibrationData[2][0]= (s16)(EPROM_CalibratingData[9]<<8) | EPROM_CalibratingData[8] ;
	/* z max */
	calibrationData[2][1]= (s16)(EPROM_CalibratingData[11]<<8) | EPROM_CalibratingData[10] ;


	HCOMPASS_SetCalibration(
					calibrationData[0][0], calibrationData[0][1],
					calibrationData[1][0], calibrationData[1][1],
					calibrationData[2][0], calibrationData[2][1]
			);

	SYSCFG_vConfigEXTI_Line(PORTC, EXTI15);
	MGPIO_vSetPinMode(PORTC, PIN15,INPUT);
	MGPIO_vSetPinInPutType(PORTC,PIN15,PULLUP);
	MEXTI_vInterruptTrigger(EXTI15,FALLING);

	MEXTI_vCallBack(EXTI15, HCOMPASS_RSTCalibration);
	MEXTI_vEnableInterrupt(EXTI15);
	MNVIC_vEnableInterrupt(NVIC_EXTI15_10);


}
void HCOMPASS_vSetRowData(){

	MGPIO_vSetPinMode(PORTC,PIN14, OUTPUT);
	static u8 cal_Flag=0;

	/* Read data register 00H ~ 05H. */
	/* Send Register Position 00H */
	u8 Local_TxData[]={X_LSB};
	MI2C_vMasterTx(COMPASS_I2C,COMPASS_ADDRESS,Local_TxData,1,WithoutStop);
	/* Read Data */
	u8 Local_RxData[6]={0};
	MI2C_u8MasterRx(COMPASS_I2C,COMPASS_ADDRESS,Local_RxData,6);

	s16 RowData[3]={0};

	RowData[0] =  (s16)(Local_RxData[X_MSB]<<8) | Local_RxData[X_LSB] ;
	RowData[1] =  (s16)(Local_RxData[Y_MSB]<<8) | Local_RxData[Y_LSB] ;
	RowData[2] =  (s16)(Local_RxData[Z_MSB]<<8) | Local_RxData[Z_LSB] ;

	//static s16 calibrationData[3][2] = {{-1043, 643}, {-1135, 326}, {0, 706}};
	//static s16 calibrationData[3][2] = {{32767, -32768}, {32767, -32768}, {0, 706}};
	u8 Calibration_Flag=0;
	for (u8 i = 0; i < 3 ; i++ ) {
		if (RowData[i] < calibrationData[i][0]) {
			calibrationData[i][0] = RowData[i];
			Calibration_Flag=1;
		}
		if (RowData[i] > calibrationData[i][1]) {
			calibrationData[i][1] = RowData[i];
			Calibration_Flag=1;
		}
	}
	if(Calibration_Flag==1){
		cal_Flag^=1;
		MGPIO_vSetPinValue(PORTC, PIN14, cal_Flag);
		HCOMPASS_SetCalibration(
				calibrationData[0][0], calibrationData[0][1],
				calibrationData[1][0], calibrationData[1][1],
				calibrationData[2][0], calibrationData[2][1]
		);
		HEPROM_vWriteData(CMP_EPROM_PAGE,CMP_EPROM_PAGE_OFFSET, calibrationData, CalibrationSize);
	}


	f32 CalibratedData[3]={0};
	HCOMPASS_ApplyCalibration(RowData, CalibratedData);

	CompassData.X =  CalibratedData[0];
	CompassData.Y =  CalibratedData[1];
	CompassData.Z =  CalibratedData[2];


}


void HCOMPASS_vReadRowData(s16* PTR_RxRowData){

	PTR_RxRowData[0] =  CompassData.X ;
	PTR_RxRowData[1] =  CompassData.Y ;
	PTR_RxRowData[2] =  CompassData.Z ;
}



/* Function to calculate pitch angle */
/* Positive pitch indicates a downward tilt in the forward direction.*/
f32 HCOMPASS_f32GetPitch() {
	s16 y =CompassData.Y;
	s16 z = CompassData.Z;
	return atan2((f32)CompassData.X, sqrt((f32)(y*y + z*z))) * (180.0 / M_PI);
}

/* Function to calculate roll angle */
/*Positive roll indicates a tilt to the right.*/
f32 HCOMPASS_f32GetRoll() {
	s16 x= CompassData.X;
	s16 z= CompassData.Z;
	return atan2((f32)CompassData.X, sqrt((f32)(x*x + z*z))) * (180.0 / M_PI);
}

/* Function to calculate heading angle */
/*Heading is the compass direction, with 0 degrees pointing North
 * and increasing clockwise.
 * Positive heading represents an eastward direction.
 */
f32 HCOMPASS_f32GetHeading() {
	// Calculate the heading angle using atan2 and convert to degrees
<<<<<<< HEAD
	f32 Heading = atan2((f32)CompassData.Y, (f32)CompassData.X) * (180.0 / M_PI);
	Heading = Heading * (-1) ;
	// Ensure the heading is in the range [0, 360) degrees
	Heading = (Heading < 0) ? (360.0 + Heading) : Heading;
=======
	f32 Heading = atan2((f32)CompassData.Y, (f32)CompassData.X) * (180.0 / M_PI)*(-1);
	//Heading = Heading * (-1) ;
//	// Ensure the heading is in the range [0, 360) degrees
//	Heading = (Heading < 0) ? (360.0 + Heading) : Heading;
>>>>>>> azza

	return Heading;
}

f32 HCOMPASS_f32GetHeadingOutRef(){
	// Get Heading value out of GetHeading function
	f32 Heading = HCOMPASS_f32GetHeading();
	f32 HeadingOutRef = Heading - Heading_Ref;
<<<<<<< HEAD
	HeadingOutRef = (HeadingOutRef < 0) ? (360.0 + HeadingOutRef) : HeadingOutRef;
=======
	if (HeadingOutRef < -180)
		HeadingOutRef += 360;
	if ( HeadingOutRef > 180)
		HeadingOutRef -= 360;
//	HeadingOutRef = (HeadingOutRef < 0) ? (360.0 + HeadingOutRef) : HeadingOutRef;
>>>>>>> azza
	return HeadingOutRef;
}


void HCOMPASS_SetCalibration(s16 x_min, s16 x_max, s16 y_min, s16 y_max, s16 z_min, s16 z_max) {


	HCOMPASS_SetCalibrationOffsets((x_min + x_max) / 2.0, (y_min + y_max) / 2.0, (z_min + z_max) / 2.0);

	f32 x_avg_delta = (x_max - x_min) / 2.0;
	f32 y_avg_delta = (y_max - y_min) / 2.0;
	f32 z_avg_delta = (z_max - z_min) / 2.0;

	f32 avg_delta = (x_avg_delta + y_avg_delta + z_avg_delta) / 3.0;
	//f32 avg_delta = (x_avg_delta + y_avg_delta ) / 2.0 ;

	HCOMPASS_SetCalibrationScales(avg_delta / x_avg_delta, avg_delta / y_avg_delta, avg_delta / z_avg_delta);
}

void HCOMPASS_SetCalibrationOffsets(f32 x_offset, f32 y_offset, f32 z_offset) {
	_offset[0] = x_offset;
	_offset[1] = y_offset;
	_offset[2] = z_offset;
}

void HCOMPASS_SetCalibrationScales(f32 x_scale, f32 y_scale, f32 z_scale) {
	_scale[0] = x_scale;
	_scale[1] = y_scale;
	_scale[2] = z_scale;
}

f32 HCOMPASS_GetCalibrationOffset(u8 index) {
	return _offset[index];
}

f32 HCOMPASS_GetCalibrationScale(u8 index) {
	return _scale[index];
}

void HCOMPASS_ClearCalibration() {
	HCOMPASS_SetCalibrationOffsets(0.0, 0.0, 0.0);
	HCOMPASS_SetCalibrationScales(1.0, 1.0, 1.0);
}

/* standby Example */
/* Write Register 09H by 0x00 */


/* Soft Reset Example */
/* Write Register 0AH by 0x80 */

/* SET/RESET Period : It is recommended that the register 0BH is written by 0x01*/


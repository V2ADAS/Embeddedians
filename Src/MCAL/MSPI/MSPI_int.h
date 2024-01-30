/*
 * MSPI_int.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Omar
 */

#ifndef MCAL_MSPI_MSPI_INT_H_
#define MCAL_MSPI_MSPI_INT_H_

/*
 * Since some SPI1 and SPI3/I2S3 pins may be mapped onto
 * some pins used by the JTAG interface you may either:
 * – map SPI/I2S onto other pins
 * – disable the JTAG and use the SWD interface prior
*/


/************** DATA FRAME ******************/
#define FRAME_8_BIT					0
#define FRAME_16_BIT				1

/*************** BAUD RATE *************/
#define DIV2					0b000
#define DIV4					0b001
#define DIV8					0b010
#define DIV16					0b011
#define DIV32					0b100
#define DIV64					0b101
#define DIV128					0b110
#define DIV256					0b111


#define MSPI1					0
#define MSPI2					1
#define MSPI3					2
#define MSPI4					3

#define MSPI_MASTER				1
#define MSPI_SLAVE				0


void MSPI_vMasterInit( u8 Local_u8SPINo );

void MSPI_vSlaveInit( u8 Local_u8SPINo );

void MSPI_vEnableRxInt(u8 Local_u8SPINo);

void MSPI_vEnableTxInt(u8 Local_u8SPINo);

u8 MSPI_u8MasterTransceiver( u8 Local_u8SPINo,u8 Local_u8SlavePort , u8 Local_u8SlavePin ,u8 Local_u8Data);

u8 MSPI_u8SlaveTransceiver( u8 Local_u8SPINo ,u8 Local_u8Data);

void MSPI_vSetTxCallBackFunc(u8 Local_u8SPINo,void(*Local_pvTxIRQ)(void));

void MSPI_vSetRxCallBackFunc(u8 Local_u8SPINo,void(*Local_pvRxIRQ)(void));

u8 MSPI_u8ReadRecievedData(u8 Local_u8SPINo);

#endif /* MCAL_MSPI_MSPI_INT_H_ */

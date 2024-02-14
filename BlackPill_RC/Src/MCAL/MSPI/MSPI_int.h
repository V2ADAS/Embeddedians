/*******************************************************************************************************/
/* Author            : Omar Wael                                                                       */
/* Version           : V0.0.0                                                                          */
/* Data              : 1 Dec 2023                                                                      */
/* Description       : MSPI_Interface.c --> implementations                                            */
/* Module  Features  :                                                                                 */
/*      01- MSPI_MasterInit                                                                            */
/*      02- MSPI_SlaveInit                                                                             */
/*      03- MSPI_EnableRxInt                                                                           */
/*      04- MSPI_EnableTxInt                                                                           */
/*      05- MSPI_MasterTransceiver                                                                     */
/*      06- MSPI_SlaveTransceiver                                                                      */
/*      07- MSPI_SetTxCallBackFunc                         											   */
/*      08- MSPI_SetRxCallBackFunc																	   */
/*      09- MSPI_ReadRecievedData																	   */
/*******************************************************************************************************/


/***************************************************************************/
/*                  File Guard Will Call On Time in .c File                */
/***************************************************************************/
#ifndef MCAL_MSPI_MSPI_INT_H_
#define MCAL_MSPI_MSPI_INT_H_

/*
 * Since some SPI1 and SPI3/I2S3 pins may be mapped onto
 * some pins used by the JTAG interface you may either:
 * – map SPI/I2S onto other pins
 * – disable the JTAG and use the SWD interface prior
*/



/***************************************************************************/
/*                 DATA FRAME							                   */
/***************************************************************************/
#define FRAME_8_BIT					0
#define FRAME_16_BIT				1

/***************************************************************************/
/*                 BAUD RATE									           */
/***************************************************************************/
#define DIV2					0b000
#define DIV4					0b001
#define DIV8					0b010
#define DIV16					0b011
#define DIV32					0b100
#define DIV64					0b101
#define DIV128					0b110
#define DIV256					0b111


/***************************************************************************/
/*                 MSPI Indices								    	       */
/***************************************************************************/
#define MSPI1					0
#define MSPI2					1
#define MSPI3					2
#define MSPI4					3
/***************************************************************************/
/*                 MSPI Mode								               */
/***************************************************************************/
#define MSPI_MASTER				1
#define MSPI_SLAVE				0

/***************************************************************************/
/*           Function Declarations for MSPI module						   */
/***************************************************************************/

/*----------------------------------------------------------------------------------------------------*/
/*                                      01- MSPI_MasterInit                                           */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Initialize MSPI as Master.                                              */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/* 3- Function Return      -> void																	  */
/******************************************************************************************************/
void MSPI_vMasterInit( u8 Local_u8SPINo );

/*----------------------------------------------------------------------------------------------------*/
/*                                      02- MSPI_SlaveInit                                            */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Initialize MSPI as Slave.                                               */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/* 3- Function Return      -> void																	  */
/******************************************************************************************************/
void MSPI_vSlaveInit( u8 Local_u8SPINo );

/*----------------------------------------------------------------------------------------------------*/
/*                                      03- MSPI_EnableRxInt                                          */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable RX interrupt for MSPI.                                           */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/* 3- Function Return      -> void 																	  */
/*----------------------------------------------------------------------------------------------------*/
void MSPI_vEnableRxInt(u8 Local_u8SPINo);

/*----------------------------------------------------------------------------------------------------*/
/*                                      04- MSPI_EnableTxInt                                          */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable TX interrupt for MSPI.                                           */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/* 3- Function Return      -> void 																	  */
/*----------------------------------------------------------------------------------------------------*/
void MSPI_vEnableTxInt(u8 Local_u8SPINo);

/*----------------------------------------------------------------------------------------------------*/
/*                                      05- MSPI_MasterTransceiver                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Perform data transmission/reception in Master mode.                     */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/*                            @param Local_u8SlavePort = Slave port number                            */
/*                            @param Local_u8SlavePin = Slave pin number                              */
/*                            @param Local_u8Data = Data to be transmitted/received                   */
/* 3- Function Return      -> u8 (Received data in case of Master reception)                          */
/*----------------------------------------------------------------------------------------------------*/
u8 MSPI_u8MasterTransceiver( u8 Local_u8SPINo,u8 Local_u8SlavePort , u8 Local_u8SlavePin ,u8 Local_u8Data);

/*----------------------------------------------------------------------------------------------------*/
/*                                      06- MSPI_SlaveTransceiver                                     */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Perform data transmission/reception in Slave mode.                      */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/*                            @param Local_u8Data = Data to be transmitted/received                   */
/* 3- Function Return      -> u8 (Received data in case of Slave reception)                           */
/*----------------------------------------------------------------------------------------------------*/
u8 MSPI_u8SlaveTransceiver( u8 Local_u8SPINo ,u8 Local_u8Data);

/*----------------------------------------------------------------------------------------------------*/
/*                                      07- MSPI_SetTxCallBackFunc                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Set the callback function for TX interrupt.                             */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/*                            @param Local_pvTxIRQ = Pointer to the TX interrupt callback function    */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MSPI_vSetTxCallBackFunc(u8 Local_u8SPINo,void(*Local_pvTxIRQ)(void));

/*----------------------------------------------------------------------------------------------------*/
/*                                      08- MSPI_SetRxCallBackFunc                                    */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Set the callback function for RX interrupt.                             */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/*                            @param Local_pvRxIRQ = Pointer to the RX interrupt callback function    */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MSPI_vSetRxCallBackFunc(u8 Local_u8SPINo,void(*Local_pvRxIRQ)(void));

/*----------------------------------------------------------------------------------------------------*/
/*                                      09- MSPI_ReadRecievedData                                     */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Read the received data in the RX buffer.                                */
/* 2- Function Input       -> @param Local_u8SPINo = MSPI1, MSPI2, MSPI3, MSPI4                       */
/* 3- Function Return      -> u8 (Received data in the RX buffer)                                     */
/*----------------------------------------------------------------------------------------------------*/
u8 MSPI_u8ReadRecievedData(u8 Local_u8SPINo);

#endif /* MCAL_MSPI_MSPI_INT_H_ */

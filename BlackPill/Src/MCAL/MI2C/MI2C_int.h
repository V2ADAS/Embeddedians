/*******************************************************************************************************/
/* Author            : Omar                                                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 28 Jan 2024                                                                     */
/* Description       : MI2C_Interface.h --> implementations                                            */
/* Module  Features  :                                                                                 */
/*      01- MI2C_MasterInit                                                                            */
/*      02- MI2C_MasterTx                                                                              */
/*      03- MI2C_MasterRx                                                                              */
/*      04- MI2C_SlaveInit                                                                             */
/*      05- MI2C_SlaveRx                                                                               */
/*      06- MI2C_SendSlaveADDR                                                                         */
/*      07- MI2C_SendDataByte                                                                          */
/*      08- MI2C_ReadDataByte                                                                          */
/*      09- MI2C_GenerateStart                                                                         */
/*      10- MI2C_ClearStart                                                                            */
/*      11- MI2C_ClearADDR                                                                             */
/*      12- MI2C_GenerateStop                                                                          */
/*******************************************************************************************************/

/* test */

/***************************************************************************/
/*                  File Guard Will Call On Time in .c File                */
/***************************************************************************/
#ifndef MCAL_MI2C_MI2C_INT_H_
#define MCAL_MI2C_MI2C_INT_H_

#include "MI2C_Private.h"

/*----------------------------------------------------------------------------------------------------*/
/*                                      I2C_Number                                                    */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {

	I2C1,
	I2C2,
	I2C3
} I2CNo_t;

/*----------------------------------------------------------------------------------------------------*/
/*                                      I2C_Direction                                                */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {

	WithWrite,
	WithRead
} I2C_Dir_t;

/*----------------------------------------------------------------------------------------------------*/
/*                                      I2C_STOPSTAT                                         		  */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {

	WithStop,
	WithoutStop
} I2C_STOPSTAT_t;


/*----------------------------------------------------------------------------------------------------*/
/*                                      I2C_ERRORSTATS                                                */
/*----------------------------------------------------------------------------------------------------*/
typedef enum {

	ADDRFAIL,
	NoError
} I2C_ERRORSTATS_t;

/**************************** User APIs *************************************/

/*----------------------------------------------------------------------------------------------------*/
/*                                      01- MI2C_MasterInit                                           */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Initialize I2C as Master.                                               */
/* 2- Function Input       -> @param Copy_I2CNumber = I2C1, I2C2, I2C3                                */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vMasterInit(I2CNo_t Copy_I2CNumber);

/*----------------------------------------------------------------------------------------------------*/
/*                                      02- MI2C_MasterTx                                             */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Perform I2C Master transmission.                                        */
/* 2- Function Input       -> @param Copy_I2CNumber = I2C1, I2C2, I2C3                                */
/*                            @param Copy_u8SlaveAddress = Slave address                              */
/*                            @param Copy_u8Data = Pointer to Data to be transmitted                  */
/*                            @param Copy_u8DataLen = Length of the data                              */
/*                            @param StopStatus = WithStop or WithoutStop                             */
/* 3- Function Return      -> I2C_ERRORSTATS_t (Error status)                                         */
/*----------------------------------------------------------------------------------------------------*/
I2C_ERRORSTATS_t MI2C_vMasterTx(I2CNo_t Copy_I2CNumber, u8 Copy_u8SlaveAddress, u8* Copy_u8Data, u8 Copy_u8DataLen, I2C_STOPSTAT_t StopStatus);

/*----------------------------------------------------------------------------------------------------*/
/*                                      03- MI2C_MasterRx                                             */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Perform I2C Master reception.                                           */
/* 2- Function Input       -> @param Copy_I2CNumber = I2C1, I2C2, I2C3                                */
/*                            @param Copy_u8SlaveAddress = Slave address                              */
/*                            @param RxData = Pointer to the received data buffer                     */
/*                            @param DataLen = Length of the data buffer                              */
/* 3- Function Return      -> u8 (Received data)                                                      */
/*----------------------------------------------------------------------------------------------------*/
u8 MI2C_u8MasterRx(I2CNo_t Copy_I2CNumber, u8 Copy_u8SlaveAddress, u8* RxData, u8 DataLen);

/*----------------------------------------------------------------------------------------------------*/
/*                                      04- MI2C_SlaveInit                                            */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Initialize I2C as Slave.                                                */
/* 2- Function Input       -> @param Copy_I2CNumber = I2C1, I2C2, I2C3                                */
/*                            @param Copy_u8SlaveOwnAddress = Slave's own address                     */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vSlaveInit(I2CNo_t Copy_I2CNumber, u8 Copy_u8SlaveOwnAddress);

/*----------------------------------------------------------------------------------------------------*/
/*                                      05- MI2C_SlaveRx                                              */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Perform I2C Slave reception.                                            */
/* 2- Function Input       -> @param Copy_I2CNumber = I2C1, I2C2, I2C3                                */
/* 3- Function Return      -> u8 (Received data)                                                      */
/*----------------------------------------------------------------------------------------------------*/
u8 MI2C_u8SlaveRx(I2CNo_t Copy_I2CNumber);




/************************* Helping APIs *************************************/

/*----------------------------------------------------------------------------------------------------*/
/*                                      06- MI2C_SendSlaveADDR                                        */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Send slave address in the specified direction.                          */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                  */
/*                            @param Copy_u8SlaveAddress = Slave address                              */
/*                            @param Direction = WithWrite or WithRead                                */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vSendSlaveADDR(volatile I2C_Mem_Map_t* I2Cx, u8 Copy_u8SlaveAddress, I2C_Dir_t Direction);

/*----------------------------------------------------------------------------------------------------*/
/*                                      07- MI2C_SendDataByte                                         */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Send a data byte on the I2C bus.                                        */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                  */
/*                            @param Copy_u8Data = Data to be transmitted                             */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vSendDataByte(volatile I2C_Mem_Map_t* I2Cx, u8 Copy_u8Data);

/*----------------------------------------------------------------------------------------------------*/
/*                                      08- MI2C_ReadDataByte                                         */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Read a data byte from the I2C bus.                                      */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                  */
/* 3- Function Return      -> u8 (Received data)                                                      */
/*----------------------------------------------------------------------------------------------------*/
u8 MI2C_vReadDataByte(volatile I2C_Mem_Map_t* I2Cx);

/*----------------------------------------------------------------------------------------------------*/
/*                                      09- MI2C_GenerateStart                                        */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Generate a START condition on the I2C bus.                              */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                  */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vGenerateStart(volatile I2C_Mem_Map_t* I2Cx);

/*                                      10- MI2C_ClearStart                                           */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Clear the START condition on the I2C bus.                                */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vClearStart(volatile I2C_Mem_Map_t* I2Cx);

/*----------------------------------------------------------------------------------------------------*/
/*                                      11- MI2C_ClearADDR                                           */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Clear the ADDR flag in I2C_SR1 register.                                */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vClearADDR(volatile I2C_Mem_Map_t* I2Cx);

/*----------------------------------------------------------------------------------------------------*/
/*                                      12- MI2C_GenerateStop                                        */
/*----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Generate a STOP condition on the I2C bus.                               */
/* 2- Function Input       -> @param I2Cx = I2C memory map structure                                */
/* 3- Function Return      -> void                                                                    */
/*----------------------------------------------------------------------------------------------------*/
void MI2C_vGenerateStop(volatile I2C_Mem_Map_t* I2Cx);

#endif /* MCAL_MI2C_MI2C_INT_H_ */


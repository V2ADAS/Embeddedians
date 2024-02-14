/*
 * I2C_Interface.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef I2C_I2C_INTERFACE_H_
#define I2C_I2C_INTERFACE_H_

//#include "../GPIO/GPIO_Interface.h"
#include "I2C_Registers_2.h"
#include "I2C_Config_2.h"

void I2C_voidInit(st_I2C_RegDef_t* I2Cn, I2C_Config_t* config);
void I2C_voidReset(st_I2C_RegDef_t* I2Cn);

/* Repeated Start */
#define I2C_RS_DISABLE	0
#define I2C_RS_ENABLE	1

/* Master Polling Functions */
void I2C_voidMasterSendData(st_I2C_RegDef_t* I2Cn, u8 address, u8* data, u32 len, u8 repeatedStart);
void I2C_voidMasterReceiveData(st_I2C_RegDef_t* I2Cn,  u8 address, u8* data, u32 len, u8 repeatedStart);

/* Interrupt Control */
#define I2C_INT_DIS		0
#define I2C_INT_EN		1

/* Master Interrupt Functions */
void I2C_voidMasterSendDataIT(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle);
void I2C_voidMasterReceiveDataIT(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle);

/* Interrupt Functions */
void I2C_voidInterruptControl(st_I2C_RegDef_t* I2Cn, u8 state);
void I2C_voidEventInterruptHandler(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle);
void I2C_voidErrorInterruptHandler(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle);

/* Slave Functions */
void I2C_voidSlaveSendData(st_I2C_RegDef_t* I2Cn, u8 data);
void I2C_voidSlaveReceiveData(st_I2C_RegDef_t* I2Cn, u8* data);
void I2C_voidSlaveHandleCallBackFunction(st_I2C_RegDef_t* I2Cn, u8 state);

/* Events */
#define I2C_EVENT_RECEPTION_FINISHED 	0
#define I2C_EVENT_TRANSMISSION_FINISHED 1
#define I2C_EVENT_REQUEST_DATA 			2
#define I2C_EVENT_RECEIVE_DATA 			3

#endif /* I2C_I2C_INTERFACE_H_ */

/*
 * MI2C_int.h
 *
 *  Created on: Jan 28, 2024
 *      Author: Omar
 */

#ifndef MCAL_MI2C_MI2C_INT_H_
#define MCAL_MI2C_MI2C_INT_H_

typedef enum{

	I2C1,
	I2C2,
	I2C3
} I2CNo_t;

/**************************** User APIs *************************************/

void MI2C_vMasterInit(I2CNo_t Copy_I2CNumber);
void MI2C_vMasterTx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress , u8 Copy_u8Data );
u8 MI2C_u8MasterRx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress );

void MI2C_vSlaveInit(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveOwnAddress);
u8 MI2C_u8SlaveRx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress );


/************************* Helping APIs *************************************/

void MI2C_vGenerateStart(volatile I2C_Mem_Map_t* I2Cx);
void MI2C_vClearStart(volatile I2C_Mem_Map_t* I2Cx);

void MI2C_vClearADDR(volatile I2C_Mem_Map_t* I2Cx);

void MI2C_vGenerateStop(volatile I2C_Mem_Map_t* I2Cx);


#endif /* MCAL_MI2C_MI2C_INT_H_ */

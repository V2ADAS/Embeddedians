/*
 * I2C_Program.c
 *
 *  Created on: Jun 22, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES.h"

#include "I2C_Interface_2.h"

//static void I2C_voidConfigurePins(st_I2C_RegDef_t* I2Cn);

void I2C_voidInit(st_I2C_RegDef_t* I2Cn, I2C_Config_t* config){

	//I2C_voidConfigurePins(I2Cn);

	/* Clock Configuration */
	I2Cn->CR2 |= (I2C_FREQ & 0x3F);

	/* Configure Address */
	if(config->addressSize == I2C_7_BIT){
		// clear address
		I2Cn->OAR1 &= 0x00;
		// Set the 7 bit address mode
		I2Cn->OAR1 &= ~(1<<15);
		I2Cn->OAR1 |= (1<<14); // This bit should be high by software (Reference Manual)
		// write the address
		I2Cn->OAR1 |= ((config->address<<1) & 0x00FE);

	}
	else{
		// 10 bit addressing mode
	}

	/* Speed Configuration */
	if(config->speedMode == I2C_STANDARD){
		//I2Cn->CCR = ((FREQ * (T_SCL/2)) & 0xFFF);
		I2Cn->CCR = ((I2C_FREQ * ((1000U/config->speed)/2)) & 0xFFF);
	}
	else if(config->speedMode == I2C_FAST){
		// Fast mode
	}
	I2Cn->TRISE = ((I2C_FREQ + 1) & 0x3F);

	// Peripheral Enable
	I2Cn->CR1 |= (1<<I2C_PE);

	/* ACK Control */
	if(config->ACK == I2C_ACK_EN)
		I2Cn->CR1 |= (1<<10);
	else
		I2Cn->CR1 &= ~(1<<10);
}

void I2C_voidMasterSendData(st_I2C_RegDef_t* I2Cn, u8 address, u8* data, u32 len, u8 repeatedStart){
	u8 slaveAddress;

	// Send Start bit
	I2Cn->CR1 |= (1<<I2C_START);

	// Send the address
	while(!(I2Cn->SR1 & (1<<I2C_FLAG_SB)));
	slaveAddress = address<<1;
	slaveAddress &= ~(1); // Clear LSB to enter Transmission mode
	I2Cn->DR = slaveAddress;

	// Wait for address to be sent
	while(!(I2Cn->SR1 & (1<<I2C_FLAG_ADDR)));
	u8 readSR2 = I2Cn->SR2; // Clear ADDR flag
	(void)readSR2;

	// Send the data
	for(u32 i=0; i<len; i++){
		while(!(I2Cn->SR1 & (1<<I2C_FLAG_TXE)));
		I2Cn->DR = data[i];
	}

	// Send Stop bit
	while( (!(I2Cn->SR1 & (1<<I2C_FLAG_TXE))) );
	if(repeatedStart == I2C_RS_DISABLE)
		I2Cn->CR1 |= (1<<I2C_STOP);
}

void I2C_voidMasterReceiveData(st_I2C_RegDef_t* I2Cn,  u8 address, u8* data, u32 len, u8 repeatedStart){
	u32 i=0;
	u8 slaveAddress;

	// Send Start bit
	I2Cn->CR1 |= (1<<I2C_START);

	// Send the address
	while(!(I2Cn->SR1 & (1<<I2C_FLAG_SB)));
	slaveAddress = address<<1;
	slaveAddress |= (1); // Set LSB to enter Receiving mode
	I2Cn->DR = slaveAddress;

	// Wait for address to be sent
	while(!(I2Cn->SR1 & (1<<I2C_FLAG_ADDR)));
	if(len==1) // Disable the ACK
		I2Cn->CR1 &= ~(1<<10);

	u8 readSR2 = I2Cn->SR2; // Clear ADDR flag
	(void)readSR2;

	// Receive the data
	for(i=0; i<len; i++){
		while(!(I2Cn->SR1 & (1<<I2C_FLAG_RXNE)));
		if(i == len-2) // Disable the ACK
			I2Cn->CR1 &= ~(1<<10);
		if((i==len-1) && (repeatedStart == I2C_RS_DISABLE))
			I2Cn->CR1 |= (1<<I2C_STOP);
		data[i] = I2Cn->DR;
	}

	// ReEnable ACK
	I2Cn->CR1 |= (1<<10);
}

void I2C_voidSlaveSendData(st_I2C_RegDef_t* I2Cn, u8 data){
	I2Cn->DR = data;
}

void I2C_voidSlaveReceiveData(st_I2C_RegDef_t* I2Cn, u8* data){
	*data = I2Cn->DR;
}

/*static void I2C_voidConfigurePins(st_I2C_RegDef_t* I2Cn){
	GPIO_Config_t I2C_config;
	I2C_config.mode = GPIO_ALT_FN;
	I2C_config.outType = GPIO_OPEN_DRAIN;
	I2C_config.pupdState = GPIO_NO_PUPD;
	I2C_config.speed = GPIO_HIGH_SPEED;

	if(I2Cn == I2C1){
		I2C_config.AltFuncMode = GPIO_AF4;
		GPIO_voidInitPin(PORTB, I2C1_SCL_PIN, &I2C_config); // SCL
		GPIO_voidInitPin(PORTB, I2C1_SDA_PIN, &I2C_config); // SDA
	}
	else if(I2Cn == I2C2){
		I2C_config.AltFuncMode = GPIO_AF4;
		GPIO_voidInitPin(PORTB, 10, &I2C_config); // SCL
		I2C_config.AltFuncMode = GPIO_AF9;
		GPIO_voidInitPin(PORTB, 3, &I2C_config); // SDA
	}
	else if(I2Cn == I2C3){
		I2C_config.AltFuncMode = GPIO_AF4;
		GPIO_voidInitPin(PORTA, 8, &I2C_config); // SCL
		I2C_config.AltFuncMode = GPIO_AF9;
		GPIO_voidInitPin(PORTB, 4, &I2C_config); // SDA
	}
}*/

void I2C_voidReset(st_I2C_RegDef_t* I2Cn)
{
	I2Cn->CR1 |= (1<<15);
}

void I2C_voidMasterSendDataIT(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle){
	// Initialize handle variables
	handle->TxOrRx = I2C_TX_MODE;
	handle->index = 0;
	handle->runningState = I2C_RUNNING;

	// Send Start bit
	I2Cn->CR1 |= (1<<I2C_START);
}

void I2C_voidMasterReceiveDataIT(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle){
	// Initialize handle variables
	handle->TxOrRx = I2C_RX_MODE;
	handle->index = 0;
	handle->runningState = I2C_RUNNING;

	// Send Start bit
	I2Cn->CR1 |= (1<<I2C_START);
}

void I2C_voidEventInterruptHandler(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle){
	u32 SR1 = I2Cn->SR1;

	// 1- SB
	if(SR1 & (1<<I2C_FLAG_SB))
	{
		u8 slaveAddress = (handle->slaveAddress<<1);
		if(handle->TxOrRx == I2C_TX_MODE)
			slaveAddress &= ~(1); // Clear LSB to enter Transmission mode
		else
			slaveAddress |= (1); // Set LSB to enter Receiving mode
		I2Cn->DR = slaveAddress;
		(void)slaveAddress;
	}

	// 2- ADDR
	else if(SR1 & (1<<I2C_FLAG_ADDR))
	{
		if( I2Cn->SR2 & (1<<0) )
		{ // Master
			if( (handle->TxOrRx == I2C_RX_MODE) && (handle->len == 1) )
				I2Cn->CR1 &= ~(1<<10); // Disable the ACK
		}

		// Clear ADDR flag in case Master or Slave
		u8 readSR2 = I2Cn->SR2;
		(void)readSR2;
	}

	// 3- BTF
	else if(SR1 & (1<<I2C_FLAG_BTF))
	{
		if(handle->TxOrRx == I2C_TX_MODE)
		{
			if(handle->index == handle->len){
				if(handle->repeatedStart == I2C_RS_DISABLE)
					I2Cn->CR1 |= (1<<I2C_STOP);
				/* Notify Application Communication Ended */
				// To be Done
				handle->runningState = I2C_FINISHED;
			}
		}
	}

	// 4- STOPF
	else if(SR1 & (1<<I2C_FLAG_STOPF))
	{
		// Slave Mode
		u32 readCR1 = I2Cn->CR1;
		I2Cn->CR1 = readCR1; // Clear STOPF flag
		(void)readCR1;
		I2C_voidSlaveHandleCallBackFunction(I2Cn, I2C_EVENT_RECEPTION_FINISHED);
	}

	// 5- RXNE
	else if(SR1 & (1<<I2C_FLAG_RXNE))
	{
		if( (I2Cn->SR2 & (1<<0)) ) // Master
		{
			if(handle->index == (handle->len-2))
				I2Cn->CR1 &= ~(1<<10);		// Disable the ACK

			if((handle->index==handle->len-1) && (handle->repeatedStart == I2C_RS_DISABLE))
				I2Cn->CR1 |= (1<<I2C_STOP);	// Generate Stop Bit

			// Read the data
			handle->data[handle->index] = I2Cn->DR;
			handle->index++;

			/* Notify Application Communication Ended */
			// To be Done
			if(handle->index == handle->len){
				handle->runningState = I2C_FINISHED;
				// ReEnable ACK
				I2Cn->CR1 |= (1<<10);
			}
		}
		else// Slave
		{
			I2C_voidSlaveHandleCallBackFunction(I2Cn, I2C_EVENT_RECEIVE_DATA);
		}
	}

	// 6- TXE
	else if(SR1 & (1<<I2C_FLAG_TXE))
	{
		if( (I2Cn->SR2 & (1<<0)) ) // Master
		{
			if(handle->index < handle->len){
				I2Cn->DR = handle->data[handle->index];
				handle->index++;
			}
		}
		else // Slave
		{
			I2C_voidSlaveHandleCallBackFunction(I2Cn, I2C_EVENT_REQUEST_DATA);
		}
	}
}

void I2C_voidErrorInterruptHandler(st_I2C_RegDef_t* I2Cn, I2C_HandleIT_t* handle){
	u32 SR1 = I2Cn->SR1;

	// 1- BERR
	if(SR1 & (1<<I2C_FLAG_BERR))
	{
		I2Cn->SR1 &= ~(1<<I2C_FLAG_BERR);
		handle->runningState = I2C_ERROR_BERR;
	}
	// 2- ARLO
	else if(SR1 & (1<<I2C_FLAG_ARLO))
	{
		I2Cn->SR1 &= ~(1<<I2C_FLAG_ARLO);
		handle->runningState = I2C_ERROR_ARLO;
	}
	// 3- AF
	else if(SR1 & (1<<I2C_FLAG_AF))
	{
		I2Cn->SR1 &= ~(1<<I2C_FLAG_AF);
		if(I2Cn->SR2 & (1<<0)){
			handle->runningState = I2C_ERROR_AF;
		}
		else{
			I2C_voidSlaveHandleCallBackFunction(I2Cn, I2C_EVENT_TRANSMISSION_FINISHED);
		}
	}
	// 4- OVR
	else if(SR1 & (1<<I2C_FLAG_OVR))
	{
		I2Cn->SR1 &= ~(1<<I2C_FLAG_OVR);
		handle->runningState = I2C_ERROR_OVR;
	}
	// 5- PECERR
	else if(SR1 & (1<<I2C_FLAG_PECERR))
	{
		I2Cn->SR1 &= ~(1<<I2C_FLAG_PECERR);
		handle->runningState = I2C_ERROR_PECERR;
	}
	// 6- TIMEOUT
	else if(SR1 & (1<<I2C_FLAG_TIMEOUT))
	{
		I2Cn->SR1 &= ~(1<<I2C_FLAG_TIMEOUT);
		handle->runningState = I2C_ERROR_TIMEOUT;
	}

}

void I2C_voidInterruptControl(st_I2C_RegDef_t* I2Cn, u8 state){
	if(state == I2C_INT_EN){
		// Enable Interrupt
		I2Cn->CR2 |= (1<<I2C_ITBUFEN);
		I2Cn->CR2 |= (1<<I2C_ITEVTEN);
		I2Cn->CR2 |= (1<<I2C_ITERREN);
	}
	else{
		// Disable Interrupt
		I2Cn->CR2 &= ~(1<<I2C_ITBUFEN);
		I2Cn->CR2 &= ~(1<<I2C_ITEVTEN);
		I2Cn->CR2 &= ~(1<<I2C_ITERREN);
	}
}

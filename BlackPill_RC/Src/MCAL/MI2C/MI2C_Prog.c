/*
 * MI2C_Prog.c
 *
 *  Created on: Jan 28, 2024
 *      Author: Omar
 */

#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES.h"

#include"MI2C_Config.h"
#include"MI2C_Private.h"
#include"MI2C_int.h"




/*The following is the required sequence in master mode.
• Program the peripheral input clock in I2C_CR2 Register in order to generate correct
timings
• Configure the clock control registers
• Configure the rise time register
• Program the I2C_CR1 register to enable the peripheral
• Set the START bit in the I2C_CR1 register to generate a Start condition
The peripheral input clock frequency must be at least:
• 2 MHz in Sm mode
• 4 MHz in Fm mode
*/

void MI2C_vMasterInit(I2CNo_t Copy_I2CNumber){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG; break;
	case I2C2: I2Cx=I2C2_REG; break;
	case I2C3: I2Cx=I2C3_REG; break;

	}

	/* disable peripheral for resting all regs */
	CLR_BIT(I2Cx->CR1,CR1_PE);
	/* PLCK */
	I2Cx->CR2 |= I2C_PCLK ;

	/* configure clock control register */
	/*For instance: in Sm mode, to generate a 100 kHz SCL frequency:
	If FREQR = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
	(0x28 <=> 40d x 125 ns = 5000 ns*/
	I2Cx->CCR |= 0x28 ;
	/* select standard mode */
	CLR_BIT(I2Cx->CCR,CCR_FS);

	/* configure rise time register */
	/*For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
	If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
	therefore the TRISE[5:0] bits must be programmed with 09h.
	(1000 ns / 125 ns = 8 + 1)*/
	I2Cx->TRISE |= 9 ;

	/* Peripheral Enable */
	SET_BIT(I2Cx->CR1,CR1_PE);


}
void MI2C_vMasterTx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress , u8 Copy_u8Data ){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
		switch(Copy_I2CNumber){
		case I2C1: I2Cx=I2C1_REG; break;
		case I2C2: I2Cx=I2C2_REG; break;
		case I2C3: I2Cx=I2C3_REG; break;
		}
	/* generate start */
	MI2C_vGenerateStart(I2Cx);

	/* clear start flag */
	MI2C_vClearStart(I2Cx);

	/* send slave address with write */
	Copy_u8SlaveAddress = Copy_u8SlaveAddress<<1 ;
	Copy_u8SlaveAddress &= ~(1);
	I2Cx->DR=  Copy_u8SlaveAddress  ;

	/* clear ADDR flag */
	MI2C_vClearADDR(I2Cx);

	/* write data in DR */
	I2Cx->DR = Copy_u8Data ;

	/* check  byte transfer successfully */
	// TODO : check if this works properly
	while( !GET_BIT(I2Cx->SR1,SR1_BTF) );

	/* generate stop condition */
	MI2C_vGenerateStop(I2Cx);

}

u8 MI2C_u8MasterRx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress );

void MI2C_vSlaveInit(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveOwnAddress){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
		switch(Copy_I2CNumber){
		case I2C1: I2Cx=I2C1_REG; break;
		case I2C2: I2Cx=I2C2_REG; break;
		case I2C3: I2Cx=I2C3_REG; break;
		}

	/* disable the peripheral */
	CLR_BIT(I2Cx->CR1,CR1_PE);

	/* PLCK */
	I2Cx->CR2 |= I2C_PCLK ;

	/* slave own address */
	I2Cx->OAR1 = Copy_u8SlaveOwnAddress<<1 ;

	/* enable ACK */
	SET_BIT(I2Cx->CR1,CR1_ACK);

	/* Enable peripheral */
	SET_BIT_FAST(I2Cx->CR1,CR1_PE);


}

u8 MI2C_u8SlaveRx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress ){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
		switch(Copy_I2CNumber){
		case I2C1: I2Cx=I2C1_REG; break;
		case I2C2: I2Cx=I2C2_REG; break;
		case I2C3: I2Cx=I2C3_REG; break;
		}
	/* check if the address flag is set */
	while( !GET_BIT(I2Cx->SR1,SR1_ADDR));
	/* clear ADDR */
	MI2C_vClearADDR(I2Cx);
	/* check the RX reg has received data */
	while( !GET_BIT(I2Cx->SR1,SR1_RXNE));
	/* read DR */
	u8 Local_u8RxData = (u8)I2Cx->DR;
	/* check stop bit flag */
	while( !GET_BIT(I2Cx->SR1,SR1_STOPF));
	/* clear stop bit flag */
	/* read SR1 */
	u8 Local_u8Dummy = I2Cx->SR1;
	(void)Local_u8Dummy;
	/*write CR1*/
	SET_BIT(I2Cx->CR1,CR1_STOP);

	return Local_u8RxData ;

}




/******************************************************************************************************************************/

void MI2C_vGenerateStart(volatile I2C_Mem_Map_t* I2Cx){

	SET_BIT(I2Cx->CR1,CR1_START);
	/* hold on start flag until set */
	while( !GET_BIT(I2Cx->SR1,SR1_SB));

}

void MI2C_vClearStart(volatile I2C_Mem_Map_t* I2Cx){

	u32 Local_u8Dummy = I2Cx->SR1;
	(void)Local_u8Dummy;
	//TODO
	/* writing data ( address ) in DR */
}

void MI2C_vClearADDR(volatile I2C_Mem_Map_t* I2Cx){

	while( !GET_BIT(I2Cx->SR1,SR1_ADDR));
	u32 Local_u8Dummy = I2Cx->SR1;
	 Local_u8Dummy = I2Cx->SR2;
	(void)Local_u8Dummy;
}

void MI2C_vGenerateStop(volatile I2C_Mem_Map_t* I2Cx){


	SET_BIT(I2Cx->CR1,CR1_STOP);

}


/*******************************************************************************************************/
/* Author            : Omar                                                                          */
/* Version           : V0.0.0                                                                        */
/* Data              : 28 Jan 2024                                                                   */
/* Description       : MI2C_Prog.c --> implementations                                              */
/* Module  Features  :                                                                               */
/*      01- MI2C_vMasterInit                                                                        */
/*      02- MI2C_vMasterTx                                                                          */
/*      03- MI2C_u8MasterRx                                                                         */
/*      04- MI2C_vSlaveInit                                                                         */
/*      05- MI2C_u8SlaveRx                                                                          */
/*      06- MI2C_vSendSlaveADDR                                                                     */
/*      07- MI2C_vSendDataByte                                                                      */
/*      08- MI2C_vReadDataByte                                                                      */
/*      09- MI2C_vGenerateStart                                                                     */
/*      10- MI2C_vClearStart                                                                        */
/*      11- MI2C_vClearADDR                                                                         */
/*      12- MI2C_vGenerateStop                                                                      */
/*******************************************************************************************************/

/***************************************************************************/
/*                  File Includes and Definitions                        */
/***************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include"../MGPIO/MGPIO_int.h"
#include"../MSTK/MSYSTICK_Int.h"
#include "MI2C_Config.h"
#include "MI2C_Private.h"
#include "MI2C_int.h"


/***************************************************************************/
/*                       Function Implementations                         */
/***************************************************************************/



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

void MI2C_vMasterInit(I2CNo_t Copy_I2CNumber ){

	u8 SDA_PIN,SCL_PIN,SDA_AF,SCL_PORT;
	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG;
	/* I2C 1 Initialization */
	SDA_PIN = I2C1_SDA;
	SCL_PIN = I2C1_SCL;
	SDA_AF = MGPIO_ALTFUNC_I2C13;
	SCL_PORT = PORTB ;
	break;

	case I2C2: I2Cx=I2C2_REG;
	SDA_PIN = I2C2_SDA;
	SCL_PIN = I2C2_SCL;
	SDA_AF = MGPIO_ALTFUNC_I2C23;
	SCL_PORT = PORTB ;
	break;

	case I2C3: I2Cx=I2C3_REG;
	SDA_PIN = I2C3_SDA;
	SCL_PIN = I2C3_SCL;
	SDA_AF = MGPIO_ALTFUNC_I2C23;
	SCL_PORT = PORTA ;
	break;

	}


	MGPIO_vSetPinMode(SCL_PORT,SCL_PIN,ALTFUNC);
	MGPIO_vSetPinMode(SDA_PORT,SDA_PIN,ALTFUNC);


	MGPIO_vSetPinOutPutType(SCL_PORT, SCL_PIN, GPIO_OPEN_DRAIN);
	MGPIO_vSetPinOutPutType(SDA_PORT, SDA_PIN, GPIO_OPEN_DRAIN);

	MGPIO_vSetPinOutPutSpeed(SCL_PORT, SCL_PIN, MGPIO_SPEED_VHIGH);

	MGPIO_vSetPinOutPutSpeed(SDA_PORT, SDA_PIN, MGPIO_SPEED_VHIGH);
	MGPIO_vSetAlternativeFunction(SCL_PORT, SCL_PIN,SCL_AF);
	MGPIO_vSetAlternativeFunction(SDA_PORT, SDA_PIN,SDA_AF);


	//		MGPIO_vSetPinMode(PORTB,PIN6,ALTFUNC);
	//		MGPIO_vSetPinMode(PORTB,PIN7,ALTFUNC);
	//
	//		MGPIO_vSetPinOutPutType(PORTB, PIN6, GPIO_OPEN_DRAIN);
	//		MGPIO_vSetPinOutPutType(PORTB, PIN7, GPIO_OPEN_DRAIN);
	//		MGPIO_vSetPinOutPutSpeed(PORTB, PIN6, MGPIO_SPEED_VHIGH);
	//		MGPIO_vSetPinOutPutSpeed(PORTB, PIN7, MGPIO_SPEED_VHIGH);
	//
	//			MGPIO_vSetAlternativeFunction(PORTB, PIN6,MGPIO_ALTFUNC_I2C13);
	//			MGPIO_vSetAlternativeFunction(PORTB, PIN7,MGPIO_ALTFUNC_I2C13);
	/* disable peripheral for resting all regs */
	CLR_BIT(I2Cx->CR1,CR1_PE);
	/* reset the peripheral */
	SET_BIT(I2Cx->CR1,CR1_SWRST);
	CLR_BIT(I2Cx->CR1,CR1_SWRST);

	/* PLCK */
	I2Cx->CR2 |= I2C_PCLK ;

	/* configure clock control register */
	/*For instance: in Sm mode, to generate a 100 kHz SCL frequency:
	If FREQR = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
	(0x28 <=> 40d x 125 ns = 5000 ns*/
	I2Cx->CCR |= 0x50 ;
	/* select standard mode */
	CLR_BIT(I2Cx->CCR,CCR_FS);

	/* configure rise time register */
	/*For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
	If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
	therefore the TRISE[5:0] bits must be programmed with 09h.
	(1000 ns / 125 ns = 8 + 1)*/
	I2Cx->TRISE = 17 ;

	/* Master own address */


	/* Peripheral Enable */
	SET_BIT(I2Cx->CR1,CR1_PE);



}
I2C_ERRORSTATS_t MI2C_vMasterTx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress , u8* Copy_u8Data , u8 Copy_u8DataLen,I2C_STOPSTAT_t StopStatus){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	u8 Local_StatFlag=NoError;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG; break;
	case I2C2: I2Cx=I2C2_REG; break;
	case I2C3: I2Cx=I2C3_REG; break;
	}
	/* generate start */
	Local_StatFlag=MI2C_vGenerateStart(I2Cx);
	if (Local_StatFlag !=NoError){
		MI2C_vMasterInit(Copy_I2CNumber);
		return Local_StatFlag;
	}

	/* clear start flag */
	MI2C_vClearStart(I2Cx);

	/* send slave address with write */
	//Copy_u8SlaveAddress = Copy_u8SlaveAddress<<1 ;
	//Copy_u8SlaveAddress &= ~(1);
	//I2Cx->DR= Copy_u8SlaveAddress  ;

	MI2C_vSendSlaveADDR(I2Cx, Copy_u8SlaveAddress, WithWrite);
	/*	if(GET_BIT(I2Cx->SR1,SR1_AF)){
		CLR_BIT(I2Cx->SR1,SR1_AF);
		MI2C_vGenerateStop(I2Cx);
		return ADDRFAIL;
	}*/
	/* clear ADDR flag */
	Local_StatFlag = MI2C_vClearADDR(I2Cx);
	if (Local_StatFlag !=NoError){
		MI2C_vMasterInit(Copy_I2CNumber);
		return Local_StatFlag;
	}


	u8 Count=0;
	while(Count<Copy_u8DataLen){

		/* write data in DR */
		Local_StatFlag=MI2C_vSendDataByte(I2Cx, Copy_u8Data[Count]);
		if(Local_StatFlag!= NoError){
			MI2C_vMasterInit(Copy_I2CNumber);
			return Local_StatFlag;
		}

		/* check  byte transfer successfully */
		// TODO : check if this works properly
		MSYSTICK_vStartTime();
		while( !GET_BIT(I2Cx->SR1,SR1_BTF) ){

			if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
				MSYSTICK_vStop();
				/* reset the peripheral */
				//					SET_BIT(I2Cx->CR1,CR1_SWRST);
				//					CLR_BIT(I2Cx->CR1,CR1_SWRST);
				//				// TODO:	MI2C_vMasterInit(Copy_I2CNumber);
				return DATAFAIL;
			}

		}
		Count++;
	}

	if(StopStatus == WithStop)
		/* generate stop condition */
		MI2C_vGenerateStop(I2Cx);


	return NoError;
}

I2C_ERRORSTATS_t MI2C_vMaster_MemWrite(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress ,u8*Copy_u8MemAdd,u8 Copy_u8MemAddLen, u8* Copy_u8Data , u8 Copy_u8DataLen){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	u8 Local_StatFlag=NoError;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG; break;
	case I2C2: I2Cx=I2C2_REG; break;
	case I2C3: I2Cx=I2C3_REG; break;
	}
	/* generate start */
	Local_StatFlag=MI2C_vGenerateStart(I2Cx);
	if (Local_StatFlag !=NoError){
		MI2C_vMasterInit(Copy_I2CNumber);
		return Local_StatFlag;
	}

	/* clear start flag */
	MI2C_vClearStart(I2Cx);

	MI2C_vSendSlaveADDR(I2Cx, Copy_u8SlaveAddress, WithWrite);

	/* clear ADDR flag */
	Local_StatFlag = MI2C_vClearADDR(I2Cx);
	if (Local_StatFlag !=NoError){
		MI2C_vMasterInit(Copy_I2CNumber);
		return Local_StatFlag;
	}

	/*********************** Send MemAdd************************************/
	u8 ADD_Count=0;
	while(ADD_Count<Copy_u8MemAddLen){

		/* write data in DR */
		Local_StatFlag=MI2C_vSendDataByte(I2Cx, Copy_u8MemAdd[ADD_Count]);
		if(Local_StatFlag!= NoError){
			MI2C_vMasterInit(Copy_I2CNumber);
			return Local_StatFlag;
		}

		/* check  byte transfer successfully */
		// TODO : check if this works properly
		MSYSTICK_vStartTime();
		while( !GET_BIT(I2Cx->SR1,SR1_BTF) ){

			if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
				MSYSTICK_vStop();
				return DATAFAIL;
			}

		}
		ADD_Count++;
	}



	/********************** Send Data *******************************/
	u8 Count=0;
	while(Count<Copy_u8DataLen){

		/* write data in DR */
		Local_StatFlag=MI2C_vSendDataByte(I2Cx, Copy_u8Data[Count]);
		if(Local_StatFlag!= NoError){
			MI2C_vMasterInit(Copy_I2CNumber);
			return Local_StatFlag;
		}

		/* check  byte transfer successfully */
		// TODO : check if this works properly
		MSYSTICK_vStartTime();
		while( !GET_BIT(I2Cx->SR1,SR1_BTF) ){

			if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
				MSYSTICK_vStop();
				return DATAFAIL;
			}

		}
		Count++;
	}
	/* generate stop condition */
	MI2C_vGenerateStop(I2Cx);


	return NoError;
}


u8 MI2C_u8MasterRx(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveAddress, u8* RxData , u8 DataLen ){
	u8 Local_StatFlag = NoError ;
	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG; break;
	case I2C2: I2Cx=I2C2_REG; break;
	case I2C3: I2Cx=I2C3_REG; break;
	}
	/* Generate Start */
	MI2C_vGenerateStart(I2Cx);
	if (Local_StatFlag !=NoError){
		MI2C_vMasterInit(Copy_I2CNumber);
		return Local_StatFlag;
	}

	/* Clear Start */
	MI2C_vClearStart(I2Cx);

	//	if(GET_BIT(I2Cx->SR1,SR1_AF)){
	//		CLR_BIT(I2Cx->SR1,SR1_AF);
	//		MI2C_vGenerateStop(I2Cx);
	//		return ADDRFAIL;
	//	}

	/* if receiving only one byte disable ack before clearing ADDR Flag */
	if(DataLen==1){
		/* send Slave address with read */
		MI2C_vSendSlaveADDR(I2Cx, Copy_u8SlaveAddress, WithRead);
		CLR_BIT(I2Cx->CR1,CR1_ACK);

		/* clear ADDR flag */
		Local_StatFlag=MI2C_vClearADDR(I2Cx);
		if (Local_StatFlag !=NoError){
			MI2C_vMasterInit(Copy_I2CNumber);
			return Local_StatFlag;
		}
		/* Generate Stop */
		SET_BIT(I2Cx->SR1,SR1_STOPF);
		/* read last data byte */
		RxData[0]=MI2C_vReadDataByte(I2Cx);
		return NoError;
	}

	/* send Slave address with read */
	MI2C_vSendSlaveADDR(I2Cx, Copy_u8SlaveAddress, WithRead);

	/* clear ADDR flag */
	Local_StatFlag=MI2C_vClearADDR(I2Cx);
	if (Local_StatFlag !=NoError){
		MI2C_vMasterInit(Copy_I2CNumber);
		return Local_StatFlag;
	}

	u8 Count =0;
	while(DataLen >2){
		RxData[Count]=MI2C_vReadDataByte(I2Cx);
		Count++;
		DataLen--;
		/* Enable ACK */
		SET_BIT(I2Cx->CR1,CR1_ACK);

	}
	/* read the second last data byte */
	RxData[Count]=MI2C_vReadDataByte(I2Cx);
	/* Disable ACK */
	CLR_BIT(I2Cx->CR1,CR1_ACK);
	/* Generate Stop */
	SET_BIT(I2Cx->SR1,SR1_STOPF);

	/* read last data byte */
	Count++;
	RxData[Count]=MI2C_vReadDataByte(I2Cx);

	return NoError ;
}

void MI2C_vSlaveInit(I2CNo_t Copy_I2CNumber , u8 Copy_u8SlaveOwnAddress){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG; break;
	case I2C2: I2Cx=I2C2_REG; break;
	case I2C3: I2Cx=I2C3_REG; break;
	}


	/* disable peripheral for resting all regs */
	CLR_BIT(I2Cx->CR1,CR1_PE);
	/* reset the peripheral */
	SET_BIT(I2Cx->CR1,CR1_SWRST);
	CLR_BIT(I2Cx->CR1,CR1_SWRST);

	/* PLCK */
	I2Cx->CR2 |= I2C_PCLK ;

	/* configure clock control register */
	/*For instance: in Sm mode, to generate a 100 kHz SCL frequency:
		If FREQR = 08, TPCLK1 = 125 ns so CCR must be programmed with 0x28
		(0x28 <=> 40d x 125 ns = 5000 ns*/
	I2Cx->CCR |= 0x50 ;
	/* select standard mode */
	CLR_BIT(I2Cx->CCR,CCR_FS);

	/* configure rise time register */
	/*For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
		If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
		therefore the TRISE[5:0] bits must be programmed with 09h.
		(1000 ns / 125 ns = 8 + 1)*/
	I2Cx->TRISE = 17 ;

	/* slave own address */
	I2Cx->OAR1 = Copy_u8SlaveOwnAddress<<1 ;

	/* Peripheral Enable */
	SET_BIT(I2Cx->CR1,CR1_PE);
	/* enable ACK */
	SET_BIT(I2Cx->CR1,CR1_ACK);



}

u8 MI2C_u8SlaveRx(I2CNo_t Copy_I2CNumber ){

	volatile I2C_Mem_Map_t* I2Cx = NULL_PTR;
	switch(Copy_I2CNumber){
	case I2C1: I2Cx=I2C1_REG; break;
	case I2C2: I2Cx=I2C2_REG; break;
	case I2C3: I2Cx=I2C3_REG; break;
	}
	/* check if the address flag is set */
	//while( !GET_BIT(I2Cx->SR1,SR1_ADDR));
	if( !GET_BIT(I2Cx->SR1,SR1_ADDR))
		return 0;
	/* clear ADDR */
	MI2C_vClearADDR(I2Cx);
	/* check the RX reg has received data */
	while( !GET_BIT(I2Cx->SR1,SR1_RXNE));
	/* read DR */
	u8 Local_u8RxData = (u8)I2Cx->DR;

	/* check stop bit flag */
	//while( !GET_BIT(I2Cx->SR1,SR1_STOPF));
	/* clear stop bit flag */
	/* read SR1 */
	u8 Local_u8Dummy = I2Cx->SR1;
	(void)Local_u8Dummy;
	/*write CR1*/
	SET_BIT(I2Cx->CR1,CR1_STOP);

	return Local_u8RxData ;

}




/******************************************************************************************************************************/

void MI2C_vSendSlaveADDR(volatile I2C_Mem_Map_t* I2Cx,u8 Copy_u8SlaveAddress,I2C_Dir_t Direction){

	switch(Direction){
	case(WithWrite):
																			I2Cx->DR=(Copy_u8SlaveAddress<<1); break;
	case(WithRead):
																			Copy_u8SlaveAddress= Copy_u8SlaveAddress<<1;
	Copy_u8SlaveAddress |= 1;
	I2Cx -> DR = Copy_u8SlaveAddress ;
	break;

	}

}

u8 MI2C_vSendDataByte(volatile I2C_Mem_Map_t* I2Cx , u8 Copy_u8Data){

	MSYSTICK_vStartTime();
	while( !GET_BIT(I2Cx->SR1,SR1_TXE) ){

		if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
			MSYSTICK_vStop();
			/* reset the peripheral */
			SET_BIT(I2Cx->CR1,CR1_SWRST);
			CLR_BIT(I2Cx->CR1,CR1_SWRST);

			return DATAFAIL;
		}
	}
	I2Cx->DR = Copy_u8Data;
	// TODO : use BTF ??
	return NoError;

}

u8 MI2C_vReadDataByte(volatile I2C_Mem_Map_t* I2Cx){

	MSYSTICK_vStartTime();
	while(!GET_BIT(I2Cx->SR1,SR1_RXNE)){
		if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
			MSYSTICK_vStop();
			//				/* reset the peripheral */
			//				SET_BIT(I2Cx->CR1,CR1_SWRST);
			//				CLR_BIT(I2Cx->CR1,CR1_SWRST);
			//				MI2C_vMasterInit(I2Cx);
			return DATAFAIL;
		}
	}
	u8 RxData = I2Cx ->DR ;
	return RxData ;
}

u8 MI2C_vGenerateStart(volatile I2C_Mem_Map_t* I2Cx){
	/* enable ACK */
	SET_BIT(I2Cx->CR1,CR1_ACK);

	SET_BIT(I2Cx->CR1,CR1_START);
	/* hold on start flag until set */
	MSYSTICK_vStartTime();
	while( !GET_BIT(I2Cx->SR1,SR1_SB)){

		if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
			MSYSTICK_vStop();
			/* reset the peripheral */
			SET_BIT(I2Cx->CR1,CR1_SWRST);
			CLR_BIT(I2Cx->CR1,CR1_SWRST);
			return STARTFAIL;
		}
	}
	return NoError;

}

void MI2C_vClearStart(volatile I2C_Mem_Map_t* I2Cx){

	u32 Local_u8Dummy = I2Cx->SR1;
	(void)Local_u8Dummy;
	//TODO
	/* writing data ( address ) in DR */
}
u8 MI2C_vClearADDR(volatile I2C_Mem_Map_t* I2Cx){

	MSYSTICK_vStartTime();
	while( !GET_BIT(I2Cx->SR1,SR1_ADDR)){

		if(MSYSTICK_f32GetElapsedTime()> I2C_TIMEOUT){
			MSYSTICK_vStop();
			/* reset the peripheral */
			SET_BIT(I2Cx->CR1,CR1_SWRST);
			CLR_BIT(I2Cx->CR1,CR1_SWRST);
			return ADDRFAIL;
		}
	}
	u32 Local_u8Dummy = I2Cx->SR1;
	Local_u8Dummy = I2Cx->SR2;
	(void)Local_u8Dummy;
	return NoError;
}

void MI2C_vGenerateStop(volatile I2C_Mem_Map_t* I2Cx){


	SET_BIT(I2Cx->CR1,CR1_STOP);

}

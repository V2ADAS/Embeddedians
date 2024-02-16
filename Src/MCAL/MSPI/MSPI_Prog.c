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
/*                  File Includes and Definitions                          */
/***************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include"MSPI_Private.h"
#include"MSPI_int.h"
#include "MSPI_Config.h"
#include"../MGPIO/MGPIO_int.h"

static void(*SPIx_pvTxcallback[4])(void)={STD_NULL};
static void(*SPIx_pvRXcallback[4])(void)={STD_NULL};

void MSPI_vMasterInit( u8 Local_u8SPINo ){

	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
	switch(Local_u8SPINo){
	case MSPI1: SPIx=SPI1  ; break;
	case MSPI2: SPIx=SPI2  ; break;
	case MSPI3: SPIx=SPI3  ; break;
	case MSPI4: SPIx=SPI4 ; break;
	}

	if(SPIx != STD_NULL){
	/* BAUD RATE */
	SPIx ->CR1 |=  (BAUD_RATE<< CR1_BR );

	/* Default clock phase */

	/* DATA FRAME */
#if DATA_FRAME == FRAME_8_BIT
	CLR_BIT(SPIx->CR1 ,CR1_DFF);

#elif DATA_FRAME == FRAME_16_BIT
	SET_BIT(SPIx->CR1,CR1_DFF);

#endif
	/* MSB or LSB */

	/* NSS */
	/* In NSS software mode,
     *set the SSM and SSI bits in the SPI_CR1 register
     */
	SET_BIT(SPIx->CR1,CR1_SSM);
	SET_BIT(SPIx->CR1,CR1_SSI);
	/* Select as Master */
	SET_BIT(SPIx->CR1,CR1_MSTR);

	/* Enable SPI */
	SET_BIT(SPIx->CR1,CR1_SPE);

	}

}

void MSPI_vSlaveInit( u8 Local_u8SPINo ){

	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
		switch(Local_u8SPINo){
		case MSPI1: SPIx=SPI1  ; break;
		case MSPI2: SPIx=SPI2  ; break;
		case MSPI3: SPIx=SPI3  ; break;
		case MSPI4: SPIx=SPI4 ; break;
		}
	if(SPIx != STD_NULL){

	/* DATA FRAME */
	#if DATA_FRAME == FRAME_8_BIT
		CLR_BIT(SPIx->CR1 ,CR1_DFF);

	#elif DATA_FRAME == FRAME_16_BIT
		SET_BIT(SPIx->CR1,CR1_DFF);

	#endif
		/* Clock Polarity & Clock Phase */

		/* Frame format */
		/* NSS Bit --> Hardware */
		CLR_BIT(SPIx->CR1,CR1_SSM);
		/* Select as SLAVE */
		CLR_BIT(SPIx->CR1,CR1_MSTR);

		/* Enable SPI */
		SET_BIT(SPIx->CR1,CR1_SPE);

	}
}

u8 MSPI_u8MasterTransceiver( u8 Local_u8SPINo,u8 Local_u8SlavePort , u8 Local_u8SlavePin ,u8 Local_u8Data){

	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
				switch(Local_u8SPINo){
				case MSPI1: SPIx=SPI1  ; break;
				case MSPI2: SPIx=SPI2  ; break;
				case MSPI3: SPIx=SPI3  ; break;
				case MSPI4: SPIx=SPI4 ; break;
				}


		// activate slave
		MGPIO_vSetPinValue(Local_u8SlavePort,Local_u8SlavePin,LOW);
		if(SPIx != STD_NULL){
		/* PUT DATA in Tx BUFFER */
			SPIx ->DR = Local_u8Data ;

		/* Wait until data is transmitted */
			while(GET_BIT(SPIx->SR,SR_TXE)==0);

		/* wait until data is received */
			while(GET_BIT(SPIx->SR,SR_RXNE)==0);
		/* wait until busy flag is 0 */
			//while(GET_BIT(SPIx->SR,SR_BSY)==1);

		/* deactivate slave */
			MGPIO_vSetPinValue(Local_u8SlavePort,Local_u8SlavePin,HIGH);

			return  (u8)SPIx->DR;
		}



			return 0 ;


	}




u8 MSPI_u8SlaveTransceiver( u8 Local_u8SPINo ,u8 Local_u8Data){


	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
				switch(Local_u8SPINo){
				case MSPI1: SPIx=SPI1  ; break;
				case MSPI2: SPIx=SPI2  ; break;
				case MSPI3: SPIx=SPI3  ; break;
				case MSPI4: SPIx=SPI4 ; break;
				}

		if(SPIx != STD_NULL){
		/* PUT DATA in Tx BUFFER */
			SPIx ->DR = Local_u8Data ;

		/* Wait until data is transmitted */
			while(GET_BIT(SPIx->SR,SR_TXE)==0);

		/* wait until data is received */
			while(GET_BIT(SPIx->SR,SR_RXNE)==0);
		/* wait until busy flag is 0 */
			//while(GET_BIT(SPIx->SR,SR_BSY)==1);

			return  (u8)SPIx->DR;
		}

			return 0 ;
	}

void MSPI_vEnableRxInt(u8 Local_u8SPINo){

	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
					switch(Local_u8SPINo){
					case MSPI1: SPIx=SPI1  ; break;
					case MSPI2: SPIx=SPI2  ; break;
					case MSPI3: SPIx=SPI3  ; break;
					case MSPI4: SPIx=SPI4 ; break;
					}
	if ( SPIx == STD_NULL)
		return;

	SET_BIT(SPIx->CR2,CR2_RXNEIE);
}

void MSPI_vEnableTxInt(u8 Local_u8SPINo){


	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
	switch(Local_u8SPINo){
		case MSPI1: SPIx=SPI1  ; break;
		case MSPI2: SPIx=SPI2  ; break;
		case MSPI3: SPIx=SPI3  ; break;
		case MSPI4: SPIx=SPI4 ; break;
						}
		if ( SPIx == STD_NULL)
			return;

		SET_BIT(SPIx->CR2,CR2_TXEIE);
	}



void MSPI_vSetTxCallBackFunc(u8 Local_u8SPINo,void(*Local_pvTxIRQ)(void)){

	SPIx_pvTxcallback[Local_u8SPINo]=Local_pvTxIRQ;


}

void MSPI_vSetRxCallBackFunc(u8 Local_u8SPINo,void(*Local_pvRxIRQ)(void)){

	SPIx_pvRXcallback[Local_u8SPINo]=Local_pvRxIRQ;


}


u8 MSPI_u8ReadRecievedData(u8 Local_u8SPINo){

	volatile SPI_Mem_Map_t* SPIx = STD_NULL ;
		switch(Local_u8SPINo){
			case MSPI1: SPIx=SPI1  ; break;
			case MSPI2: SPIx=SPI2  ; break;
			case MSPI3: SPIx=SPI3  ; break;
			case MSPI4: SPIx=SPI4 ; break;
							}
		u8 Local_u8ReceivedData = SPIx->DR;
		return Local_u8ReceivedData;

}

void SPI1_IRQHandler(){

	if( GET_BIT(SPI1->SR,SR_TXE) && SPIx_pvTxcallback[0]!=STD_NULL)
		SPIx_pvTxcallback[0]();


	if( GET_BIT(SPI1->SR,SR_RXNE) && SPIx_pvRXcallback[0]!=STD_NULL)
		SPIx_pvRXcallback[0]();
}

void SPI2_IRQHandler(){

	if( GET_BIT(SPI1->SR,SR_TXE) && SPIx_pvTxcallback[1]!=STD_NULL)
			SPIx_pvTxcallback[1]();


		if( GET_BIT(SPI1->SR,SR_RXNE) && SPIx_pvRXcallback[1]!=STD_NULL)
			SPIx_pvRXcallback[1]();

}

void SPI3_IRQHandler(){

	if( GET_BIT(SPI1->SR,SR_TXE) && SPIx_pvTxcallback[2]!=STD_NULL)
			SPIx_pvTxcallback[2]();


		if( GET_BIT(SPI1->SR,SR_RXNE) && SPIx_pvRXcallback[2]!=STD_NULL)
			SPIx_pvRXcallback[2]();

}

void SPI4_IRQHandler(){

	if( GET_BIT(SPI1->SR,SR_TXE) && SPIx_pvTxcallback[3]!=STD_NULL)
			SPIx_pvTxcallback[3]();


		if( GET_BIT(SPI1->SR,SR_RXNE) && SPIx_pvRXcallback[3]!=STD_NULL)
			SPIx_pvRXcallback[3]();

}

/***************************************************************************/
/* Author       : Mohamed Hawas                                              */
/* Version      : V0.0.0                                                   */
/*  Date        :  8 Jun 2023                                              */
/*  Author      : John                                                     */
/*  Description : Driver Functions Implementation                          */
/*  Features    :                                                          */
/***************************************************************************/

/***************************************************************************/
/*                        Standard Types LIB                               */
/***************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/***************************************************************************/
/*                           MCAL Components                               */
/***************************************************************************/
#include "MUSART_Interface.h"
#include "MUSART_Config.h"
#include "MUSART_Private.h"
/***************************************************************************/
/*                        Functions Implementations                        */
/***************************************************************************/

void MUART_Enable(u8 UART_Index)
{
	USART_REG UARTx = Get_UART(UART_Index);
	/*Enable Uart */
	UARTx ->CR1.UE = 1 ;

	/*Select BaudRate -> 9600*/
	UARTx ->BRR = 0x683;

	/* Select Stop Bits As 1-BIT */
	UARTx -> CR2.STOP |= (USART1_ONE_STOP_BITS << 12);

	/* ENABLE RX */
	UARTx ->CR1.RE = 1;

	/* ENABLE TX */
	UARTx ->CR1.TE = 1;

	/* Select No Sending BREAK */
	UARTx ->CR1.SBK = 0 ;

	/* Select Disable Parity */
	UARTx ->CR1.PCE = 0;

	/* SELECT WORD LENGHT AS 8DATA-BITS */
	UARTx ->CR1.M = _8DATA_LENGTH_ ;

	/*SELECT OVER SAMPLING BY 16*/
	UARTx ->CR1.OVER8 = 0;

}


void MUART_Disable(u8 UART_Index)
{
	USART_REG UARTx = Get_UART(UART_Index);
	UARTx ->CR1.UE = 0 ;
}

void MUART_Send_Byte(u8 UART_Index ,u8 data){
	USART_REG UARTx = Get_UART(UART_Index);
	while(GET_BIT(USART1_REG ->SR,7) == 0);
	UARTx->DR = data;
}


void MUART_Send_Data(u8 UART_Index , u8 *data)
{
	u8 i = 0 ;
	u8 length =sizeof(*data);
	USART_REG UARTx = Get_UART(UART_Index);
	for(i = 0; i < length; i++)
	{
		//Busy wait until transmission complete
		while(GET_BIT(USART1_REG ->SR,7) == 0);
		UARTx->DR = data[i] ;
	}
}


u8 MUART_Receive_Byte(u8 UART_Index)
{
	u8 data ;
	USART_REG UARTx = Get_UART(UART_Index);
	//Busy wait until reception complete then read it
	while(!GET_BIT(UARTx ->SR,5));
	data = (UARTx ->DR);
	return (u8)data;
}


void MUART_Receive_Data(u8 UART_Index ,u8 Buffer[] ,u8 max_size)
{
	
}

USART_REG Get_UART(u8 UART_Index){
	USART_REG UARTx ;
	switch(UART_Index)
	{
	case 1: UARTx = USART1_REG ; break;
	case 2: UARTx = USART2_REG ; break;
	case 6: UARTx = USART6_REG ; break;
	}
	return UARTx;
}






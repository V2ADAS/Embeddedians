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
#include "../MNVIC/MNVIC_int.h"
#include "../MGPIO/MGPIO_int.h"

/***************************************************************************/
/*                        Functions Implementations                        */
/***************************************************************************/
static void(*UARTx_pvRXcallback[3])(void)={STD_NULL};

volatile USART_t * UART_1 = (USART_t*)USART1_BASE_ADDRESS ;
volatile USART_t * UART_2 = (USART_t*)USART2_BASE_ADDRESS ;
volatile USART_t * UART_6 = (USART_t*)USART6_BASE_ADDRESS ;

void MUART_Enable(u8 UART_Index)
{

	USART_t * UARTx = (USART_t *)Get_UART(UART_Index);
	/*Enable Uart */

	/*Select BaudRate -> 9600*/
	UARTx ->BRR = 0x683; //clock 16
	//	UARTx ->BRR = 0x341; //clock 8

	/* Select Stop Bits As 1-BIT */
	UARTx -> CR2.STOP |= (USART1_ONE_STOP_BITS << 12);

	/* Select Disable Parity */
	UARTx ->CR1.PCE = 0;

	/* ENABLE RX */
	UARTx ->CR1.RE = 1;
	UARTx ->CR1.RXNEIE=1;


	/* ENABLE TX */
	UARTx ->CR1.TE = 1;

	/* Select No Sending BREAK */
	UARTx ->CR1.SBK = 0 ;

	/* SELECT WORD LENGHT AS 8DATA-BITS */
	UARTx ->CR1.M = _9DATA_LENGTH_ ;

	/*SELECT OVER SAMPLING BY 16*/
	UARTx ->CR1.OVER8 = 0 ;

	UARTx ->CR1.UE = 1 ;

}

void MUART_Init(u8 UART_Index)
{
	switch (UART_Index) {
	case UART1:
		// Tx : A9
		MGPIO_vSetPinMode(PORTA, PIN9 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, PIN9, AF7);
		//Rx : A10
		MGPIO_vSetPinMode(PORTA, PIN10 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, PIN10, AF7);
		MNVIC_vEnableInterrupt(NVIC_USART1);

		//	MGPIO_vSetPinOutPutType(PORTA, PIN9,GPIO_PUSH_PULL);
		//	MGPIO_vSetPinOutPutSpeed(PORTA, PIN9,MGPIO_SPEED_MEDIUM);
		//	MGPIO_vSetPinInPutType(PORTA, PIN9,PULLUP);
		//	MGPIO_vSetPinInPutType(PORTA, PIN10,PULLUP);
		break;

	case UART2:
		//Tx :A2
		MGPIO_vSetPinMode(PORTA, PIN2 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, PIN2, AF7);
		//Rx : A3
		MGPIO_vSetPinMode(PORTA, PIN3 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, PIN3, AF7);
		MNVIC_vEnableInterrupt(NVIC_USART2);
		break;

	case UART6:
		//Tx : A11
		MGPIO_vSetPinMode(PORTA, PIN11 ,ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, PIN11, AF8);
		//Rx : A12
		MGPIO_vSetPinMode(PORTA, PIN12 , ALTFUNC);
		MGPIO_vSetAlternativeFunction(PORTA, PIN12, AF8);
		MNVIC_vEnableInterrupt(NVIC_USART6);
		break;
	}
}


void MUART_Disable(u8 UART_Index)
{
	USART_t * UARTx = Get_UART(UART_Index);
	UARTx ->CR1.UE = 0 ;
}

void MUART_Send_Byte(u8 UART_Index ,u8 data){
	USART_t * UARTx = Get_UART(UART_Index);
	while(GET_BIT(UARTx ->SR,7) == 0);
	UARTx->DR = data;
}


void MUART_Send_Data(u8 UART_Index , u8 *ptrToData , u16 size)
{
	USART_t * UARTx = Get_UART(UART_Index);
	for(int i = 0; i < size; i++)
	{
		UARTx->DR = *ptrToData ;
		//Busy wait until transmission complete
		while(GET_BIT(UARTx ->SR,7) == 0);
		ptrToData++ ;
	}
}


u8 MUART_Receive_Byte(u8 UART_Index)
{
	u8 data ;
	USART_t * UARTx = Get_UART(UART_Index);
	//Busy wait until reception complete then read it
	while(!GET_BIT(UARTx ->SR,5));
	data = (UARTx ->DR);
	return (u8)data;
}


u8 MUART_Receive_Data(u8 UART_Index)
{
	u8 data ;
	USART_t * UARTx = Get_UART(UART_Index);
	data = (UARTx ->DR);
	return (u8)data;
}

USART_t * Get_UART(u8 UART_Index){
	USART_t * UARTx ;
	switch(UART_Index)
	{
	case 1: UARTx = UART_1 ; break;
	case 2: UARTx = UART_2 ; break;
	case 6: UARTx = UART_6 ; break;
//	case 1: UARTx = USART1_REG ; break;
//	case 2: UARTx = USART2_REG ; break;
//	case 6: UARTx = USART6_REG ; break;
	}
	return UARTx;
}

void MUART_vSetRxCallBackFunc(u8 UART_Index,void(*Local_pvRxIRQ)(void)){
	switch (UART_Index) {
	case UART1:
		UARTx_pvRXcallback[0]=Local_pvRxIRQ;
		break;
	case UART2:
		UARTx_pvRXcallback[1]=Local_pvRxIRQ;
		break;
	case UART6:
		UARTx_pvRXcallback[2]=Local_pvRxIRQ;
		break;
	}
}


void USART1_IRQHandler(void)
{
	UARTx_pvRXcallback[0]();
	MNVIC_vClearPendingFlag(NVIC_USART1);
}
void USART2_IRQHandler(void)
{
	UARTx_pvRXcallback[1]();
	MNVIC_vClearPendingFlag(NVIC_USART2);
}
void USART6_IRQHandler(void)
{
	UARTx_pvRXcallback[2]();
	MNVIC_vClearPendingFlag(NVIC_USART6);
}

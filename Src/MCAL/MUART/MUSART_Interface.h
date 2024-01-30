/***************************************************************************/
/* Author       : John Makkar                                              */
/* Version      : V0.0.0                                                   */
/*  Date        :  8 Jun 2023                                              */
/*  Author      : John                                                     */
/*  Description : Driver Functions Prototypes                              */
/*  Features    :                                                          */
/***************************************************************************/

#ifndef MUSART_INTERFACE_H_
#define MUSART_INTERFACE_H_

#include "MUSART_Private.h"
/***************************************************************************/
/*                        Functions Prototypes                             */
/***************************************************************************/
void MUART_Enable(u8 UART_Index);
void MUART_Disable(u8 UART_Index);
void MUART_Send_Byte(u8 UART_Index ,u8 data);
void MUART_Send_Data(u8 UART_Index ,u8* data);
u8 MUART_Receive_Byte(u8 UART_Index);
void MUART_Receive_Data(u8 UART_Index,u8 Buffer[] ,u8 max_size);
USART_REG Get_UART(u8 UART_Index);


#endif /* MUSART_INTERFACE_H_ */


#include"MCAL/MRCC/MRCC_int.h"
#include"MCAL/MGPIO/MGPIO_int.h"
#include"MCAL/MNVIC/MNVIC_int.h"
#include"MCAL/MEXTI/MEXTI_int.h"
#include"MCAL/MIWDT/MIWDT_int.h"
#include"MCAL/MSTK/MSYSTICK_int.h"
#include"MCAL/MSPI/MSPI_int.h"
#include"MCAL/MRCC/MRCC_private.h"
#include"MCAL/MUART/MUSART_Interface.h"
#include"MCAL/MUART/MUSART_Config.h"
#include"MCAL/MUART/MUSART_Private.h"
//#include"APP/Inc/Path_Tracking.h"


typedef struct  {
	u8 start ;
	u8 c ;
	u16 b ;
	u16 Tx_Data[10];

}Data_ST ;
 
data_st Tx = {'*' , 50 , 500 , {10, 20, 30, 40, 50, 60, 70, 80, 90, 100} } ;
data_st Rx = {0};
u8 * Rx_ptr = &Rx ;

void Rx_callback()
{
	u8 data_rx ;
	data_rx = MUART_Receive_Data(UART2);
	if (data_rx == '*')
		Rx_ptr = &Rx ;
	*Rx_ptr = data_rx ;
	Rx_ptr++;
//	if (data_rx == 100 )
//		MGPIO_vSetPinValue(PORTC, PIN14, HIGH);

}


int main (void){


	MRCC_vInit();
	MRCC_vEnableClock(GPIOA_EN);
	MRCC_vEnableClock(GPIOB_EN);
	MRCC_vEnableClock(GPIOC_EN);
	MRCC_vEnableClock(USART1_EN);
	MRCC_vEnableClock(USART2_EN);
	MRCC_vEnableClock(USART6_EN);


	MGPIO_vSetPinMode(PORTC, PIN13, OUTPUT);
	MGPIO_vSetPinValue(PORTC, PIN13, HIGH);
	MGPIO_vSetPinMode(PORTC, PIN14, OUTPUT);
	MGPIO_vSetPinMode(PORTC, PIN15, OUTPUT);
	MUART_Init(UART1);
	MUART_Init(UART2);
	MUART_Init(UART6);

	MUART_vSetRxCallBackFunc(UART2,Rx_callback);

	MUART_Enable(UART6);
	MUART_Enable(UART2);
	MUART_Enable(UART1);
	u8 a = 20 ;
	u8 *ptr = &Tx ;
	u8 size = sizeof(Tx);


	while(1){
		MUART_Send_Data(UART1, ptr  ,size );


		MGPIO_vSetPinValue(PORTC, PIN13, HIGH);
		MSYSTICK_vDelayms(500);
		MGPIO_vSetPinValue(PORTC, PIN13, LOW);
		MSYSTICK_vDelayms(500);
	}

}

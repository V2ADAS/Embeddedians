/*
 * MGPIO_int.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Omar
 */

#ifndef MCAL_MGPIO_MGPIO_INT_H_
#define MCAL_MGPIO_MGPIO_INT_H_
#include"../../LIB/STD_TYPES.h"
#define PIN0					0
#define PIN1					1
#define PIN2					2
#define PIN3					3
#define PIN4					4
#define PIN5					5
#define PIN6					6
#define PIN7					7
#define PIN8					8
#define PIN9					9
#define PIN10					10
#define PIN11					11
#define PIN12					12
#define PIN13					13
#define PIN14					14
#define PIN15					15

#define INPUT		0b00
#define OUTPUT		0b01
#define ALTFUNC		0b10
#define ANALOG		0b11

#define MGPIO_SPEED_LOW			0b00
#define MGPIO_SPEED_MEDIUM		0b01
#define MGPIO_SPEED_HIGH		0b10
#define MGPIO_SPEED_VHIGH		0b11

#define NOPULL		0b00
#define PULLUP		0b01
#define PULLDOWN	0b10

typedef enum{

	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF15

} ALTFUNC_Map_t;

#define MGPIO_ALTFUNC_SYS		AF0
#define MGPIO_ALTFUNC_TIM12		AF1
#define MGPIO_ALTFUNC_TIM35		AF2
#define MGPIO_ALTFUNC_TIM911	AF3
#define MGPIO_ALTFUNC_I2C13		AF4
#define MGPIO_ALTFUNC_SPI14		AF5
#define MGPIO_ALTFUNC_SPI3		AF6
#define MGPIO_ALTFUNC_USART12	AF7
#define MGPIO_ALTFUNC_USART6	AF8
#define MGPIO_ALTFUNC_I2C23		AF9
#define MGPIO_ALTFUNC_OTG_FS	AF10
#define MGPIO_ALTFUNC_NULL		AF11
#define MGPIO_ALTFUNC_SDIO		AF12
#define MGPIO_ALTFUNC_NULL2		AF13
#define MGPIO_ALTFUNC_NULL3		AF14
#define MGPIO_ALTFUNC_EVENTOUT	AF15


#define PORTA					0
#define PORTB					1
#define PORTC					2

#define GPIO_OPEN_DRAIN				1
#define GPIO_PUSH_PULL				0

#define HIGH					1
#define LOW					0

/****************** Functions ProtoType **********************************/

void MGPIO_vSetPinMode( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinMode);

void MGPIO_vSetPinOutPutType( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinOutPutType);

void MGPIO_vSetPinOutPutSpeed( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinOutPutSpeed);

void MGPIO_vSetPinInPutType( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinInputType);

u8 MGPIO_u8GetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinNo);

void MGPIO_vSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinNo ,u8 Copy_u8PinValue);

/******* BSRR ********/
void MGPIO_vSetPinAtomic(u8 Copy_u8PortID, u8 Copy_u8PinNo ,u8 Copy_u8PinValue);

void MGPIO_vSetAlternativeFunction(u8 Copy_u8PortID, u8 Copy_u8PinNo ,u8 Copy_u8FunctionName);



#endif /* MCAL_MGPIO_MGPIO_INT_H_ */

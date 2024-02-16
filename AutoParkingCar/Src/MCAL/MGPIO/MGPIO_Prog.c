/*
 * MGPIO_Prog.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Omar
 */

#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES.h"

#include"MGPIO_Config.h"
#include"MGPIO_Private.h"
#include"MGPIO_int.h"


void MGPIO_vSetPinMode( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinMode){

	   switch(Copy_u8PortID){
	   case PORTA:
		   /*clear the current mode*/
		   GPIOA -> MODER &= ~(0b11<<(Copy_u8PinNo*2));
		   /* set the desired mode*/
		   GPIOA -> MODER |= (Copy_u8PinMode <<(Copy_u8PinNo*2));
		   break;
	   case PORTB:
	  		   /*clear the current mode*/
	  		   GPIOB -> MODER &= ~(0b11<<(Copy_u8PinNo*2));
	  		   /* set the desired mode*/
	  		   GPIOB -> MODER |= (Copy_u8PinMode <<(Copy_u8PinNo*2));
	  		   break;
	   case PORTC:
	  		   /*clear the current mode*/
	  		   GPIOC -> MODER &= ~(0b11<<(Copy_u8PinNo*2));
	  		   /* set the desired mode*/
	  		   GPIOC -> MODER |= (Copy_u8PinMode <<(Copy_u8PinNo*2));
	  		   break;
	   }
}

void MGPIO_vSetPinOutPutType( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinOutPutType){

	switch(Copy_u8PortID){
	case PORTA:
		if(Copy_u8PinOutPutType == GPIO_OPEN_DRAIN)
			SET_BIT(GPIOA -> OTYPER , Copy_u8PinNo);
		else
			CLR_BIT(GPIOA -> OTYPER , Copy_u8PinNo);
		break;
	case PORTB:
			if(Copy_u8PinOutPutType == GPIO_OPEN_DRAIN)
				SET_BIT(GPIOB -> OTYPER , Copy_u8PinNo);
			else
				CLR_BIT(GPIOB -> OTYPER , Copy_u8PinNo);
			break;
	case PORTC:
			if(Copy_u8PinOutPutType == GPIO_OPEN_DRAIN)
				SET_BIT(GPIOC -> OTYPER , Copy_u8PinNo);
			else
				CLR_BIT(GPIOC -> OTYPER , Copy_u8PinNo);
			break;

	}
}

void MGPIO_vSetPinOutPutSpeed( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinOutPutSpeed){

	switch(Copy_u8PortID){
		   case PORTA:
			   /*clear the current speed*/
			   GPIOA -> OSPEEDR &= ~(0b11<<(Copy_u8PinNo*2));
			   /* set the desired speed*/
			   GPIOA -> OSPEEDR |= (Copy_u8PinOutPutSpeed <<(Copy_u8PinNo*2));
			   break;
		   case PORTB:
		  		   /*clear the current speed*/
		  		   GPIOB -> OSPEEDR &= ~(0b11<<(Copy_u8PinNo*2));
		  		   /* set the desired speed*/
		  		   GPIOB -> OSPEEDR |= (Copy_u8PinOutPutSpeed <<(Copy_u8PinNo*2));
		  		   break;
		   case PORTC:
		  		   /*clear the current speed*/
		  		   GPIOC -> OSPEEDR &= ~(0b11<<(Copy_u8PinNo*2));
		  		   /* set the desired speed*/
		  		   GPIOC -> OSPEEDR |= (Copy_u8PinOutPutSpeed <<(Copy_u8PinNo*2));
		  		   break;
		   }
}

void MGPIO_vSetPinInPutType( u8 Copy_u8PortID, u8 Copy_u8PinNo , u8 Copy_u8PinInputType){

	switch(Copy_u8PortID){
			   case PORTA:
				   /*clear the current pull*/
				   GPIOA -> PUPDR &= ~(0b11<<(Copy_u8PinNo*2));
				   /* set the desired pull */
				   GPIOA -> PUPDR |= (Copy_u8PinInputType <<(Copy_u8PinNo*2));
				   break;
			   case PORTB:
			  		   /*clear the current pull */
			  		   GPIOB -> PUPDR &= ~(0b11<<(Copy_u8PinNo*2));
			  		   /* set the desired pull */
			  		   GPIOB -> PUPDR |= (Copy_u8PinInputType <<(Copy_u8PinNo*2));
			  		   break;
			   case PORTC:
			  		   /*clear the current pull */
			  		   GPIOC -> PUPDR &= ~(0b11<<(Copy_u8PinNo*2));
			  		   /* set the desired pull */
			  		   GPIOC -> PUPDR |= (Copy_u8PinInputType <<(Copy_u8PinNo*2));
			  		   break;
			   }
}

u8 MGPIO_u8GetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinNo){

		u8 Local_u8PinVal = 0;
		switch(Copy_u8PortID){
		case PORTA:
			Local_u8PinVal= GET_BIT(GPIOA -> IDR , Copy_u8PinNo);
			break;
		case PORTB:
					Local_u8PinVal= GET_BIT(GPIOB -> IDR , Copy_u8PinNo);
					break;
		case PORTC:
					Local_u8PinVal= GET_BIT(GPIOC -> IDR , Copy_u8PinNo);
					break;
		}
		return Local_u8PinVal;
}

void MGPIO_vSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinNo ,u8 Copy_u8PinValue){

	switch(Copy_u8PortID){
		case PORTA:
			if(Copy_u8PinValue == HIGH)
				SET_BIT(GPIOA -> ODR , Copy_u8PinNo);
			else
				CLR_BIT(GPIOA -> ODR , Copy_u8PinNo);
			break;
		case PORTB:
				if(Copy_u8PinValue == HIGH)
					SET_BIT(GPIOB -> ODR , Copy_u8PinNo);
				else
					CLR_BIT(GPIOB -> ODR , Copy_u8PinNo);
				break;
		case PORTC:
				if(Copy_u8PinValue == HIGH)
					SET_BIT(GPIOC -> ODR , Copy_u8PinNo);
				else
					CLR_BIT(GPIOC -> ODR , Copy_u8PinNo);
				break;

		}
}

/******* BSRR ********/
/***
 * it seem to be  wrong implementation
 * as set_bit is  REG |= 1<< pino  --> read ,modify, write
 *
 * the correct atomic funtion should be
 * set_bit_fast REG = 1<< pino --> write
 *
 * **/
void MGPIO_vSetPinAtomic(u8 Copy_u8PortID, u8 Copy_u8PinNo ,u8 Copy_u8PinValue){

	switch(Copy_u8PortID){
			case PORTA:
				if(Copy_u8PinValue == HIGH)
					SET_BIT(GPIOA -> BSRR , Copy_u8PinNo);
				else
					SET_BIT(GPIOA -> BSRR , (Copy_u8PinNo+16));
				break;
			case PORTB:
					if(Copy_u8PinValue == HIGH)
						SET_BIT(GPIOB -> BSRR , Copy_u8PinNo);
					else
						SET_BIT(GPIOB -> BSRR , (Copy_u8PinNo+16));
					break;
			case PORTC:
					if(Copy_u8PinValue == HIGH)
						SET_BIT(GPIOC -> BSRR , Copy_u8PinNo);
					else
						SET_BIT(GPIOC -> BSRR , (Copy_u8PinNo+16));
					break;

			}
}

void MGPIO_vSetAlternativeFunction(u8 Copy_u8PortID, u8 Copy_u8PinNo ,u8 Copy_u8FunctionName){


	switch(Copy_u8PortID){
	case PORTA:
		if(Copy_u8PinNo <=7 ){
			/* Clear the current alt func */
			GPIOA -> AFRL &= ~(0b1111 << (Copy_u8PinNo*4) );
			/* set the desired alt func */
			GPIOA -> AFRL |= (Copy_u8FunctionName <<(Copy_u8PinNo*4));
		}
		else{
			Copy_u8PinNo-=8;
			/* Clear the current alt func */
			GPIOA -> AFRH &= ~(0b1111 << (Copy_u8PinNo*4) );
			/* set the desired alt func */
			GPIOA -> AFRH |= (Copy_u8FunctionName <<(Copy_u8PinNo*4));
		}
		break;
	case PORTB:
			if(Copy_u8PinNo <=7 ){
				/* Clear the current alt func */
				GPIOB -> AFRL &= ~(0b1111 << (Copy_u8PinNo*4) );
				/* set the desired alt func */
				GPIOB -> AFRL |= (Copy_u8FunctionName <<(Copy_u8PinNo*4));
			}
			else{
				Copy_u8PinNo-=8;
				/* Clear the current alt func */
				GPIOB -> AFRH &= ~(0b1111 << (Copy_u8PinNo*4) );
				/* set the desired alt func */
				GPIOB -> AFRH |= (Copy_u8FunctionName <<(Copy_u8PinNo*4));
			}
			break;
	case PORTC:
			if(Copy_u8PinNo <=7 ){
				/* Clear the current alt func */
				GPIOC -> AFRL &= ~(0b1111 << (Copy_u8PinNo*4) );
				/* set the desired alt func */
				GPIOC -> AFRL |= (Copy_u8FunctionName <<(Copy_u8PinNo*4));
			}
			else{
				Copy_u8PinNo-=8;
				/* Clear the current alt func */
				GPIOC -> AFRH &= ~(0b1111 << (Copy_u8PinNo*4) );
				/* set the desired alt func */
				GPIOC -> AFRH |= (Copy_u8FunctionName <<(Copy_u8PinNo*4));
			}
			break;

	}



}

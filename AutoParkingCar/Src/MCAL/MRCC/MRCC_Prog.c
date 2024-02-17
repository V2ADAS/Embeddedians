/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                   */
/* Version           : V0.0.0                                                                          */
/* Data              : 5 nov 2023                                                                      */
/* Description       : Driver Functions Implementation                                                 */
/*******************************************************************************************************/

/***************************************************************************/
/*                           MCAL Components                               */
/***************************************************************************/
#include"MRCC_Config.h"
#include"MRCC_Private.h"
#include"MRCC_Int.h"

/***************************************************************************/
/*                        Functions Implementations                        */
/***************************************************************************/
void MRCC_vInit(void){
	/*CSS (ON/OFF)*/

#if RCC_SYS_CLK == RCC_HSE
	  //HSEBYP CLR -> Oscillator is Enabled 'Not Bypassed'
	  CLR_BIT(RCC->CR,HSEBYP);
	  //Enable Selected Clock
	  SET_BIT(RCC->CR,HSEON);
	  // Wait Until HSE is ready "Clock is working properly"
	  while( !GET_BIT(RCC->CR,HSERDY) );
	  //Select System Clock
	  CLR_SET(RCC->CFGR,SW0);
	  //Wait until HSE is used as system clock source
	  while( GET_2BITS(RCC->CFGR,SWS0) != SWS_HSE );
#elif RCC_SYS_CLK == RCC_HSI
	  //Enable Selected Clock
	  SET_BIT(RCC->CR,HSION);
	  // Wait Until HSI is ready "Clock is working properly"
	  while( !GET_BIT(RCC->CR,HSIRDY) );
	  //Select System Clock
	  CLR_2BITS(RCC->CFGR,SW0);
	  //Wait until HSI is used as system clock source
	  while( GET_2BITS(RCC->CFGR,SWS0) != SWS_HSI );
#elif RCC_SYS_CLK == RCC_PLL
		  //Select Clock
		  SET_CLR(RCC->CFGR,SW0);
		  //Wait until PLL is used as system clock source
		  //while( GET_2BITS(RCC->CFGR,SWS0) != SWS_PLL );
		  //Enable Selected Clock
		  SET_BIT(RCC->CR,PLLON);
		  // Wait Until PLL is ready "Clock is working properly"
		  while( !GET_BIT(RCC->CR,PLLRDY) );
#endif

}

void MRCC_vEnableClock(PeripheralEnable_t Copy_u8PeripheralNo){
	if(Copy_u8PeripheralNo >= 96){
		Copy_u8PeripheralNo -= 96;
		SET_BIT(RCC->APB2ENR,Copy_u8PeripheralNo);
	}
	else if(Copy_u8PeripheralNo >= 64){
		Copy_u8PeripheralNo -= 64;
		SET_BIT(RCC->APB1ENR,Copy_u8PeripheralNo);
	}
	else if(Copy_u8PeripheralNo >= 32){
		Copy_u8PeripheralNo -= 32;
		SET_BIT(RCC->AHB2ENR,Copy_u8PeripheralNo);
	}
	else{
		SET_BIT(RCC->AHB1ENR,Copy_u8PeripheralNo);}
}

void MRCC_vDisableClock(PeripheralEnable_t Copy_u8PeripheralNo){
	if(Copy_u8PeripheralNo >= 96){
		Copy_u8PeripheralNo -= 96;
		CLR_BIT(RCC->APB2ENR,Copy_u8PeripheralNo);
	}
	else if(Copy_u8PeripheralNo >= 64){
		Copy_u8PeripheralNo -= 64;
		CLR_BIT(RCC->APB1ENR,Copy_u8PeripheralNo);
	}
	else if(Copy_u8PeripheralNo >= 32){
		Copy_u8PeripheralNo -= 32;
		CLR_BIT(RCC->AHB2ENR,Copy_u8PeripheralNo);
	}
	else{
		CLR_BIT(RCC->AHB1ENR,Copy_u8PeripheralNo);};
}




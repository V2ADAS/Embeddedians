/***************************************************************************/
/* Author       : Omar Wael                                                */
/* Version      : V0.0.0                                                   */
/*  Date        : Oct 31, 2023                                             */
/*  Description : Driver Functions Implementation                          */
/***************************************************************************/

/***************************************************************************/
/*                        Standard Types LIB                               */
/***************************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/***************************************************************************/
/*                           MCAL Components                               */
/***************************************************************************/
#include"MNVIC_Config.h"
#include"MNVIC_Private.h"
#include"MNVIC_int.h"


static MNVIC_Priority_GP Global_u8GPMode  ;

/***************************************************************************/
/*                        Functions Implementations                        */
/***************************************************************************/
void MNVIC_vEnableInterrupt(Enum_MNVIC_NUM_t Copy_u8InterruptNo){

	/* note : writing 0 to any bit has no effect so we can u atomic instruction like BSSR */
	SET_BIT_FAST( NVIC->ISER[ (Copy_u8InterruptNo/32) ] , (Copy_u8InterruptNo % 32)  );
}

void MNVIC_vDisableInterrupt(Enum_MNVIC_NUM_t Copy_u8InterruptNo){

	/* note : writing 0 to any bit has no effect so we can u atomic instruction like BSSR */
		SET_BIT_FAST( NVIC->ICER[ (Copy_u8InterruptNo/32) ] , (Copy_u8InterruptNo % 32)  );

}

void MNVIC_vSetPendingFlag (Enum_MNVIC_NUM_t Copy_u8InterruptNo){

	/* note : writing 0 to any bit has no effect so we can u atomic instruction like BSSR */
	SET_BIT_FAST( NVIC->ISPR[ (Copy_u8InterruptNo/32) ] , (Copy_u8InterruptNo % 32)  );
}

void MNVIC_vClearPendingFlag (Enum_MNVIC_NUM_t Copy_u8InterruptNo){

			/* note : writing 0 to any bit has no effect so we can u atomic instruction like BSSR */
			SET_BIT_FAST( NVIC->ICPR[ (Copy_u8InterruptNo/32) ] , (Copy_u8InterruptNo % 32)  );
}

u8 MNVIC_u8ReadActiveFlag( Enum_MNVIC_NUM_t Copy_u8InterruptNo ){

	 u8 Local_u8Flag = 0 ;
	 Local_u8Flag = GET_BIT( NVIC->IABR[ (Copy_u8InterruptNo/32) ] , (Copy_u8InterruptNo % 32)  );
	 return Local_u8Flag;

}

void MNVIC_vInitGrouping(MNVIC_Priority_GP Copy_u8Grouping){

	SCB_AIRCR = (VECTKEY) | (Copy_u8Grouping<<8) ;
	Global_u8GPMode= Copy_u8Grouping;
}

void MNVIC_vSetIntPriority( Enum_MNVIC_NUM_t Copy_u8InterruptNo , MNVIC_GP_Options Copy_u8GP , MNVIC_SUB_Options Copy_u8SUB ){

	switch(Global_u8GPMode){
	case GP0SUB16 :
		NVIC -> IPR[Copy_u8InterruptNo] = (Copy_u8SUB<<4); break;
	case GP2SUB8 :
		NVIC -> IPR[Copy_u8InterruptNo] = ( (Copy_u8GP<<7)|(Copy_u8SUB<<4) ); break;
	case GP4SUB4 :
		NVIC -> IPR[Copy_u8InterruptNo] = ( (Copy_u8GP<<6)|(Copy_u8SUB<<4) ); break;
	case GP8SUB2 :
		NVIC -> IPR[Copy_u8InterruptNo] =  ( (Copy_u8GP<<5)|(Copy_u8SUB<<4) ); break;
	case GP16SUB0 :
		NVIC -> IPR[Copy_u8InterruptNo] =  (Copy_u8GP<<4) ; break;

	}

	/*u8 L_u8PrioValue = 0;
		switch(Global_u8GPMode){
			case GP16SUB0 : L_u8PrioValue =  Copy_u8GP; break;
			case GP8SUB2  : L_u8PrioValue = (Copy_u8GP << 1) | Copy_u8SUB; break;
			case GP4SUB4  : L_u8PrioValue = (Copy_u8GP << 2) | Copy_u8SUB; break;
			case GP2SUB8  : L_u8PrioValue = (Copy_u8GP << 3) | Copy_u8SUB; break;
			case GP0SUB16 : L_u8PrioValue =  Copy_u8SUB; break;
		}

		NVIC->IPR[Copy_u8InterruptNo] = L_u8PrioValue << 4;*/

}

void MNVIC_vTrigSoftwareInt( Enum_MNVIC_NUM_t Copy_u8InterruptNo ){

	NVIC -> STIR |= Copy_u8InterruptNo ;

}


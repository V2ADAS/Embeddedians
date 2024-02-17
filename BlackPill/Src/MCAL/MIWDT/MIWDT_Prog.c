/*
 * MIWDT.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Omar
 */
#include"../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include"MIWDT_Private.h"
#include"MIWDT_int.h"
#include"MIWDT_Config.h"

/*, it is mandatory to wait
until RVU bit is reset before changing the reload value and to wait until PVU bit is reset
before changing the prescaler value
*/



void MIWDG_vStart( u8 Local_u8TimeOut){



	/* start */
	IWDG->KR=IWDG_ENABLE_KEY;
	/* Enable accesssing */
	IWDG->KR=IWDG_REG_MODIFY_KEY;
	/* check if there is onging prescaler change */
	//while(GET_BIT(IWDG->SR,SR_PVU)==1);
	/* set prescaler */
	IWDG->PR=Local_u8TimeOut;

	/* check if there is onging relaod change */
	//while(GET_BIT(IWDG->SR,SR_RVU));
	/* set the reload value */
	IWDG->RLR=0xFFF;
	while(GET_BIT(IWDG->SR,SR_PVU)==1 || GET_BIT(IWDG->SR,SR_RVU)==1 );
	IWDG->KR =  IWDG_RELOAD_KEY;        // Reload the watchdog
	 //IWDG->KR = 0xCCCC;        // Start the watchdog

}

void MIWDG_vReload(){



	/* Reload Key */
	IWDG -> KR = IWDG_RELOAD_KEY;


}

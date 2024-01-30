/*
 * MIWDT_Private.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Omar
 */

#ifndef MCAL_MIWDT_MIWDT_PRIVATE_H_
#define MCAL_MIWDT_MIWDT_PRIVATE_H_


/********************* IWDG BASE ADDRESS ******************************/

#define IWDG_BASE_ADDRESS				(0x40003000)



/********************* IWDG REGISTERS *******************************/

typedef struct {

	u32 KR ;
	u32 PR ;
	u32 RLR ;
	u32 SR ;

} IWDG_Mem_Map_t;

/********************* POINTER TO REG ******************************/

#define IWDG					((volatile IWDG_Mem_Map_t*)(IWDG_BASE_ADDRESS))

/********************** IWDG KEYS **************************/

#define IWDG_ENABLE_KEY				(0x0000CCCC)
#define IWDG_RELOAD_KEY				(0x0000AAAA)
#define IWDG_REG_MODIFY_KEY			(0x00005555)

/*********************** SOME PIN NUMBERS ************************/

#define	SR_PVU						0
#define SR_RVU						1


#endif /* MCAL_MIWDT_MIWDT_PRIVATE_H_ */

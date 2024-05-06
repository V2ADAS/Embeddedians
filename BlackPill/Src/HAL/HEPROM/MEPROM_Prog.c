/*
 * MEPROM_Prog.c
 *
 *  Created on: May 4, 2024
 *      Author: Omar
 */
#include"../../MCAL/MI2C/MI2C_int.h"
#include"../../MCAL/MSTK/MSYSTICK_Int.h"
#include"MEPROM_Int.h"

void HEPROM_vWriteData(u16 Copy_u16PageNo ,u8 Copy_u8ByteNo,u8* PTR_TxData , u8 Copy_u8Datalen ){

	u16 Local_MemLoc = ( (Copy_u16PageNo<<6) | Copy_u8ByteNo );

	u8 MemLoc_HByte = (u8)(Local_MemLoc>>8);
	u8 MemLoc_LByte= (u8)(Local_MemLoc);

	u8 MemADDR[2]={MemLoc_HByte,MemLoc_LByte};

	MI2C_vMaster_MemWrite(EPROM_I2C,EPROM_ADDRESS, MemADDR,2,PTR_TxData, Copy_u8Datalen);

	MSYSTICK_vDelayms(5);
}

void HEPROM_vReadData(u16 Copy_u16PageNo ,u8 Copy_u8ByteNo,u8* PTR_RxData , u8 Copy_u8Datalen ){


	u16 Local_MemLoc = ( (Copy_u16PageNo<<6) | Copy_u8ByteNo );

	u8 MemLoc_HByte = (u8)(Local_MemLoc>>8);
	u8 MemLoc_LByte= (u8)(Local_MemLoc);

	u8 MemADDR[2]={MemLoc_HByte,MemLoc_LByte};

	MI2C_vMasterTx(EPROM_I2C, EPROM_ADDRESS, MemADDR,2, WithoutStop);

	MI2C_u8MasterRx(EPROM_I2C, EPROM_ADDRESS, PTR_RxData, Copy_u8Datalen);



}

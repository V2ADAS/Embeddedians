/*
 * MEPROM.h
 *
 *  Created on: May 4, 2024
 *      Author: Omar
 */

#ifndef HAL_HEPROM_MEPROM_INT_H_
#define HAL_HEPROM_MEPROM_INT_H_

#define EPROM_I2C			I2C1
#define EPROM_ADDRESS		0x50



void HEPROM_vWriteData(u16 Copy_u16PageNo ,u8 Copy_u8ByteNo,u8* PTR_TxData , u8 Copy_u8Datalen );

void HEPROM_vReadData(u16 Copy_u16PageNo ,u8 Copy_u8ByteNo,u8* PTR_RxData , u8 Copy_u8Datalen );


#endif /* HAL_HEPROM_MEPROM_INT_H_ */

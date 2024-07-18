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
#define PAGE_SIZE			64

#define CMP_EPROM_PAGE					0
#define CMP_EPROM_PAGE_OFFSET			0

/* personal parking want to store 500*3 = 1500 byte
 * each page has 64 byte
 * needed pages 1500/64 = 24 pages
 */
#define PARKING_EPROM_START_PAGE		1
#define PARKING_EPROM_END_PAGE		25

/* OUR EPROM is AT24c256 */
/* OUR EPROM is 512 page each is 64 byte */
/* Total 512*64 =  32,768 byte -----> 262,144 bits */

void HEPROM_vInit(u8 I2C_No);

void HEPROM_vWriteData (u16 page, u16 offset, u8 *data, u16 size);

void HEPROM_vReadData (u16 page, u16 offset, u8 *data, u16 size);


#endif /* HAL_HEPROM_MEPROM_INT_H_ */

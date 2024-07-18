/*
 * MEPROM_Prog.c
 *
 *  Created on: May 4, 2024
 *      Author: Omar
 */
#include"../../MCAL/MI2C/MI2C_int.h"
#include"../../MCAL/MSTK/MSYSTICK_Int.h"
#include"MEPROM_Int.h"
#include"math.h"


u16 bytestowrite(u16 size, u16 offset);

void HEPROM_vInit(u8 I2C_No){

	MI2C_vMasterInit(I2C_No);
}

//void HEPROM_vWriteData(u16 page, u16 offset, u8 *data, u16 size){
//
//	u16 Local_MemLoc = ( (page<<6) | offset );
//
//	u8 MemLoc_HByte = (u8)(Local_MemLoc>>8);
//	u8 MemLoc_LByte= (u8)(Local_MemLoc);
//
//	u8 MemADDR[2]={MemLoc_HByte,MemLoc_LByte};
//
//	MI2C_vMaster_MemWrite(EPROM_I2C,EPROM_ADDRESS, MemADDR,2,data, size);
//
//	MSYSTICK_vDelayms(5);
//}
//
//void HEPROM_vReadData (u16 page, u16 offset, u8 *data, u16 size){
//
//
//	u16 Local_MemLoc = ( (page<<6) | offset );
//
//	u8 MemLoc_HByte = (u8)(Local_MemLoc>>8);
//	u8 MemLoc_LByte= (u8)(Local_MemLoc);
//
//	u8 MemADDR[2]={MemLoc_HByte,MemLoc_LByte};
//
//	MI2C_vMasterTx(EPROM_I2C, EPROM_ADDRESS, MemADDR,2, WithoutStop);
//
//	MI2C_u8MasterRx(EPROM_I2C, EPROM_ADDRESS, data, size);
//
//
//
//}
//


void HEPROM_vWriteData(u16 page, u16 offset, u8 *data, u16 size) {
    u16 pos = 0;
    u16 currentOffset = offset;
    u16 remainingSize = size;
    u16 currentPage = page;

    while (remainingSize > 0) {
        // Calculate the maximum number of bytes that can be written to the current page
        u16 bytesToWrite = PAGE_SIZE - currentOffset;
        if (bytesToWrite > remainingSize) {
            bytesToWrite = remainingSize;
        }

        // Calculate the memory address for the current page and offset
        u16 localMemLoc = (currentPage << 6) | currentOffset;
        u8 memAddr[2] = { (u8)(localMemLoc >> 8), (u8)localMemLoc };

        // Write the data to the EEPROM
        MI2C_vMaster_MemWrite(EPROM_I2C, EPROM_ADDRESS, memAddr, 2, &data[pos], bytesToWrite);

        // Delay to allow for the write cycle to complete
        MSYSTICK_vDelayms(5);

        // Update the position, remaining size, and offset for the next iteration
        pos += bytesToWrite;
        remainingSize -= bytesToWrite;
        currentOffset = 0; // After the first page, the offset is always 0
        currentPage += 1;  // Move to the next page
    }
}


void HEPROM_vReadData(u16 page, u16 offset, u8 *data, u16 size) {
    u16 pos = 0;
    u16 currentOffset = offset;
    u16 remainingSize = size;
    u16 currentPage = page;

    while (remainingSize > 0) {
        // Calculate the maximum number of bytes that can be read from the current page
        u16 bytesToRead = PAGE_SIZE - currentOffset;
        if (bytesToRead > remainingSize) {
            bytesToRead = remainingSize;
        }

        // Calculate the memory address for the current page and offset
        u16 localMemLoc = (currentPage << 6) | currentOffset;
        u8 memAddr[2] = { (u8)(localMemLoc >> 8), (u8)localMemLoc };

        // Send the memory address to the EEPROM
        MI2C_vMasterTx(EPROM_I2C, EPROM_ADDRESS, memAddr, 2, WithoutStop);

        // Read the data from the EEPROM
        MI2C_u8MasterRx(EPROM_I2C, EPROM_ADDRESS, &data[pos], bytesToRead);

        // Update the position, remaining size, and offset for the next iteration
        pos += bytesToRead;
        remainingSize -= bytesToRead;
        currentOffset = 0; // After the first page, the offset is always 0
        currentPage += 1;  // Move to the next page
    }
}



u16 bytestowrite(u16 size, u16 offset) {
	//u16 page_size = 64;  // Assuming each page is 64 bytes
	u16 remaining_in_page = PAGE_SIZE - offset;
	return (size < remaining_in_page) ? size : remaining_in_page;
}





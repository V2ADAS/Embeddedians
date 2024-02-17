/*
 * MSPI_Confing.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Omar
 */

#ifndef MCAL_MSPI_MSPI_CONFIG_H_
#define MCAL_MSPI_MSPI_CONFIG_H_

/************** DATA FRAME ******************/

/*
 * OPTIONS ARE :
 * 1- FRAME_8_BIT
 * 2- FRAME_16_BIT
 * */
#define  DATA_FRAME				FRAME_8_BIT

/*************** BAUD RATE *************/
// IN MASTER ONLY

/*
 * OPTIONS ARE :
 * 000: fPCLK/2
 * 001: fPCLK/4
 * 010: fPCLK/8
 * 011: fPCLK/16
 * 100: fPCLK/32
 * 101: fPCLK/64
 * 110: fPCLK/128
 * 111: fPCLK/256
 * */

#define	BAUD_RATE			DIV8

#endif /* MCAL_MSPI_MSPI_CONFIG_H_ */

/***************************************************************************/
/* Author       : Omar Wael                                                */
/* Version      : V0.0.0                                                   */
/*  Date        :  1 Dec 2023                                              */
/*  Description : Driver Functions Implementation                          */
/*  Features    : Register Definition                                      */
/***************************************************************************/

/***************************************************************************/
/*                  File Guard Will Call On Time in .c File                */
/***************************************************************************/
#ifndef MCAL_MSPI_MSPI_PRIVATE_H_
#define MCAL_MSPI_MSPI_PRIVATE_H_

/***************************************************************************/
/*                      SPIs BASE ADDRESS                                  */
/***************************************************************************/
#define SPI1_BASE_ADD				(0x40013000)
#define SPI2_BASE_ADD				(0x40003800)
#define SPI3_BASE_ADD				(0x40003C00)
#define SPI4_BASE_ADD				(0x40013400)

/**************************************************************************/
/* Register Definition :-                                                 */
/* Features    : Private File Can`t Be Edit By User                       */
/* Description :-                                                         */
/*               - #define :      YES                                     */
/*               - union   :      NO                                      */
/*               - struct  :      YEs                                     */
/**************************************************************************/
/***************************************************************************/
/*                      SPI REGISTERS MAP                                  */
/***************************************************************************/
typedef struct{

	u32 CR1;
	u32 CR2 ;
	u32 SR ;
	u32 DR ;
	u32 CRCPR ;
	u32 RXCRCR ;
	u32 TXCRCR ;
	u32 I2SCFGR ;
	u32 I2SPR ;


} SPI_Mem_Map_t;

/***************************************************************************/
/*                      POINTER TO SPI REGISTER                            */
/***************************************************************************/
#define SPI1				((volatile SPI_Mem_Map_t*)(SPI1_BASE_ADD))
#define SPI2				((volatile SPI_Mem_Map_t*)(SPI2_BASE_ADD))
#define SPI3				((volatile SPI_Mem_Map_t*)(SPI3_BASE_ADD))
#define SPI4				((volatile SPI_Mem_Map_t*)(SPI4_BASE_ADD))

/***************************************************************************/
/*                       SOME BITS NUMBERS                                 */
/***************************************************************************/
#define CR1_BIDIMODE			15
#define CR1_DFF					11
#define CR1_SSM					9
#define CR1_SSI					8
#define CR1_SPE					6
#define CR1_BR					3
#define CR1_MSTR				2

#define CR2_TXEIE				7
#define CR2_RXNEIE				6
#define CR2_SSOE				2

#define SR_BSY					7
#define SR_TXE					1
#define SR_RXNE					0

#endif /* MCAL_MSPI_MSPI_PRIVATE_H_ */

/***************************************************************************/
/* Author       : Omar Wael                                                */
/* Version      : V0.0.0                                                   */
/*  Date        :  Jan 28, 2024                                             */
/*  Description : Driver Functions Implementation                          */
/*  Features    : Register Definition                                      */
/***************************************************************************/

/***************************************************************************/
/*                  File Guard Will Call On Time in .c File                */
/***************************************************************************/
#ifndef MCAL_MI2C_MI2C_PRIVATE_H_
#define MCAL_MI2C_MI2C_PRIVATE_H_

/***************************************************************************/
/*                      I2Cs BASE ADDRESS                                  */
/***************************************************************************/

#define I2C1_BASE_ADDR					(0x40005400)
#define I2C2_BASE_ADDR					(0x40005800)
#define I2C3_BASE_ADDR					(0x40005C00)


/**************************************************************************/
/* Register Definition :-                                                 */
/* Features    : Private File Can`t Be Edit By User                       */
/* Description :-                                                         */
/*               - #define :      YES                                     */
/*               - union   :      NO                                      */
/*               - struct  :      YEs                                     */
/**************************************************************************/
/***************************************************************************/
/*                      I2C REGISTERS MAP                                  */
/***************************************************************************/

typedef struct {

	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 OAR1;
	volatile u32 OAR2;
	volatile u32 DR;
	volatile u32 SR1;
	volatile u32 SR2;
	volatile u32 CCR;
	volatile u32 TRISE;
	volatile u32 FLTR;

}I2C_Mem_Map_t ;

/***************************************************************************/
/*                      POINTER TO I2C REGISTER                            */
/***************************************************************************/

#define I2C1_REG							((volatile I2C_Mem_Map_t*)(I2C1_BASE_ADDR))
#define I2C2_REG							((volatile I2C_Mem_Map_t*)(I2C2_BASE_ADDR))
#define I2C3_REG							((volatile I2C_Mem_Map_t*)(I2C3_BASE_ADDR))

/***************************************************************************/
/*                       SOME BITS POSITIONS                               */
/***************************************************************************/
#define CR1_PE								0
#define CR1_START							8
#define CR1_STOP							9
#define CR1_ACK								10
#define CR1_POS								11
#define CR1_SWRST							15

#define SR1_SB								0
#define SR1_ADDR							1
#define SR1_BTF								2
#define SR1_STOPF							4
#define SR1_RXNE							6
#define SR1_TXE								7
#define SR1_AF								10

#define CCR_FS								15



#endif /* MCAL_MI2C_MI2C_PRIVATE_H_ */

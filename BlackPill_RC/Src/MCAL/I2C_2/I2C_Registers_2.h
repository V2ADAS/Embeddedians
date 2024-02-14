/*
 * I2C_Registers.h
 *
 *  Created on: Jun 22, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef I2C_I2C_REGISTERS_H_
#define I2C_I2C_REGISTERS_H_

#define I2C1_BASE_ADDR 					0x40005400U
#define I2C2_BASE_ADDR 					0x40005800U
#define I2C3_BASE_ADDR 					0x40005C00U

typedef volatile struct{
	u32 CR1;
	u32 CR2;
	u32 OAR1;
	u32 OAR2;
	u32 DR;
	u32 SR1;
	u32 SR2;
	u32 CCR;
	u32 TRISE;
	u32 FLTR;
}st_I2C_RegDef_t;

#define I2C1	((st_I2C_RegDef_t *)I2C1_BASE_ADDR)
#define I2C2	((st_I2C_RegDef_t *)I2C2_BASE_ADDR)
#define I2C3	((st_I2C_RegDef_t *)I2C3_BASE_ADDR)

/* CR1 Register Bits */
#define I2C_PE			0
#define I2C_START		8
#define I2C_STOP		9
#define I2C_ACK			10

/* CR2 Registers Bits */
#define	I2C_ITERREN			8
#define	I2C_ITEVTEN			9
#define	I2C_ITBUFEN			10

/* SR1 Register Flags */
#define I2C_FLAG_SB			0
#define I2C_FLAG_ADDR		1
#define	I2C_FLAG_BTF		2
#define I2C_FLAG_STOPF		4
#define I2C_FLAG_RXNE		6
#define I2C_FLAG_TXE		7

// Error Flags
#define I2C_FLAG_BERR		8
#define I2C_FLAG_ARLO		9
#define I2C_FLAG_AF			10
#define I2C_FLAG_OVR		11
#define I2C_FLAG_PECERR		12
#define I2C_FLAG_TIMEOUT	14

#endif /* I2C_I2C_REGISTERS_H_ */

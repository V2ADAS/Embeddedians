
#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(var,Bit_No)   		(var |=(1<<Bit_No))
#define SET_BIT_FAST(REG,BITx)		REG =  (1<<BITx)
#define CLR_BIT(var,Bit_No)   		(var &=~(1<<Bit_No))
#define TOG_BIT(var,Bit_No)    		(var ^=(1<<Bit_No))
#define GET_BIT(var,Bit_No)   		((var>>Bit_No) & 0x01)

#define CLR_SET(Var,Bit_No)			(Var = ( (Var|=1<<Bit_No) & (Var &= ~( 1<< (Bit_No+1) ) ) ) )
#define SET_CLR(Var,Bit_No)			(Var = ( ( Var|=1<<(Bit_No+1) ) & ( Var&=~( 1<<(Bit_No) ) ) ) )
#define SET_2BITS(Var,Bit_No)		( Var|=3<<Bit_No )
#define CLR_2BITS(Var,Bit_No)		( Var &= ~(3<<Bit_No) )
#define GET_2BITS(var,Bit_No)   	((var>>Bit_No) & 0x03)

#define SET_VAL(Var,Bit_No,Val)		(Var |= (Val<<Bit_No))
#define PI 3.14159265359
#include <math.h>
#endif

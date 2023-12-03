/*
 * BIT_MATH.h
 *
 * Created: 8/20/2023 3:31:59 PM
 *  Author: Omar
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

# define  SET_BIT(REG,BITx)   				REG |= (1<<BITx)
# define  CLR_BIT(REG,BITx)   				REG &= ~(1<< BITx)
# define  TOG_BIT(REG,BITx)   				REG ^= (1<<BITx)
# define  GET_BIT(REG,BITx)			    ( (REG >> BITx) & 1 )
# define  SET_BIT_FAST(REG,BITx)			REG =  (1<<BITx)


#endif /* BIT_MATH_H_ */

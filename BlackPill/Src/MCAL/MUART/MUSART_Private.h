/***************************************************************************/
/* Author       : Mohamed Hawas                                             */
/* Version      : V0.0.0                                                   */
/*  Date        :  8 Jun 2023                                              */
/*  Description : Driver Functions Implementation                          */
/*  Features    : Register Definition                                      */
/***************************************************************************/

/***************************************************************************/
/*                  File Guard Will Call On Time in .c File                */
/***************************************************************************/
#ifndef MUSART_PRIVATE_H_
#define MUSART_PRIVATE_H_
/***************************************************************************/
/*                      Base Address Of USARTx Register                    */
/***************************************************************************/
#define USART1_BASE_ADDRESS      0x40011000UL
#define USART2_BASE_ADDRESS      0x40004400UL
#define USART6_BASE_ADDRESS      0x40011400UL


/**************************************************************************/
/* Register Definition :-                                                 */
/* Features    : Private File Can`t Be Edit By User                       */
/* Description :-                                                         */
/*               - #define :      YES                                     */
/*               - union   :      NO                                      */
/*               - struct  :      YED                                     */
/**************************************************************************/

typedef struct{
	u32 SBK     :1       ;
	u32 RWU     :1       ;
	u32 RE      :1       ;
	u32 TE      :1       ;
	u32 IDLEIE  :1       ;
	u32 RXNEIE  :1       ;
	u32 TCIE     :1       ;
	u32 TXEIE	:1		  ;
	u32 PEIE     :1       ;
	u32 PS       :1       ;
	u32 PCE      :1       ;
	u32 WAKE     :1       ;
	u32 M        :1       ;
	u32 UE       :1       ;
	u32 RESERVER1:1       ;
	u32 OVER8    :1       ;
	u32 RESERVER2:16      ;
}USART_CR1;

typedef struct{
	u32 ADD      :4  ;
	u32 RESERVER :1  ;
	u32 LBDL     :1  ;
	u32 LBDIR    :1  ;
	u32 RESERVER1:1  ;
	u32 LBCL     :1  ;
	u32 CPHA     :1  ;
	u32 CPOL     :1  ;
	u32 CLKEN    :1  ;
	u32 STOP     :2  ;
	u32 LINEN    :1  ;
	u32 RESERVER2:1  ;
	u32 RESERVER3:16 ;
}USART_CR2;

typedef struct{
	u32 EIE           ;
	u32 IREN          ;
	u32 IRLP          ;
	u32 HDSEL         ;
	u32 NACK          ;
	u32 SCEN          ;
	u32 DMAR          ;
	u32 RTSE          ;
	u32 CTSE          ;
	u32 CTSIE         ;
	u32 ONEBIT        ;
	u32 RESERVERD:19  ;
}USART_CR3;

typedef struct{
	u32 PSC:8        ;
	u32 GT :8        ;
	u32 RESERVERD:16 ;
}USART_GTPR;

typedef struct{
	u32 SR         ;
	u32 DR         ;
	u32 BRR        ;
	USART_CR1  CR1 ;
	USART_CR2  CR2 ;
	USART_CR3  CR3 ;
	USART_GTPR GTPR ;
}USART_t;

/***************************************************************************/
/*                     Struct Macro Base Address Of USARTx                 */
/***************************************************************************/
typedef volatile USART_t* USART_REG;

#define USART1_REG ((USART_REG)(USART1_BASE_ADDRESS))
#define USART2_REG ((USART_REG)(USART2_BASE_ADDRESS))
#define USART6_REG ((USART_REG)(USART6_BASE_ADDRESS))


#endif /* MUSART_PRIVATE_H_ */

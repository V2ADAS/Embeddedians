/*******************************************************************************************************/
/* Author            : Mohamed Hawas                                                                   */
/* Version           : V1.0.1                                                                          */
/* Date              : Feb 21, 2024                                                                    */
/* Description       : MFPU_Prog.c - main code file for Floating Point Unit (FPU) control              */
/* Module Features	 :																				   */
/* 		 01- MFPU_Enable																			   */
/* 		 02- MFPU_Disable  																			   */
/*******************************************************************************************************/
/* 											  Includes                                                 */
/*******************************************************************************************************/
#include "MFPU_Int.h"  // Include the header file for FPU control

/*******************************************************************************************************/
/* 											  Function Definitions                                     */
/*******************************************************************************************************/

/*-----------------------------------------------------------------------------------------------------*/
/* Description: Enables the Floating Point Unit (FPU)                                                  */
/*                                                                                                     */
/* Notes:                                                                                              */
/* - This function sets CP10 and CP11 bits in SCB_CPACR to enable full access to the FPU.              */
/* - It ensures that the FPU settings take effect using memory barrier instructions.                   */
/*-----------------------------------------------------------------------------------------------------*/
void MFPU_Enable(void) {
	// Set CP10 and CP11 Full Access
	SCB_CPACR |= (0xF << 20);

	// Ensure the FPU settings take effect
	//__asm volatile ("dsb");
	//__asm volatile ("isb");
}

/*-----------------------------------------------------------------------------------------------------*/
/* Description: Disables the Floating Point Unit (FPU)                                                 */
/*                                                                                                     */
/* Notes:                                                                                              */
/* - This function clears CP10 and CP11 bits in SCB_CPACR to disable full access to the FPU.           */
/* - It ensures that the FPU settings take effect using memory barrier instructions.                   */
/*-----------------------------------------------------------------------------------------------------*/
void MFPU_Disable(void) {
	// Clear CP10 and CP11 Full Access
	SCB_CPACR &= ~(0xF << 20);

	// Ensure the FPU settings take effect
	//__asm volatile ("dsb");
	//__asm volatile ("isb");
}

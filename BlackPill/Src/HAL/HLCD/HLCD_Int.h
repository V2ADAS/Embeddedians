/*******************************************************************************************************/
/* Author            : Amr ElMaghraby "ControllersTech"                                                */
/* Version           : V1.0.3                                                                          */
/* Data              : 17 Feb 2024                                                                     */
/* Description       : HLCD_Int.h --> implementations                                                  */
/* Module  Features  :                                                                                 */
/*      01- HLCD_vInit                                                                                 */
/*      02- LOC_HLCD_vSendCMD                                                                          */
/*      03- HLCD_vSendData                                                                             */
/*      04- HLCD_vSendString                                                                           */
/*      05- StringReverse                                                                              */
/*      06- IntToString                                                                                */
/*      07- HLCD_vSendNum                                                                              */
/*      08- HLCD_vPutCur                                                                               */
/*      09- HLCD_vClear                                                                                */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef HAL_HLCD_INT_H_
#define HAL_HLCD_INT_H_
/*******************************************************************************************************/
/*                                    Include files needed for HSERVO_Int.h 		                   */
/*******************************************************************************************************/
#include"../../LIB/STD_TYPES.h" //Standard Types Lib
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                          APIs                                                       */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                              		  	01-HLCD_vInit                                    		   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Initializes the LCD.
 *
 * @param void
 *
 * @return void
 *
 * @note This function initializes the LCD, preparing it for further operations.
 */
void HLCD_vInit(void);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                              		  	02-LOC_HLCD_vSendCMD                          			   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Sends a command to the LCD.
 *
 * @param Copy_u8CMD: An 8-bit unsigned integer representing the command to be sent to the LCD.
 *
 * @return None
 *
 * @note This function is used to send commands to the LCD module. The command parameter (Copy_u8CMD)
 *       specifies the action or configuration to be performed on the LCD, such as clearing the
 *       display, setting the cursor position, or other control commands.
 */
void LOC_HLCD_vSendCMD(u8 Copy_u8CMD);
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                              		  	 03-HLCD_vSendData                              		   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Sends data to the LCD.
 *
 * @param Copy_u8Data: An 8-bit unsigned integer representing the data to be sent to the LCD.
 *
 * @return None
 *
 * @note This function is used to send data to the LCD module. The data parameter (Copy_u8Data)
 *       represents the character or information to be displayed on the LCD screen.
 */
void HLCD_vSendData(u8 Copy_u8Data);
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                              		  	04-HLCD_vSendString                        	  			   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Sends a string to the LCD.
 *
 * @param Copy_u8StrPtr: A pointer to an unsigned 8-bit array (string) containing the data
 *                       to be sent to the LCD.
 *
 * @return void
 *
 * @note This function is used to send a string of characters to the LCD module. The parameter
 *       Copy_u8StrPtr is a pointer to the first character of the string, and the entire string
 *       will be displayed on the LCD screen.
 */
void HLCD_vSendString(u8 *Copy_u8StrPtr);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                     05- StringReverse                				               */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Reverses a string in-place.
 * @param str: The string to be reversed.
 * @param length: The length of the string.
 *
 * @note This function modifies the input string in-place by reversing its characters.
 */
static void StringReverse(u8 str[], s32 length);
/******************************************************************************************************/


/*******************************************************************************************************/
/*                                      06- IntToString                            			           */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Converts an integer to a string representation.
 * @param num: The integer to be converted.
 * @param str: The buffer to store the resulting string.
 * @param base: The numeric base for representing the integer (e.g., 10 for decimal, 16 for hexadecimal).
 * @return A pointer to the resulting string.
 *
 * @note This function handles the conversion of an integer to its string representation with the specified base.
 *       The resulting string is stored in the provided buffer. Ensure that the buffer is large enough to
 *       accommodate the string representation and the null terminator.
 */
static u8* IntToString(s32 num, u8 str[], s32 base);
/******************************************************************************************************/


/*******************************************************************************************************/
/*                                      07- HLCD_vSendNum                                              */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Sends a 32-bit unsigned integer to an LCD display for output.
 * @param Copy_u32Number: The 32-bit unsigned integer to be displayed on the LCD.
 *
 * @note This function is responsible for sending the specified 32-bit unsigned integer to the LCD display
 *       for output. The exact implementation details, such as formatting and communication with the LCD,
 *       should be provided in the function definition or documentation.
 */
void HLCD_vSendNum(u32 Copy_u32Number);
/******************************************************************************************************/

/*******************************************************************************************************/
/*                              		  	08-HLCD_vPutCur                                			   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Puts the cursor at the specified position on the LCD.
 *
 * @param Copy_u8Row: An 8-bit unsigned integer representing the row position (0 or 1).
 * @param Copy_u8Column: An 8-bit unsigned integer representing the column position (0 Up to 15).
 *
 * @return None
 *
 * @note This function is used to position the cursor on the LCD screen. The parameters Copy_u8Row
 *       and Copy_u8Column determine the row and column where the cursor will be placed, allowing
 *       subsequent data or commands to be displayed or executed at that specific location.
 */
void HLCD_vPutCur(u8 Copy_u8Row, u8 Copy_u8Column);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                              		  	09-HLCD_vClear                               			   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Clears the content on the LCD screen.
 *
 * @param None
 *
 * @return None
 *
 * @note This function is used to clear the entire content displayed on the LCD screen, returning
 *       the cursor to the home position (0, 0).
 */
void HLCD_vClear(void);
/*******************************************************************************************************/

#endif /* HAL_HLCD_INT_H_*/

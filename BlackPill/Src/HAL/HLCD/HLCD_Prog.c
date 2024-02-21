/*******************************************************************************************************/
/* Author            : Amr ElMaghraby "ControllersTech"                                                */
/* Version           : V1.0.3                                                                          */
/* Data              : 17 Feb 2024                                                                     */
/* Description       : HLCD_Prog.c --> implementations                                                 */
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
/*                                Header File Inclusions                                               */
/*-----------------------------------------------------------------------------------------------------*/
#include "../../LIB/STD_TYPES.h"         // Include the standard types header file.
#include "HLCD_Config.h"                 // Include the LCD configuration header file.
#include "HLCD_Int.h"                    // Include the LCD interface header file.
#include "../../MCAL/MI2C/MI2C_int.h"    // Include the I2C (Inter-Integrated Circuit) interface header file.
#include "../../MCAL/MSTK/MSYSTICK_Int.h"// Include the SysTick Timer interface header file.
#include "HLCD_Int.h"					 // Include the LCD Interface file.
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                LOC_HLCD_vSendCMD Function Implementation                            */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Sends a command to the LCD.
 *
 * @param Copy_u8CMD: An 8-bit unsigned integer representing the command to be sent to the LCD.
 *
 * @return None
 *
 * @note This function sends a command to the LCD module by breaking it into upper and lower nibbles.
 *       The command is transmitted in four steps to mimic the enable (EN) and register select (RS) signals
 *       for the LCD. The I2C (Inter-Integrated Circuit) interface is used for communication with the LCD.
 *       The LCD module is expected to be configured with a specific slave address (SLAVE_ADDRESS_LCD).
 *       The WithStop parameter indicates whether to generate a stop condition after the data transmission.
 */
void LOC_HLCD_vSendCMD(u8 Copy_u8CMD)
{
	u8 data_u, data_l;
	u8 data_t[4];

	// Extract upper and lower nibbles from the command
	data_u = (Copy_u8CMD & 0xF0);
	data_l = ((Copy_u8CMD << 4) & 0xF0);

	// Form the data array with enable (EN) and register select (RS) signals
	data_t[0] = data_u | 0x0C;  // EN=1, RS=0
	data_t[1] = data_u | 0x08;  // EN=0, RS=0
	data_t[2] = data_l | 0x0C;  // EN=1, RS=0
	data_t[3] = data_l | 0x08;  // EN=0, RS=0

	// Transmit the data array using the I2C interface
	MI2C_vMasterTx(I2C1, SLAVE_ADDRESS_LCD, data_t, 4, WithStop);
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                HLCD_vInit Function Implementation                                   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Initializes the LCD.
 *
 * @param None
 *
 * @return None
 *
 * @note This function performs the initialization sequence for the LCD, including 4-bit mode setup,
 *       display initialization, and configuring the display settings. Delay functions are used to
 *       ensure proper timing during the initialization process.
 */
void HLCD_vInit(void)
{
	// 4-bit initialization
	MSYSTICK_vDelayms(50);    // Wait for >40ms
	LOC_HLCD_vSendCMD(0x30);
	MSYSTICK_vDelayms(5);     // Wait for >4.1ms
	LOC_HLCD_vSendCMD(0x30);
	MSYSTICK_vDelayms(1);     // Wait for >100us
	LOC_HLCD_vSendCMD(0x30);
	MSYSTICK_vDelayms(10);
	LOC_HLCD_vSendCMD(0x20);  // 4-bit mode
	MSYSTICK_vDelayms(10);

	// Display initialization
	LOC_HLCD_vSendCMD(0x28);  // Function set --> DL=0 (4-bit mode), N=1 (2-line display), F=0 (5x8 characters)
	MSYSTICK_vDelayms(1);
	LOC_HLCD_vSendCMD(0x08);  // Display on/off control --> D=0, C=0, B=0 (display off)
	MSYSTICK_vDelayms(1);
	LOC_HLCD_vSendCMD(0x01);  // Clear display
	MSYSTICK_vDelayms(1);
	MSYSTICK_vDelayms(1);
	LOC_HLCD_vSendCMD(0x06);  // Entry mode set --> I/D=1 (increment cursor) & S=0 (no shift)
	MSYSTICK_vDelayms(1);
	LOC_HLCD_vSendCMD(0x0C);  // Display on/off control --> D=1, C and B=0 (Cursor and blink, last two bits)
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                HLCD_vSendData Function Implementation                                */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Sends data to the LCD.
 *
 * @param Copy_u8Data: An 8-bit unsigned integer representing the data to be sent to the LCD.
 *
 * @return None
 *
 * @note This function sends data to the LCD module by breaking it into upper and lower nibbles.
 *       The data is transmitted in four steps to mimic the enable (EN) and register select (RS) signals
 *       for the LCD. The I2C (Inter-Integrated Circuit) interface is used for communication with the LCD.
 *       The LCD module is expected to be configured with a specific slave address (SLAVE_ADDRESS_LCD).
 *       The WithStop parameter indicates whether to generate a stop condition after the data transmission.
 */
void HLCD_vSendData(u8 Copy_u8Data)
{
	u8 data_u, data_l;
	u8 data_t[4];

	// Extract upper and lower nibbles from the data
	data_u = (Copy_u8Data & 0xF0);
	data_l = ((Copy_u8Data << 4) & 0xF0);

	// Form the data array with enable (EN) and register select (RS) signals
	data_t[0] = data_u | 0x0D;  // EN=1, RS=1
	data_t[1] = data_u | 0x09;  // EN=0, RS=1
	data_t[2] = data_l | 0x0D;  // EN=1, RS=1
	data_t[3] = data_l | 0x09;  // EN=0, RS=1

	// Transmit the data array using the I2C interface
	MI2C_vMasterTx(I2C1, SLAVE_ADDRESS_LCD, data_t, 4, WithStop);
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                             HLCD_vSendString Function Implementation                               */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Sends a string to the LCD.
 *
 * @param Copy_u8StrPtr: A pointer to an unsigned 8-bit array (string) containing the data
 *                       to be sent to the LCD.
 *
 * @return None
 *
 * @note This function iterates through each character in the provided string (null-terminated)
 *       and sends it to the LCD using the HLCD_vSendData function. The process continues until
 *       the null character (end of the string) is encountered.
 */
void HLCD_vSendString(u8 *Copy_u8StrPtr)
{
	// Iterate through each character in the string until the null character is encountered
	while (*Copy_u8StrPtr)
	{
		// Send the current character to the LCD using HLCD_vSendData
		HLCD_vSendData(*Copy_u8StrPtr++);
	}
}

/*******************************************************************************************************/
/*                                      StringReverse                				                   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Reverses a string in-place.
 * @param str: The string to be reversed.
 * @param length: The length of the string.
 *
 * @note This function modifies the input string in-place by reversing its characters.
 */
static void StringReverse(u8 str[], s32 length) {
    int start = 0;
    int end = length - 1;

    // Swap characters from the start and end of the string until reaching the middle
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
/******************************************************************************************************/


/*******************************************************************************************************/
/*                                       IntToString                            			           */
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
static u8* IntToString(s32 num, u8 str[], s32 base) {
    s32 i = 0;

    // Handle 0 explicitly, as it will result in an empty string
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Process individual digits
    while (num != 0) {
        s32 rem = num % base;
        str[i++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'a');
        num = num / base;
    }

    str[i] = '\0'; // Null-terminate the string

    // Reverse the string
    StringReverse(str, i);

    return str;
}
/******************************************************************************************************/


void HLCD_vSendNum(u32 Copy_u32Number)
{
	u8 Local_u8Str[10];
	//itoa is a function to convert number to a string
	//first par: represent number it is
	//sec par: represent buffer to store string convention
	//third par: represent number base 10==>Decimal   2==>Binary

	//OR:
	//  sprintf(str, "%d", number); // Convert integer to string
	IntToString(Copy_u32Number, Local_u8Str,10);
	HLCD_vSendString(Local_u8Str);

}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                              HLCD_vPutCur Function Implementation                                   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Positions the cursor at the specified row and column on the LCD.
 *
 * @param Copy_u8Row: An 8-bit unsigned integer representing the row position (0 or 1).
 * @param Copy_u8Column: An 8-bit unsigned integer representing the column position (0-15).
 *
 * @return None
 *
 * @note This function calculates the cursor position based on the specified row and column.
 *       The row parameter determines whether the cursor should be placed at the first or second line
 *       of the LCD. The column parameter is used to set the cursor position within the specified row.
 *       The resulting position is then sent to the LCD using the LOC_HLCD_vSendCMD function.
 */
void HLCD_vPutCur(u8 Copy_u8Row, u8 Copy_u8Column)
{
	// Adjust the column parameter based on the selected row
	switch (Copy_u8Row)
	{
	case 0:
		Copy_u8Column |= 0x80;  // Set the cursor position for the first row
		break;
	case 1:
		Copy_u8Column |= 0xC0;  // Set the cursor position for the second row
		break;
	}

	// Send the calculated cursor position to the LCD using LOC_HLCD_vSendCMD
	LOC_HLCD_vSendCMD(Copy_u8Column);
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                 HLCD_vClear Function Implementation                                */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @brief Clears the content on the LCD screen.
 *
 * @param None
 *
 * @return None
 *
 * @note This function clears the content displayed on the LCD screen by setting the cursor to the
 *       beginning of the first row (0x80) and filling the entire screen with space characters (' ').
 *       The total length of the LCD is determined by the TOT_LCD_LENGTH constant. The HLCD_vSendData
 *       function is used to send space characters and overwrite the existing content on the LCD.
 */
void HLCD_vClear(void)
{
	// Set the cursor to the beginning of the first row
	LOC_HLCD_vSendCMD(0x80);
	// Assign empty char to an variable to make a very small delay to send
	u8 x = ' ';
	// Fill the entire screen with space characters (' ')
	for (int i = 0; i < TOT_LCD_LENGTH; i++)
	{
		// Send a space character to overwrite the existing content on the LCD
		//	NOTE: using higher clock freq will require adding some delay here probably.
		HLCD_vSendData(x);
	}
	HLCD_vPutCur(0, 0);
}
/*******************************************************************************************************/

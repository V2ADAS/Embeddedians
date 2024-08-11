/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                  */
/* Version           : V1.0.1                                                                          */
/* Date              : 20 July 2024                                                                    */
/* Description       : App_Connection.h --> Provides declarations for application connection functions */
/*                      and data structures.                                                           */
/* Module  Features  :                                                                                 */
/*      01- App_Start_Connect: Initializes UART connection.                                            */
/*      02- App_Tx_Data: Transmits application data over UART.                                         */
/*      03- App_UpdateUltrasonicData: Updates ultrasonic sensor data.                                  */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   Include Guard                                                     */
/* Ensures the header file is included only once in the compilation process.                           */
/*******************************************************************************************************/
#ifndef APP_INC_APP_CONNECTION_H_
#define APP_INC_APP_CONNECTION_H_

/*******************************************************************************************************/
/*                                    Include Files                                                    */
/* Includes standard types, bit manipulation functions, and UART interface header.                     */
/*******************************************************************************************************/
#include "../../LIB/STD_TYPES.h" // Standard Types Library
#include "../../LIB/BIT_MATH.h"  // Bit Manipulation Library
#include "../../MCAL/MUART/MUSART_Interface.h" // UART Interface for communication

/*******************************************************************************************************/
/*                                        Data Structure Definition                                    */
/* Defines the structure used to store sensor data and other related information.                      */
/*******************************************************************************************************/
typedef struct {
    u8 start;                       // Flag to indicate the start of communication or initialization.

    // Ultrasonic sensor data
    u16 US_RightForward;           // Distance measurement from the right forward ultrasonic sensor.
    u16 US_CenterForward;           // Distance measurement from the center forward ultrasonic sensor.
    u16 US_LeftForward;            // Distance measurement from the left forward ultrasonic sensor.
    u16 US_RightCenter;            // Distance measurement from the right center ultrasonic sensor.
    u16 US_LeftCenter;             // Distance measurement from the left center ultrasonic sensor.
    u16 US_RightBackward;          // Distance measurement from the right backward ultrasonic sensor.
    u16 US_CenterBackward;         // Distance measurement from the center backward ultrasonic sensor.
    u16 US_LeftBackward;           // Distance measurement from the left backward ultrasonic sensor.

    u32 TotalMovedDistance;        // Total distance moved, accumulated from various sensors or calculations.

    s16 Yaw_Compass;               // Yaw measurement from the compass sensor.
    s16 Yaw_MPU;                   // Yaw measurement from the MPU (Motion Processing Unit) sensor.

    // Additional variables for application-specific use
    f32 var1;                      // Placeholder for additional data (e.g., calibration or adjustment values).
    f32 var2;                      // Placeholder for additional data.
    f32 var3;                      // Placeholder for additional data.
    f32 var4;                      // Placeholder for additional data.
    f32 var5;                      // Placeholder for additional data.
} Data_ST;

/*******************************************************************************************************/
/*                                        External Variables                                          */
/* Declare the external variable of type Data_ST to be used across different files.                    */
/*******************************************************************************************************/
extern Data_ST App_Tx;

/*******************************************************************************************************/
/*                                          API Declarations                                          */
/* Function prototypes for the application connection module.                                         */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      01- App_Start_Connect                                          */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Initializes the connection via the specified UART channel.
 *              This function sets up the UART communication for transmitting and receiving data.
 * @param Copy_u8UART_Num: The UART channel number to be used for communication.
 *                          Expected to be a valid UART channel number as per the MCU specifications.
 * @return: void
 * @note Ensure the UART module is correctly configured and initialized before calling this function.
 */
void App_Start_Connect(u8 Copy_u8UART_Num);
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      02- App_Tx_Data                                                */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Transmits the application data over the initialized UART channel.
 *              This function sends the data contained in the App_Tx structure to the connected device.
 * @return: void
 * @note Ensure that App_Start_Connect has been called successfully before calling this function.
 */
void App_Tx_Data(void);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      03- App_UpdateUltrasonicData                                   */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description Updates the ultrasonic sensor data in the Data_ST structure.
 *              This function reads the current sensor values and updates the corresponding fields
 *              in the App_Tx structure.
 * @return: void
 * @note Ensure that the ultrasonic sensors are properly initialized and functioning before calling
 *       this function.
 */
void App_UpdateUltrasonicData(void);
/*******************************************************************************************************/


/* 		End of Include Guard        */

#endif /* APP_INC_APP_CONNECTION_H_ */

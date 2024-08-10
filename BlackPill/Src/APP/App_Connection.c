/*******************************************************************************************************/
/* Author            : Amr Elmaghraby                                                                  */
/* Version           : V1.0.1                                                                          */
/* Date              : 20 July 2024                                                                    */
/* Description       : App_Connection.c --> implementations                                            */
/* Module  Features  :                                                                                 */
/*      01- App_Start_Connect                                                                          */
/*      02- App_Tx_Data                                                                                */
/*      03- App_UpdateUltrasonicData                                                                   */
/*      Local functions:																			   */
/*      01- RX_Callback                                                                                */
/*******************************************************************************************************/

#include "Inc/App_Connection.h"
#include "Inc/Car_Control.h"
#include "Inc/Parking_Scanner.h"
#include "Inc/MoveBack.h"
#include "Inc/Personal_Parking.h"
#include "../HAL/HMOTOR/HMOTOR.h"
#include "../HAL/HSERVO/HSERVO_Int.h"
#include "../HAL/HULTRA_SONIC/HULTRA_SONIC_Int.h"


// Global variable to store the UART number used
u8 Gl_UART_Used = 0;

// Define a structure for transmitting application data
Data_ST App_Tx = {'*', 50, 199, 0, 1, 10, 20, 30, 40, 50, -991, -70, 80.99, 90, 11.11, 80.8, 999.9};

// Pointer to the application data structure
u8 *ptr = (u8*)&App_Tx;

// Size of the application data structure
u8 size = sizeof(App_Tx);

/**
 * @brief Callback function to handle received UART data.
 *
 * This function is called when data is received via UART via interrupt.
 */
void RX_Callback(void) {
	// Receive data from UART
	u8 data_rx = MUART_Receive_Data(UART1);
	s8 Steering_tx = 0;

	switch(data_rx) {
	case 'p':
		Scanning_vStart(PaB, Scan_Both,TIMER1,CH1);
		HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 80);
		break;
	case 'f':
		// Move forward
		HAL_MOTOR_MOVE(DC_MOTOR, FORWARD, 80);
		break;
	case 'b':
		// Move backward
		HAL_MOTOR_MOVE(DC_MOTOR, BACKWARD, 80);
		break;
	case 's':
		// Stop motor
		HAL_MOTOR_ForceStop(DC_MOTOR);
		break;
	case 'd':
		static u8 loc_flag=0;
		if(loc_flag==0){
//			App_Tx.var5 =1;
//			App_Tx_Data();
			MVBack_Start();
			loc_flag=1;
		}
		else if(loc_flag==1){
//			App_Tx.var5 =0;
//			App_Tx_Data();
			MVBack_Stop();
			loc_flag=0;
		}
		break;
	case 'r':
		// Handle personal parking states
		static u8 loc_flag = 0;
		if (loc_flag == 0) {
			PersonalParking_StartSaving();
			loc_flag = 1;
		} else if (loc_flag == 1) {
			PersonalParking_EndSaving();
			loc_flag = 0;
		}
		break;
	case 'a':
		// Apply personal parking
		PersonalParking_Apply();
		break;
	default:
		// Adjust servo angle
		Steering_tx = data_rx - 41;
		HSERVO_vServoDeg(SERVO1, Steering_tx);
		break;
	}

}

/**
 * @brief Initializes the connection using the specified UART number.
 *
 * This function initializes the UART communication by setting up the UART peripheral,
 * setting the callback function for received data, and enabling the UART.
 *
 * @param Copy_u8UART_Num: UART number to be used for the connection.
 */
void App_Start_Connect(u8 Copy_u8UART_Num) {
	// Store the UART number
	Gl_UART_Used = Copy_u8UART_Num;

	// Initialize the UART peripheral
	MUART_Init(Copy_u8UART_Num);

	// Set the callback function for received data
	MUART_vSetRxCallBackFunc(Copy_u8UART_Num, RX_Callback);

	// Enable the UART
	MUART_Enable(Copy_u8UART_Num);
}

/**
 * @brief Transmits application data via UART.
 *
 * This function sends the application data structure via UART to the connected device.
 */
void App_Tx_Data(void) {
	// Transmit the application data structure
	MUART_Send_Data(Gl_UART_Used, ptr, size);
}

/**
 * @brief Updates the ultrasonic sensor data in the application data structure.
 *
 * This function updates the ultrasonic sensor readings in the application data structure.
 * The data includes distance measurements from various directions around the vehicle.
 */
void App_UpdateUltrasonicData(void) {
	// Update right forward ultrasonic data
	App_Tx.US_RightForward = UltraSonics_ST.RF;

	// Update center forward ultrasonic data
	App_Tx.US_CenterForward = UltraSonics_ST.CF;

	// Update left forward ultrasonic data
	App_Tx.US_LeftForward = UltraSonics_ST.LF;

	// Update right center ultrasonic data
	App_Tx.US_RightCenter = UltraSonics_ST.RC;

	// Update left center ultrasonic data
	App_Tx.US_LeftCenter = UltraSonics_ST.LC;

	// Update right backward ultrasonic data
	App_Tx.US_RightBackward = UltraSonics_ST.RB;

	// Update center backward ultrasonic data
	App_Tx.US_CenterBackward = UltraSonics_ST.CB;

	// Update left backward ultrasonic data
	App_Tx.US_LeftBackward = UltraSonics_ST.LB;
}

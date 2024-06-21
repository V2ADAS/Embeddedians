/*******************************************************************************************************/
/* Author            : Amr ElMaghraby                                                            	   */
/* Version           : V1.1.0                                                                          */
/* Data              : 28 Jan 2024                                                                     */
/* Description       : MTimer_Prog.c --> implementations                                               */
/* Module  Features  :                                                                                 */
/*      01- MTIMER_vStartTime                                                                          */
/*      02- MTIMER_vCntTimer                                                                           */
/*      03- MTIMER_vDelayms                                                                            */
/*      04- MTIMER_f32GetElapsedTime                                                                   */
/*      05- MTIMER_u32GetElapsedTicks																   */
/*      06- MTIMER_vPeriodicMS                                                                         */
/*		07- MTIMER_EXTCNTClock																		   */
/*      08- MTIMER_vClearCNT																		   */
/*      09- MTIMER_vPWM                                                                                */
/*      10- MTIMER_vICU                                                                                */
/*      11- MTIMER_GET_ICU                                                                             */
/*      12- MTIMER_CallBack                                                                            */
/*      Local functions:																			   */
/* 		01-  LOC_GET_TIMER                                                                             */
/*      02-  LOC_TIMER_ICU                                                                             */
/*******************************************************************************************************/
#include"MTIMER_Private.h"
#include"MTIMER_Int.h"
#include"MTIMER_Config.h"

#include"../MGPIO/MGPIO_int.h"

//Global Pointer to be used for TIMER IRQ Call Back Functions
static void (*GLOBAL_Ptr[8])(void)={STD_NULL};

/*******************************************************************************************************/
/*                                		 LOC_TIMER_ICU Function                                    */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description 	Configures the specified TIMER for Input Capture Unit (ICU) functionality
 * 					 on the specified channel, Used internally to calculate Pulse width get by ICU.
 *
 * @param 			Copy_u8TimerNum: The TIMER number to be configured.
 *
 * @param 			Copy_u8ChannelNum: The TIMER channel to be configured for Input Capture Unit (ICU).
 * @return 			void
 */
static void LOC_TIMER_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8ChannelNum);
/*******************************************************************************************************/

//Global Array to Store each CH Captured Pulse width value
u32 Time[29]={0};
f32 timee=0;

/*******************************************************************************************************/
/*                                      LOC_GET_TIMER Function                                         */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @Description	 Local function retrieves the memory-mapped structure for the specified TIMER based
 * 				  on its number.
 * @param 		 Copy_u8TimerNum: The TIMER number to retrieve the memory-mapped structure.
 *                          Expected to be a value from {1 to 8, 9 to 11} representing different Timers.
 * @return 		 TIM2_5_MemMap_t*: Pointer to the memory-mapped structure of the specified TIMER.
 * @note 		 using TIM2_5_MemMap_t struct to be used for all timers
 */
static TIM2_5_MemMap_t* LOC_GET_TIMER(u32 Copy_u8TimerNum) {
	// Calculate the base address of the specified TIMER using its offset.
	TIM2_5_MemMap_t* TIMx = (TIM2_5_MemMap_t*)((u32)TIM2 + TIMERS_OFFSET[Copy_u8TimerNum - 1]);

	// Return the pointer to the memory-mapped structure of the specified TIMER.
	return TIMx;
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @Description Starts or enables the specified TIMER for time keeping or other time-dependent operations.
 * @param Copy_u8TimerNum: The TIMER number to be started.
 *                          Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                              TIMER5, TIMER9, TIMER10, TIMER11 }
 * @return void
 */
void MTIMER_vStartTime(Enum_TIMER_NUM Copy_u8TimerNum) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	// Reset Control Register 1 Value
	TIMx->CR1 = 0;

	// Set the prescaler value to achieve a 1ms time base
	TIMx->PSC = SYS_CLOCK * 1000;

	// Set the auto-reload value to MAX Value
	TIMx->ARR = 0xFFFFFFFF;

	// Set the Counter Enable bit to start the timer
	SET_BIT(TIMx->CR1, CEN);

	// Ensure Starting CNT from 0 as of some problems with TIMER2 and TIMER 5 if "ARR >0x0020000"
	TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief Controls the continuation or stopping of the specified TIMER.
 * @param Copy_u8TimerNum: The TIMER number to control.
 *                          Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                              TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u8TimerCont: The desired action for the TIMER.
 *                          Expected to be Enum_Timer_Cont ==> { StopTimer, ContinueTimer }
 * @return void
 */
void MTIMER_vCntTimer(Enum_TIMER_NUM Copy_u8TimerNum, Enum_Timer_Cont Copy_u8TimerCont) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	// Check the desired action for the TIMER
	switch (Copy_u8TimerCont) {
	case StopTimer:
		// Clear the Counter Enable bit to stop the timer
		CLR_BIT(TIMx->CR1, CEN);
		break;
	case ContinueTimer:
		// Set the Counter Enable bit to continue or start the timer
		SET_BIT(TIMx->CR1, CEN);
		break;
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief Delays the program execution for the specified duration in milliseconds using the specified TIMER.
 * @param Copy_u8TimerNum: The TIMER number to use for the delay.
 *                          Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                              TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u32Delayms: The delay duration in milliseconds.
 * @return void
 */
void MTIMER_vDelayms(Enum_TIMER_NUM	Copy_u8TimerNum,u32 Copy_u32Delayms){
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	static u8 first_delay_error[8] = {1,1,1,1,1,1,1,1};
	// Reset Control Register 1 Value
	TIMx->CR1 = 0;

	// Set the prescaler value to achieve a 1ms time base
	TIMx->PSC = SYS_CLOCK * 1000;

	// Set the auto-reload value to MAX Value
	TIMx->ARR = Copy_u32Delayms;

	// Set the Counter Enable bit to start the timer
	SET_BIT(TIMx->CR1, CEN);

	// Ensure Starting CNT from 0 as of some problems with TIMER2 and TIMER 5 if "ARR >0x0020000"
	TIMx->CNT = 0xFFFFFFFF;

	// Clear the update interrupt flag of TIMx
	CLR_BIT(TIMx->SR,0);

	// Wait for Update flag to be zero
	while (!GET_BIT(TIMx->SR, 0));

	// TODO: Solve error of first Delay not working
	if(first_delay_error[Copy_u8TimerNum-1] == 1){
		// Clear the update interrupt flag of TIMx
		CLR_BIT(TIMx->SR,0);
		// Wait for the Timer to reach zero (polling)
		while ( !GET_BIT(TIMx->SR, 0) );
		//set first delay error to zero
		first_delay_error[Copy_u8TimerNum-1] = 0;
	}

	// Clear the update interrupt flag of TIM1
	CLR_BIT(TIMx->SR,0);
	// Clear Enable bit to disable the timer
	CLR_BIT(TIMx->CR1, CEN);

}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @Description Retrieves the elapsed time on the specified TIMER in either seconds or milliseconds.
 * @param Copy_u8TimerNum: The TIMER number to query.
 *                          Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                              TIMER5, TIMER9, TIMER10, TIMER11 }
 * @param Copy_u8TimerUnit: The desired time unit for the elapsed time.
 *                          Expected to be Enum_TIMER_Unit ==> { milli, sec }
 * @return f32: The elapsed time in either seconds or milliseconds.
 */
f32 MTIMER_f32GetElapsedTime(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_Unit Copy_u8TimerUnit) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	switch (Copy_u8TimerUnit) {
	case milli:
		return ((f32)(TIMx->CNT));
		break;
	case sec:
		return (((f32)(TIMx->CNT)) / 1000.0);
		break;
	default:
		return 0;
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief Retrieves the elapsed ticks on the specified TIMER.
 *
 * @param Copy_u8TimerNum: The TIMER number to query.
 *                         Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                             TIMER5, TIMER9, TIMER10, TIMER11 }
 * @return u32: The elapsed ticks on the specified TIMER.
 */
u32 MTIMER_u32GetElapsedTicks(Enum_TIMER_NUM Copy_u8TimerNum) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	// Return the raw count of the timer, representing elapsed ticks
	return (TIMx->CNT);
}
/*******************************************************************************************************/



/*******************************************************************************************************/
/**
 * @brief   Configure the specified timer for a periodic delay in milliseconds.
 *
 * @param   Copy_u8TimerNum: The timer number to be configured.
 * @param   Copy_u32Delay: The desired delay in milliseconds.
 *
 * @note    This function configures the timer with the specified number for a periodic delay.
 *          The timer is set up to generate an interrupt after the specified delay.
 *          for TIMERS 1,3,4,9,10,11 MAXIMUM Allowable Delay is 65.536 sec
 *          for TIMERS  2,5 MAXIMUM Allowable Delay is 49.71 DAY!!
 *          [This values calculated as Tick time is 1ms "Clock = 16MHZ , prescaler = 16000" ]
 *          for same clock with max prescaler value 2^16:
 *          for TIMERS 1,3,4,9,10,11 MAXIMUM Allowable Delay is 268.435 sec.
 *          for TIMERS 2,5 MAXIMUM Allowable Delay is 203.61 DAY!!!!!.
 */
void MTIMER_vPeriodicMS(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delay) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	// Reset Control Register 1 Value
	TIMx->CR1 = 0;

	// Set the prescaler value to achieve a 1ms time base
	TIMx->PSC = SYS_CLOCK * 1000;

	// Set the auto-reload value to achieve the desired delay
	TIMx->ARR = Copy_u32Delay - 1;

	// Set the Update Interrupt Enable bit to enable the interrupt
	SET_BIT(TIMx->DIER, UIE);

	// Set the Counter Enable bit to start the timer
	SET_BIT(TIMx->CR1, CEN);

	// Ensure Starting CNT from 0 as of some problems with TIMER2 and TIMER 5 if "ARR >0x0020000"
	TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief Configures the specified TIMER channel to count external events on the rising edge of
 * 				 the input signal.
 * @param Copy_u8TimerNum: The TIMER number to be configured.
 *                         Expected to be Enum_TIMER_NUM ==> { TIMER1, TIMER2, TIMER3, TIMER4,
 *                           TIMER5, TIMER9 }.
 * @param Copy_u8Channel: The channel on which external events will be counted.
 *                        Expected to be Enum_TIMER_CHs ==> { CH1, CH2 }.
 * @param Copy_u32Max_Value: The maximum value for the counter. When the counter reaches this value,
 * 								 it will reset.
 * @return void
 * VERY IMPORTANT NOTE: NO EXTERNAL CLOCK MODE FOR CH3 or CH4 for Any TIMER
 * 			ALSO NO EXTERNAL MODE AT ALL FOR TIMER 10 or TIMER 11
 */
void MTIMER_vEXTCNTClock(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel,u32	Copy_u32Max_Value){
	// Configure GPIO pins and alternative functions based on the selected timer and channel
	MGPIO_vSetPinMode(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			ALTFUNC
	);
	MGPIO_vSetAlternativeFunction(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			TIMER_AF[Copy_u8TimerNum-1]
	);
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);

	//Clear CNT before starting
	//TIMx->CNT = 0x00;
	//1. Configure channel 2 to detect rising edges on the TI2 input by writing CC2S = ‘01’ in
	//the TIMx_CCMR1 register.
	SET_BIT( TIMx->CCMR[0] , ( CCxS0+(((Copy_u8Channel-1)%2)*8)) );
	CLR_BIT( TIMx->CCMR[0] , ( CCxS1+(((Copy_u8Channel-1)%2)*8)) );
	//2. Configure the input filter duration by writing the IC2F[3:0] bits in the TIMx_CCMR1
	//register (if no filter is needed, keep IC2F=0000).
	//FILTERING
	SET_BIT(TIMx->CCMR[0],( ICxF0 + ( ((Copy_u8Channel-1)%2)*8)));
	SET_BIT(TIMx->CCMR[0],( ICxF1 + ( ((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIMx->CCMR[0],( ICxF2 + ( ((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIMx->CCMR[0],( ICxF3 + ( ((Copy_u8Channel-1)%2)*8)));
	//3. Select rising edge polarity by writing CC2P=0 and CC2NP=0 in the TIMx_CCER register.
	CLR_BIT(TIMx->CCER, (CCxP + (Copy_u8Channel-1)*4) );
	//4. Configure the timer in external clock mode 1 by writing SMS=111 in the TIMx_SMCR register.
	SET_VAL(TIMx->SMCR,SMS0,0b111);
	//5. Select TI2 as the trigger input source by writing TS=110 in the TIMx_SMCR register.
	u8 x =(0b100+Copy_u8Channel);
	SET_VAL(TIMx->SMCR,TS0,x);

	TIMx->ARR = Copy_u32Max_Value;
	// Set the Update Interrupt Enable bit to enable the interrupt
	SET_BIT(TIMx->DIER, UIE);

	//6. Enable the counter by writing CEN=1 in the TIMx_CR1 register.
	SET_BIT( TIMx->CR1 , CEN );// Enable timer
	//TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
// Function to clear the counter (CNT) of the specified timer
void MTIMER_vClearCNT(Enum_TIMER_NUM Copy_u8TimerNum) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);
	// Clear the counter value (CNT) by setting it to 0x00
	TIMx->CNT = 0x00;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
void MTIMER_vPWM(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec){
	// Configure GPIO pins and alternative functions based on the selected timer and channel
	MGPIO_vSetPinMode(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			ALTFUNC
	);
	MGPIO_vSetAlternativeFunction(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			TIMER_AF[Copy_u8TimerNum-1]
	);
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);
	SET_BIT( TIMx->CR1 , ARPE );    // Enable auto-reload preload
	CLR_BIT( TIMx->CR1 , DIR); 	// UP COUNT
	CLR_BIT( TIMx->CR1 , CMS0); 	// 00: Edge-aligned mode. The counter counts up
	CLR_BIT( TIMx->CR1 , CMS1);    // 		or down depending on the direction bit(DIR)

	//01: CCx channel is configured as output  "PWM"
	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS0+(((Copy_u8Channel-1)%2)*8)) );
	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS1+(((Copy_u8Channel-1)%2)*8)) );

	// set prescaler
	/* TIME Calculation of Total Period:
	 * Total_Period = (PSC / (SYS_CLOCK * 10^6)) * ARR
	 */
	TIMx->PSC = SYS_CLOCK*10-1;
	TIMx->ARR = ( Copy_u16TotalTime_uSec*100 )/1000; // Timer auto-reload to max <<Periodic time>>
	TIMx->CCR[Copy_u8Channel-1] = ( Copy_u16PositiveDutyCycle_uSec*100 )/1000; // << DUTY CYCLE >>
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxPE+(((Copy_u8Channel-1)%2)*8)) );  //1: Preload register on TIMx_CCRx enabled

	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxM0+(((Copy_u8Channel-1)%2)*8)) );// PWM Mode1 (high then low)
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxM1+(((Copy_u8Channel-1)%2)*8)) );
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxM2+(((Copy_u8Channel-1)%2)*8)) );

	CLR_BIT( TIMx->CCER ,( CCxP + (Copy_u8Channel-1)*4) ); //Polarity 0: active high
	//SET_BIT(TIMx->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
	SET_BIT( TIMx->CCER , ( CCxE+(Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
	SET_BIT( TIMx->RESERVED2 , 15 );// MOE 1: OC and OCN outputs are enabled

	SET_BIT( TIMx->CR1 , CEN );// Enable timer
	TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/


/*******************************************************************************************************/
void MTIMER_vICU(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8Channel){
	// Configure GPIO pins and alternative functions based on the selected timer and channel
	MGPIO_vSetPinMode(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			ALTFUNC
	);
	MGPIO_vSetAlternativeFunction(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			TIMER_AF[Copy_u8TimerNum-1]
	);
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER(Copy_u8TimerNum);
	SET_BIT( TIMx->CR1 , ARPE );    // Enable auto-reload preload
	CLR_BIT( TIMx->CR1 , DIR ); 	// UP COUNT
	CLR_BIT( TIMx->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
	CLR_BIT( TIMx->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

	//01: CCx channel is configured as ICU
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

	//FILTERING
	//0010: fSAMPLING=fCK_INT, N=4
	CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF0 + ( ((Copy_u8Channel-1)%2)*8)));
	SET_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF1 + ( ((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF2 + ( ((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF3 + ( ((Copy_u8Channel-1)%2)*8)));

	// set prescaler
	TIMx->PSC = SYS_CLOCK * 10;
	TIMx -> ARR = 0xFFFFFFFF;

	//SET_BIT(TIMx->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
	SET_BIT( TIMx->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
	CLR_BIT( TIMx->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
	SET_BIT( TIMx-> DIER , Copy_u8Channel );

	SET_BIT( TIMx->CR1   , CEN );// Enable timer
	TIMx-> CNT = 0xFFFFFFFF;

}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief  Input Capture Unit (ICU) function.
 * @note   This function captures the time difference between rising and falling edges
 *         on Timer 1, Channel 4. It uses the capture/compare registers and sets the
 *         timer to capture the rising edge first, then the falling edge.
 * @return None
 */
u32 cv1=0;
u32	cv2=0;
static void LOC_TIMER_ICU(Enum_TIMER_NUM Copy_u8TimerArrIdx,Enum_TIMER_CHs Copy_u8ChannelNum) {

	// Initialize arrays to store capture state and values for each channel
	static u8 captureState[29] = {0};        // Array to store capture state for each channel
	static u32 captureValue1[29] = {0};       // Array to store capture value 1 for each channel
	static u32 captureValue2 = 0;       // Array to store capture value 2 for each channel

	// Get pointer to the memory map of the timer based on the input timer number
	TIM2_5_MemMap_t* TIMx = LOC_GET_TIMER( (Copy_u8TimerArrIdx/4) + 1);

	if (captureState[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ] == 0 ) {
		// Capture the time on the rising edge
		captureValue1[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ] = TIMx->CCR[Copy_u8ChannelNum];
		cv1= captureValue1[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ];
		// Enable falling edge capture
		SET_BIT(TIMx->CCER, (CCxP + Copy_u8ChannelNum*4) );

		// Move to the next state
		captureState[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ] = 1;
	} else {
		// Capture the time on the falling edge
		captureValue2 = TIMx->CCR[Copy_u8ChannelNum];
		cv2= captureValue2;
		// Enable rising edge capture
		CLR_BIT(TIMx->CCER, (CCxP + Copy_u8ChannelNum*4) );
		//IF Capture_Value1 > Capture_Value2 This could be due to two reasons:
		// 1) Error in edge detection due to Noise
		// 2) Timer Wraparound not handled
		//===> Solved here be let previous reading not changed
		if( captureValue1[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ] < captureValue2 ){
			// Calculate the time difference
			Time[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ] = captureValue2 - captureValue1[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ];
			timee = Time[13] / 100.0;
		}
		// Reset state value
		captureState[ ( Copy_u8TimerArrIdx + Copy_u8ChannelNum ) ] = 0;
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief   Get the ICU (Input Capture Unit) value for a specific timer and channel.
 *
 * @param   Copy_u8TimerNum: The timer number (TIMER2 or TIMER5).
 * @param   Copy_u8Channel: The channel number.
 *
 * @return  The ICU value for the specified timer and channel.
 *          If the timer is TIMER2 or TIMER5, the result is divided by (SYS_CLOCK * 100).
 */
u32 MTIMER_GET_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel) {
	return Time[(4 * (Copy_u8TimerNum - 1) + (Copy_u8Channel - 1))];
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @brief   Set a callback function for a specific timer.
 *
 * @param   Copy_u8TimerNum: The timer number.
 * @param   ptr: A pointer to the callback function to be set.
 *
 * @return  void.
 *
 * @note    The callback function will be called when the specified timer triggers an interrupt.
 */
void MTIMER_CallBack(Enum_TIMER_NUM Copy_u8TimerNum, void (*ptr)(void)) {
	// Set the callback function pointer in the GLOBAL_Ptr array
	GLOBAL_Ptr[Copy_u8TimerNum - 1] = ptr;
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM1 and TIM10 interrupts.
 *
 * @note    This function is called when either TIM1 or TIM10 triggers an interrupt.
 */
void TIM1_UP_TIM10_IRQHandler(void) {
	// Check if the update interrupt flag of TIM1 is set
	if (GET_BIT(TIM1->SR, 0)) {

		// Check if a callback function is registered for TIM1
		if (GLOBAL_Ptr[0] != STD_NULL) {
			// Call the callback function for TIM1
			GLOBAL_Ptr[0]();
		}

		// Clear the update interrupt flag of TIM1
		CLR_BIT(TIM1->SR, 0);
	}
	else {
		// Check if the capture/compare interrupt flag for CH1 of TIM10 is set
		if (GET_BIT(TIM10->SR, 1)) {

			// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM10
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU( 4 * (TIMER10 - 1) , CH1 - 1);

			// Clear the capture/compare interrupt flag for CH1 of TIM10
			CLR_BIT(TIM10->SR, CH1);
		}
		// Check if the update interrupt flag of TIM10 is set
		if (GET_BIT(TIM10->SR, 0)) {

			// Check if a callback function is registered for TIM10 (at index 6 in GLOBAL_Ptr array)
			if (GLOBAL_Ptr[6] != STD_NULL) {

				// Call the callback function for TIM10
				GLOBAL_Ptr[6]();
			}

			// Clear the update interrupt flag of TIM10
			CLR_BIT(TIM10->SR, 0);

		}
	}
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM1 trigger/completion and TIM11 interrupts.
 *
 * @note    This function is called when either TIM1 triggers a trigger/completion or TIM11 triggers an interrupt.
 */
void TIM1_TRG_COM_TIM11_IRQHandler(void) {

	// Check if the trigger interrupt or COM interrupt flag of TIM1 is set
	if (GET_BIT(TIM1->SR, 5) || GET_BIT(TIM1->SR, 6)) {
		// Handle TIMER1 trigger or COM interrupt
		// Add the necessary code or call a function for TIMER1 trigger or COM handling
	}
	else {
		// Check if the capture/compare interrupt flag for CH1 of TIM11 is set
		if (GET_BIT(TIM11->SR, 1)) {

			// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM11
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU( 4* (TIMER11 - 1) , CH1 - 1);

			// Clear the capture/compare interrupt flag for CH1 of TIM11
			CLR_BIT(TIM11->SR, CH1);
		}
		// Check if the update interrupt flag of TIM11 is set
		if (GET_BIT(TIM11->SR, 0)) {

			// Check if a callback function is registered for TIM11 (at index 7 in GLOBAL_Ptr array)
			if (GLOBAL_Ptr[7] != STD_NULL) {

				// Call the callback function for TIM11
				GLOBAL_Ptr[7]();
			}

			// Clear the update interrupt flag of TIM11
			CLR_BIT(TIM11->SR, 0);
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM1 break and TIM9 interrupts.
 *
 * @note    This function is called when either TIM1 triggers a break interrupt or TIM9 triggers an interrupt.
 */
void TIM1_BRK_TIM9_IRQHandler(void) {
	// Check if the break interrupt flag of TIM1 is set
	if (GET_BIT(TIM1->SR, 7)) {
		// Handle TIMER1 break interrupt
		// Add the necessary code or call a function for TIMER1 break handling
	}
	else {

		// Iterate through all channels of TIM9
		for (u8 ch = 1; ch <= 2; ch++) {
			// Check if the capture/compare interrupt flag for the current channel is set
			if (GET_BIT(TIM9->SR, ch)) {
				// Call the LOC_TIMER_ICU function for handling the interrupt
				// Multiplying by 4 is to get index in the array for the timer channel
				LOC_TIMER_ICU(4 * (TIMER9 - 1), ch - 1);

				// Clear the capture/compare interrupt flag for the current channel
				CLR_BIT(TIM9->SR, ch);

				// Exit the loop after handling the first set interrupt
				break;
			}
		}
		// Check if the update interrupt flag of TIM9 is set
		if (GET_BIT(TIM9->SR, 0)) {

			// Check if a callback function is registered for TIM9 (at index 5 in GLOBAL_Ptr array)
			if (GLOBAL_Ptr[5] != STD_NULL) {

				// Call the callback function for TIM9
				GLOBAL_Ptr[5]();
			}

			// Clear the update interrupt flag of TIM9
			CLR_BIT(TIM9->SR, 0);
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM1 capture/compare interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4)
 * 				 of TIM1 triggers an interrupt.
 */
void TIM1_CC_IRQHandler(void) {
	// Iterate through channels 1 to 4 of Timer 1 (TIM1)
	for (u8 ch = 1; ch <= 4; ch++) {
		// Check if the capture/compare interrupt flag for the current channel is set
		if (GET_BIT(TIM1->SR, ch)) {
			// Call the LOC_TIMER_ICU function for handling the interrupt
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU(4 * (TIMER1 - 1), ch - 1);

			// Clear the capture/compare interrupt flag for the current channel
			CLR_BIT(TIM1->SR, ch);

			// Exit the loop after handling the first set interrupt
			break;
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM2 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 * 				the update interrupt of TIM2 triggers an interrupt.
 */
void TIM2_IRQHandler(void) {
	// Iterate through all channels of TIM2
	for (u8 ch = 1; ch <= 4; ch++) {
		// Check if the capture/compare interrupt flag for the current channel is set
		if (GET_BIT(TIM2->SR, ch)) {
			// Call the LOC_TIMER_ICU function for handling the interrupt
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU( 4 * (TIMER2 - 1) , ch - 1);

			// Clear the capture/compare interrupt flag for the current channel
			CLR_BIT(TIM2->SR, ch);

			// Exit the loop after handling the first set interrupt
			break;
		}
	}

	// Check if the update interrupt flag of TIM2 is set
	if (GET_BIT(TIM2->SR, 0)) {
		// Check if a callback function is registered for TIM2 (at index 2 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[1] != STD_NULL) {

			// Call the callback function for TIM2
			GLOBAL_Ptr[1]();
		}

		// Clear the update interrupt flag of TIM2
		CLR_BIT(TIM2->SR, 0);
	}
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM3 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 * 			 the update interrupt of TIM3 triggers an interrupt.
 */
void TIM3_IRQHandler(void) {

	// Iterate through all channels of TIM3
	for (u8 ch = 1; ch <= 4; ch++) {
		// Check if the capture/compare interrupt flag for the current channel is set
		if (GET_BIT(TIM3->SR, ch)) {
			// Call the LOC_TIMER_ICU function for handling the interrupt
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU(4 * (TIMER3 - 1), ch - 1);

			// Clear the capture/compare interrupt flag for the current channel
			CLR_BIT(TIM3->SR, ch);

			// Exit the loop after handling the first set interrupt
			break;
		}
	}

	// Check if the update interrupt flag of TIM3 is set
	if (GET_BIT(TIM3->SR, 0)) {
		// Check if a callback function is registered for TIM3 (at index 3 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[2] != STD_NULL) {

			// Call the callback function for TIM3
			GLOBAL_Ptr[2]();
		}

		// Clear the update interrupt flag of TIM3
		CLR_BIT(TIM3->SR, 0);
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM4 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 * 			 the update interrupt of TIM4 triggers an interrupt.
 */
void TIM4_IRQHandler(void) {

	// Iterate through all channels of TIM4
	for (u8 ch = 1; ch <= 4; ch++) {
		// Check if the capture/compare interrupt flag for the current channel is set
		if (GET_BIT(TIM4->SR, ch)) {
			// Call the LOC_TIMER_ICU function for handling the interrupt
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU(4 * (TIMER4 - 1), ch - 1);

			// Clear the capture/compare interrupt flag for the current channel
			CLR_BIT(TIM4->SR, ch);

			// Exit the loop after handling the first set interrupt
			break;
		}
	}

	// Check if the update interrupt flag of TIM4 is set
	if (GET_BIT(TIM4->SR, 0)) {
		// Check if a callback function is registered for TIM4 (at index 4 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[3] != STD_NULL) {

			// Call the callback function for TIM4
			GLOBAL_Ptr[3]();
		}

		// Clear the update interrupt flag of TIM4
		CLR_BIT(TIM4->SR, 0);
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/**
 * @brief   Interrupt handler for TIM5 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 *  			the update interrupt of TIM5 triggers an interrupt.
 */
void TIM5_IRQHandler(void) {

	// Iterate through all channels of TIM5
	for (u8 ch = 1; ch <= 4; ch++) {
		// Check if the capture/compare interrupt flag for the current channel is set
		if (GET_BIT(TIM5->SR, ch)) {
			// Call the LOC_TIMER_ICU function for handling the interrupt
			// Multiplying by 4 is to get index in the array for the timer channel
			LOC_TIMER_ICU(4 * (TIMER5 - 1), ch - 1);

			// Clear the capture/compare interrupt flag for the current channel
			CLR_BIT(TIM5->SR, ch);

			// Exit the loop after handling the first set interrupt
			break;
		}
	}

	// Check if the update interrupt flag of TIM5 is set
	if (GET_BIT(TIM5->SR, 0)) {
		// Check if a callback function is registered for TIM5 (at index 5 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[4] != STD_NULL) {

			// Call the callback function for TIM5
			GLOBAL_Ptr[4]();
		}

		// Clear the update interrupt flag of TIM5
		CLR_BIT(TIM5->SR, 0);
	}
}
/*******************************************************************************************************/


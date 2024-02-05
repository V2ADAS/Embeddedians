/*
 * MTIMER_Prog.c
 *
 *  Created on: Dec 19, 2023
 *      Author: Hardware
 */
#include"MTIMER_Private.h"
#include"MTIMER_Int.h"
#include"MTIMER_Config.h"


static void (*GLOBAL_Ptr[8])(void)={STD_NULL};

void TIMER1_ICU(u8 Copy_u8Value);
u16 Time1[4]={0};
u32 Time2[4]={0};
u16 Time3[4]={0};
u16 Time4[4]={0};
u32 Time5[4]={0};
u16 Time9[2]={0};
u16 Time10=0;
u16 Time11=0;


void MTIMER_vTimeMS(u8 Copy_u8TimerNum,u32 Copy_u32Delay){
	//Reset Control Reg Value
	TIM1->CR1 = 0;
	//Prescaler
	TIM1->PSC = SYS_CLOCK*1000-1;
	//Auto Reset Value
	TIM1->ARR = Copy_u32Delay -1;
	//Set Update Interrupt
	SET_BIT( TIM1->DIER , UIE );
	//Control Enabled 'Start To Run'
	SET_BIT( TIM1->CR1 , CEN );
 }

void MTIMER_vPWM(u8 Copy_u8TimerNum,u8 Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec){

	SET_BIT( TIM1->CR1 , ARPE );    // Enable auto-reload preload
	CLR_BIT( TIM1->CR1 , DIR); 	// UP COUNT
	CLR_BIT( TIM1->CR1 , CMS0); 	// 00: Edge-aligned mode. The counter counts up
	CLR_BIT( TIM1->CR1 , CMS1);    // 		or down depending on the direction bit(DIR)

	//01: CCx channel is configured as output  "PWM"
	CLR_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( CCxS0+(((Copy_u8Channel-1)%2)*8)) );
	CLR_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( CCxS1+(((Copy_u8Channel-1)%2)*8)) );

	// set prescaler
	/* TIME Calculation of Total Period:
	 * Total_Period = (PSC / (SYS_CLOCK * 10^6)) * ARR
	*/
	TIM1->PSC = SYS_CLOCK*10-1;
	TIM1->ARR = ( Copy_u16TotalTime_uSec*100 )/1000; // Timer auto-reload to max <<Periodic time>>
	TIM1->CCR[Copy_u8Channel-1] = ( Copy_u16PositiveDutyCycle_uSec*100 )/1000; // << DUTY CYCLE >>
	SET_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( OCxPE+(((Copy_u8Channel-1)%2)*8)) );  //1: Preload register on TIMx_CCRx enabled

	CLR_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( OCxM0+(((Copy_u8Channel-1)%2)*8)) );// PWM Mode1 (high then low)
	SET_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( OCxM1+(((Copy_u8Channel-1)%2)*8)) );
	SET_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( OCxM2+(((Copy_u8Channel-1)%2)*8)) );

	CLR_BIT( TIM1->CCER ,( CCxP + (Copy_u8Channel-1)*4) ); //Polarity 0: active high
	//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
	SET_BIT( TIM1->CCER , ( CCxE+(Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
	SET_BIT( TIM1->BDTR , 15 );// MOE 1: OC and OCN outputs are enabled

	SET_BIT( TIM1->CR1 , CEN );// Enable timer1
}


void MTIMER_vICU(u8 Copy_u8TimerNum,u8 Copy_u8Channel){
		switch(Copy_u8TimerNum){
		case TIMER1:
			SET_BIT( TIM1->CR1 , ARPE );    // Enable auto-reload preload
			CLR_BIT( TIM1->CR1 , DIR ); 	// UP COUNT
			CLR_BIT( TIM1->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
			CLR_BIT( TIM1->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

			//01: CCx channel is configured as ICU
			SET_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
			CLR_BIT( TIM1->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

			//FILTERING
			/*SET_BIT(TIM1->CCMR[1],12);
			SET_BIT(TIM1->CCMR[1],13);
			CLR_BIT(TIM1->CCMR[1],14);
			CLR_BIT(TIM1->CCMR[1],15);*/

			// set prescaler
			TIM1->PSC = SYS_CLOCK * 100;
			TIM1 -> ARR = 0xFFFF;

			//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
			SET_BIT( TIM1->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
			CLR_BIT( TIM1->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
			SET_BIT( TIM1-> DIER , Copy_u8Channel );

			SET_BIT( TIM1->CR1   , CEN );// Enable timer1
			break;
		case TIMER2:
				SET_BIT( TIM2->CR1 , ARPE );    // Enable auto-reload preload
				CLR_BIT( TIM2->CR1 , DIR ); 	// UP COUNT
				CLR_BIT( TIM2->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
				CLR_BIT( TIM2->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

				//01: CCx channel is configured as ICU
				SET_BIT( TIM2->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
				CLR_BIT( TIM2->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

				//FILTERING
				/*SET_BIT(TIM1->CCMR[1],12);
				SET_BIT(TIM1->CCMR[1],13);
				CLR_BIT(TIM1->CCMR[1],14);
				CLR_BIT(TIM1->CCMR[1],15);*/

				// set prescaler
				TIM2->PSC = SYS_CLOCK * 100;
				TIM2 -> ARR = 0xFFFFFFFF;

				//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
				SET_BIT( TIM2->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
				CLR_BIT( TIM2->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
				SET_BIT( TIM2-> DIER , Copy_u8Channel );

				SET_BIT( TIM2->CR1   , CEN );// Enable timer2
				break;
		case TIMER3:
				SET_BIT( TIM3->CR1 , ARPE );    // Enable auto-reload preload
				CLR_BIT( TIM3->CR1 , DIR ); 	// UP COUNT
				CLR_BIT( TIM3->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
				CLR_BIT( TIM3->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

				//01: CCx channel is configured as ICU
				SET_BIT( TIM3->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
				CLR_BIT( TIM3->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

				//FILTERING
				/*SET_BIT(TIM1->CCMR[1],12);
				SET_BIT(TIM1->CCMR[1],13);
				CLR_BIT(TIM1->CCMR[1],14);
				CLR_BIT(TIM1->CCMR[1],15);*/

				// set prescaler
				TIM3 -> PSC = SYS_CLOCK * 100;
				TIM3 -> ARR = 0xFFFF;

				//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
				SET_BIT( TIM3->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
				CLR_BIT( TIM3->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
				SET_BIT( TIM3-> DIER , Copy_u8Channel );

				SET_BIT( TIM3->CR1   , CEN );// Enable timer3

				break;
		case TIMER4:
				SET_BIT( TIM4->CR1 , ARPE );    // Enable auto-reload preload
				CLR_BIT( TIM4->CR1 , DIR ); 	// UP COUNT
				CLR_BIT( TIM4->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
				CLR_BIT( TIM4->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

				//01: CCx channel is configured as ICU
				SET_BIT( TIM4->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
				CLR_BIT( TIM4->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

				//FILTERING
				/*SET_BIT(TIM1->CCMR[1],12);
				SET_BIT(TIM1->CCMR[1],13);
				CLR_BIT(TIM1->CCMR[1],14);
				CLR_BIT(TIM1->CCMR[1],15);*/

				// set prescaler
				TIM4 -> PSC = SYS_CLOCK * 100;
				TIM4 -> ARR = 0xFFFF;

				//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
				SET_BIT( TIM4->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
				CLR_BIT( TIM4->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
				SET_BIT( TIM4-> DIER , Copy_u8Channel );

				SET_BIT( TIM4->CR1   , CEN );// Enable timer4
				break;
		case TIMER5:
			SET_BIT( TIM5->CR1 , ARPE );    // Enable auto-reload preload
			CLR_BIT( TIM5->CR1 , DIR ); 	// UP COUNT
			CLR_BIT( TIM5->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
			CLR_BIT( TIM5->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

			//01: CCx channel is configured as ICU
			SET_BIT( TIM5->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
			CLR_BIT( TIM5->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

			//FILTERING
			/*SET_BIT(TIM5->CCMR[1],12);
			SET_BIT(TIM5->CCMR[1],13);
			CLR_BIT(TIM5->CCMR[1],14);
			CLR_BIT(TIM5->CCMR[1],15);*/

			// set prescaler
			TIM5 -> PSC = SYS_CLOCK * 100;
			TIM5 -> ARR = 0xFFFFffff;

			//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
			SET_BIT( TIM5->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
			CLR_BIT( TIM5->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
			SET_BIT( TIM5-> DIER , Copy_u8Channel );

			SET_BIT( TIM5->CR1   , CEN );// Enable timer4
			break;
		case TIMER9:
			SET_BIT( TIM9->CR1 , ARPE );    // Enable auto-reload preload
			CLR_BIT( TIM9->CR1 , DIR ); 	// UP COUNT
			CLR_BIT( TIM9->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
			CLR_BIT( TIM9->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

			//01: CCx channel is configured as ICU
			SET_BIT( TIM9->CCMR , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
			CLR_BIT( TIM9->CCMR , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

			//FILTERING
			/*SET_BIT(TIM9->CCMR,12);
			SET_BIT(TIM9->CCMR,13);
			CLR_BIT(TIM9->CCMR,14);
			CLR_BIT(TIM9->CCMR,15);*/

			// set prescaler
			TIM9 -> PSC = SYS_CLOCK * 100;
			TIM9 -> ARR = 0xFFFF;

			//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
			SET_BIT( TIM9->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
			CLR_BIT( TIM9->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
			SET_BIT( TIM9-> DIER , Copy_u8Channel );

			SET_BIT( TIM9->CR1   , CEN );// Enable timer4
			break;
		case TIMER10:
			SET_BIT( TIM10->CR1 , ARPE );    // Enable auto-reload preload
			CLR_BIT( TIM10->CR1 , DIR ); 	// UP COUNT
			CLR_BIT( TIM10->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
			CLR_BIT( TIM10->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

			//01: CCx channel is configured as ICU
			SET_BIT( TIM10->CCMR , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
			CLR_BIT( TIM10->CCMR , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

			//FILTERING
			/*SET_BIT(TIM10->CCMR,12);
			SET_BIT(TIM10->CCMR,13);
			CLR_BIT(TIM10->CCMR,14);
			CLR_BIT(TIM10->CCMR,15);*/

			// set prescaler
			TIM10 -> PSC = SYS_CLOCK * 100;
			TIM10 -> ARR = 0xFFFF;

			//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
			SET_BIT( TIM10->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
			CLR_BIT( TIM10->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
			SET_BIT( TIM10-> DIER , Copy_u8Channel );

			SET_BIT( TIM10->CR1   , CEN );// Enable timer4
			break;
		case TIMER11:
			SET_BIT( TIM11->CR1 , ARPE );    // Enable auto-reload preload
			CLR_BIT( TIM11->CR1 , DIR ); 	// UP COUNT
			CLR_BIT( TIM11->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
			CLR_BIT( TIM11->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

			//01: CCx channel is configured as ICU
			SET_BIT( TIM11->CCMR, ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
			CLR_BIT( TIM11->CCMR , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

			//FILTERING
			/*SET_BIT(TIM11->CCMR,12);
			SET_BIT(TIM11->CCMR,13);
			CLR_BIT(TIM11->CCMR,14);
			CLR_BIT(TIM11->CCMR,15);*/

			// set prescaler
			TIM11 -> PSC = SYS_CLOCK * 100;
			TIM11 -> ARR = 0xFFFF;

			//SET_BIT(TIM1->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
			SET_BIT( TIM11->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
			CLR_BIT( TIM11->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
			SET_BIT( TIM11-> DIER , Copy_u8Channel );

			SET_BIT( TIM11->CR1   , CEN );// Enable timer4
			break;
		}
}

/**
  * @brief  Input Capture Unit (ICU) function.
  * @note   This function captures the time difference between rising and falling edges
  *         on Timer 1, Channel 4. It uses the capture/compare registers and sets the
  *         timer to capture the rising edge first, then the falling edge.
  * @return None
  */
void TIMER1_ICU(u8 Copy_u8Value) {
    static u8 captureState[4] = {0};
    static u16 captureValue1[4] = {0};
    static u16 captureValue2[4] = {0};

    if (captureState[Copy_u8Value] == 0) {
        // Capture the time on the rising edge
        captureValue1[Copy_u8Value] = TIM1->CCR[Copy_u8Value];

        // Enable falling edge capture
        SET_BIT(TIM1->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState[Copy_u8Value] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[Copy_u8Value] = TIM1->CCR[Copy_u8Value];

        // Enable rising edge capture
        CLR_BIT(TIM1->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time1[Copy_u8Value] = captureValue2[Copy_u8Value] - captureValue1[Copy_u8Value];

        // Reset state value
        captureState[Copy_u8Value] = 0;
    }
}

void TIMER3_ICU(u8 Copy_u8Value) {
    static u8 captureState[4] = {0};
    static u16 captureValue1[4] = {0};
    static u16 captureValue2[4] = {0};

    if (captureState[Copy_u8Value] == 0) {
        // Capture the time on the rising edge
        captureValue1[Copy_u8Value] = TIM3->CCR[Copy_u8Value];

        // Enable falling edge capture
        SET_BIT(TIM3->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState[Copy_u8Value] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[Copy_u8Value] = TIM3->CCR[Copy_u8Value];

        // Enable rising edge capture
        CLR_BIT(TIM3->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time3[Copy_u8Value] = captureValue2[Copy_u8Value] - captureValue1[Copy_u8Value];

        // Reset state value
        captureState[Copy_u8Value] = 0;
    }
}

void TIMER4_ICU(u8 Copy_u8Value) {
    static u8 captureState[4] = {0};
    static u16 captureValue1[4] = {0};
    static u16 captureValue2[4] = {0};

    if (captureState[Copy_u8Value] == 0) {
        // Capture the time on the rising edge
        captureValue1[Copy_u8Value] = TIM4->CCR[Copy_u8Value];

        // Enable falling edge capture
        SET_BIT(TIM4->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState[Copy_u8Value] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[Copy_u8Value] = TIM4->CCR[Copy_u8Value];

        // Enable rising edge capture
        CLR_BIT(TIM4->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time4[Copy_u8Value] = captureValue2[Copy_u8Value] - captureValue1[Copy_u8Value];

        // Reset state value
        captureState[Copy_u8Value] = 0;
    }
}

void TIMER5_ICU(u8 Copy_u8Value) {
    static u8 captureState[4] = {0};
    static u32 captureValue1[4] = {0};
    static u32 captureValue2[4] = {0};

    if (captureState[Copy_u8Value] == 0) {
        // Capture the time on the rising edge
        captureValue1[Copy_u8Value] = TIM5->CCR[Copy_u8Value];

        // Enable falling edge capture
        SET_BIT(TIM5->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState[Copy_u8Value] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[Copy_u8Value] = TIM5->CCR[Copy_u8Value];

        // Enable rising edge capture
        CLR_BIT(TIM5->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time5[Copy_u8Value] = captureValue2[Copy_u8Value] - captureValue1[Copy_u8Value];

        // Reset state value
        captureState[Copy_u8Value] = 0;
    }
}

void TIMER2_ICU(u8 Copy_u8Value) {
    static u8 captureState[4] = {0};
    static u32 captureValue1[4] = {0};
    static u32 captureValue2[4] = {0};

    if (captureState[Copy_u8Value] == 0) {
        // Capture the time on the rising edge
        captureValue1[Copy_u8Value] = TIM2->CCR[Copy_u8Value];

        // Enable falling edge capture
        SET_BIT(TIM2->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState[Copy_u8Value] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[Copy_u8Value] = TIM2->CCR[Copy_u8Value];

        // Enable rising edge capture
        CLR_BIT(TIM2->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time2[Copy_u8Value] = captureValue2[Copy_u8Value] - captureValue1[Copy_u8Value];

        // Reset state value
        captureState[Copy_u8Value] = 0;
    }
}

void TIMER9_ICU(u8 Copy_u8Value) {
    static u8 captureState[2] = {0};
    static u16 captureValue1[2] = {0};
    static u16 captureValue2[2] = {0};

    if (captureState[Copy_u8Value] == 0) {
        // Capture the time on the rising edge
        captureValue1[Copy_u8Value] = TIM9->CCR[Copy_u8Value];

        // Enable falling edge capture
        SET_BIT(TIM9->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState[Copy_u8Value] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[Copy_u8Value] = TIM9->CCR[Copy_u8Value];

        // Enable rising edge capture
        CLR_BIT(TIM9->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time9[Copy_u8Value] = captureValue2[Copy_u8Value] - captureValue1[Copy_u8Value];

        // Reset state value
        captureState[Copy_u8Value] = 0;
    }
}

void TIMER10_ICU(u8 Copy_u8Value) {
    static u8 captureState = 0;
    static u16 captureValue1 = 0;
    static u16 captureValue2 = 0;

    if (captureState == 0) {
        // Capture the time on the rising edge
        captureValue1 = TIM10->CCR;

        // Enable falling edge capture
        SET_BIT(TIM10->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2 = TIM10->CCR;

        // Enable rising edge capture
        CLR_BIT(TIM10->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time10 = captureValue2 - captureValue1;

        // Reset state value
        captureState = 0;
    }
}

void TIMER11_ICU(u8 Copy_u8Value) {
    static u8 captureState = 0;
    static u16 captureValue1 = 0;
    static u16 captureValue2 = 0;

    if (captureState == 0) {
        // Capture the time on the rising edge
        captureValue1 = TIM11->CCR;

        // Enable falling edge capture
        SET_BIT(TIM11->CCER, (CCxP + Copy_u8Value*4) );

        // Move to the next state
        captureState= 1;
    } else {
        // Capture the time on the falling edge
        captureValue2 = TIM11->CCR;

        // Enable rising edge capture
        CLR_BIT(TIM11->CCER, (CCxP + Copy_u8Value*4) );

        // Calculate the time difference
        Time11= captureValue2 - captureValue1;

        // Reset state value
        captureState= 0;
    }
}




u32 MTIMER_GET_ICU(u8 Copy_u8TimerNum,u8 Copy_u8Channel){
	switch(Copy_u8TimerNum){
	case TIMER1:	return Time1[Copy_u8Channel - 1];
	case TIMER2:	return (Time2[Copy_u8Channel - 1]/(SYS_CLOCK*100));
	case TIMER3:	return Time3[Copy_u8Channel - 1];
	case TIMER4:	return Time4[Copy_u8Channel - 1];
	case TIMER5:	return (Time5[Copy_u8Channel - 1]/(SYS_CLOCK*100));
	case TIMER9:	return Time9[Copy_u8Channel - 1];
	case TIMER10:	return Time10;
	case TIMER11:	return Time11;
	}
}



void MTIMER_CallBack(u8 Copy_u8TimerNum,void(*ptr)(void)){
	GLOBAL_Ptr[Copy_u8TimerNum-1]=ptr;
}

void TIM1_UP_TIM10_IRQHandler(void){
	if(GET_BIT(TIM1->SR,0))
	{	if(GLOBAL_Ptr[0]!=STD_NULL)
		{   GLOBAL_Ptr[0]();	}
		CLR_BIT(TIM1->SR,0);
			}
	else{
		if( GET_BIT(TIM10-> SR,1) ){
			TIMER10_ICU(CH1 - 1);
			CLR_BIT(TIM10-> SR,CH1); }
		if(GET_BIT(TIM10-> SR,0)){
			if(GLOBAL_Ptr[6] != STD_NULL)
			{	GLOBAL_Ptr[6]();
				CLR_BIT(TIM10-> SR,0);	}
			else
				 CLR_BIT(TIM10-> SR,0);
		}
	}
}

void TIM1_TRG_COM_TIM11_IRQHandler(void){
	if(GET_BIT(TIM1->SR,5) || GET_BIT(TIM1->SR,6)){
		//TIMER1 TRIGGER or COM INTERRUPT
	}
	else{
		if( GET_BIT(TIM11-> SR,1) ){
			TIMER11_ICU(CH1 - 1);
			CLR_BIT(TIM11-> SR,CH1); }
		if(GET_BIT(TIM11-> SR,0)){
			if(GLOBAL_Ptr[7] != STD_NULL)
			{	GLOBAL_Ptr[7]();
				CLR_BIT(TIM11-> SR,0);	}
			else
				 CLR_BIT(TIM11-> SR,0);
		}
	}
}

void TIM1_BRK_TIM9_IRQHandler(void){
	if(GET_BIT(TIM1->SR,7)){
		//TIMER1 BREAK INTERRUPT
	}
	else{
		if( GET_BIT(TIM9-> SR,1) ){
			TIMER9_ICU(CH1 - 1);
			CLR_BIT(TIM9-> SR,CH1); }
		else if ( GET_BIT(TIM9-> SR,2) ){
			TIMER9_ICU(CH2 - 1);
			CLR_BIT(TIM9-> SR,CH2); }
		if(GET_BIT(TIM9-> SR,0)){
			if(GLOBAL_Ptr[5] != STD_NULL)
			{	GLOBAL_Ptr[5]();
				CLR_BIT(TIM9-> SR,0);	}
			else
				 CLR_BIT(TIM9-> SR,0);
		}
	}
}

void TIM1_CC_IRQHandler(void){
	if( GET_BIT(TIM1-> SR,1) ){
		TIMER1_ICU(CH1 - 1);
		CLR_BIT(TIM1-> SR,CH1); }
	else if ( GET_BIT(TIM1-> SR,2) ){
		TIMER1_ICU(CH2 - 1);
		CLR_BIT(TIM1-> SR,CH2); }
	else if ( GET_BIT(TIM1-> SR,3) ){
		TIMER1_ICU(CH3 - 1);
		CLR_BIT(TIM1-> SR,CH3); }
	else{
		TIMER1_ICU(CH4 - 1);
		CLR_BIT(TIM1-> SR,CH4);
	}
}

void TIM2_IRQHandler(void){
	if( GET_BIT(TIM2-> SR,1) ){
		TIMER2_ICU(CH1 - 1);
		CLR_BIT(TIM2-> SR,CH1); }
	else if ( GET_BIT(TIM2-> SR,2) ){
		TIMER2_ICU(CH2 - 1);
		CLR_BIT(TIM2-> SR,CH2); }
	else if ( GET_BIT(TIM2-> SR,3) ){
		TIMER2_ICU(CH3 - 1);
		CLR_BIT(TIM2-> SR,CH3); }
	else if( GET_BIT(TIM2-> SR,4) ){
		TIMER2_ICU(CH4 - 1);
		CLR_BIT(TIM2-> SR,CH4);
	}
	if(GET_BIT(TIM2-> SR,0)){
		if(GLOBAL_Ptr[2] != STD_NULL)
		{	GLOBAL_Ptr[2]();
			CLR_BIT(TIM2-> SR,0);	}
		else
			 CLR_BIT(TIM2-> SR,0);
	}

}

void TIM3_IRQHandler(void){
	if( GET_BIT(TIM3-> SR,1) ){
		TIMER3_ICU(CH1 - 1);
		CLR_BIT(TIM3-> SR,CH1); }
	else if ( GET_BIT(TIM3-> SR,2) ){
		TIMER3_ICU(CH2 - 1);
		CLR_BIT(TIM3-> SR,CH2); }
	else if ( GET_BIT(TIM3-> SR,3) ){
		TIMER3_ICU(CH3 - 1);
		CLR_BIT(TIM3-> SR,CH3); }
	else if( GET_BIT(TIM3-> SR,4) ){
		TIMER3_ICU(CH4 - 1);
		CLR_BIT(TIM3-> SR,CH4);
	}
	if(GET_BIT(TIM3-> SR,0)){
		if(GLOBAL_Ptr[3] != STD_NULL)
		{	GLOBAL_Ptr[3]();
			CLR_BIT(TIM3-> SR,0);	}
		else
			 CLR_BIT(TIM3-> SR,0);
	}
}

void TIM4_IRQHandler(void){
	if( GET_BIT(TIM4-> SR,1) ){
		TIMER4_ICU(CH1 - 1);
		CLR_BIT(TIM4-> SR,CH1); }
	else if ( GET_BIT(TIM4-> SR,2) ){
		TIMER4_ICU(CH2 - 1);
		CLR_BIT(TIM4-> SR,CH2); }
	else if ( GET_BIT(TIM4-> SR,3) ){
		TIMER4_ICU(CH3 - 1);
		CLR_BIT(TIM4-> SR,CH3); }
	else if( GET_BIT(TIM4-> SR,4) ){
		TIMER4_ICU(CH4 - 1);
		CLR_BIT(TIM4-> SR,CH4);
	}
	if(GET_BIT(TIM4-> SR,0)){
		if(GLOBAL_Ptr[4] != STD_NULL)
		{	GLOBAL_Ptr[4]();
			CLR_BIT(TIM4-> SR,0);	}
		else
			 CLR_BIT(TIM4-> SR,0);
	}

}

void TIM5_IRQHandler(void){
	if( GET_BIT(TIM5-> SR,1) ){
		TIMER5_ICU(CH1 - 1);
		CLR_BIT(TIM5-> SR,CH1); }
	else if ( GET_BIT(TIM5-> SR,2) ){
		TIMER5_ICU(CH2 - 1);
		CLR_BIT(TIM5-> SR,CH2); }
	else if ( GET_BIT(TIM5-> SR,3) ){
		TIMER5_ICU(CH3 - 1);
		CLR_BIT(TIM5-> SR,CH3); }
	else if( GET_BIT(TIM5-> SR,4) ){
		TIMER5_ICU(CH4 - 1);
		CLR_BIT(TIM5-> SR,CH4);
	}
	if(GET_BIT(TIM5-> SR,0)){
		if(GLOBAL_Ptr[5] != STD_NULL)
		{	GLOBAL_Ptr[5]();
			CLR_BIT(TIM5-> SR,0);	}
		else
			 CLR_BIT(TIM5-> SR,0);
	}

}



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

void TIMER_ICU(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8ChannelNum);
u32 Time[29]={0};

TIM2_5_MemMap_t* GET_TIMER(u32 Copy_u8TimerNum){
    u32 Timer_Offset[8] = TIMERS_OFFSET;
	TIM2_5_MemMap_t* TIMx = (u32)TIM2 + Timer_Offset[Copy_u8TimerNum-1];
	return TIMx;
}

/**
 * @brief   Configure the specified timer for a periodic delay in milliseconds.
 *
 * @param   Copy_u8TimerNum: The timer number to be configured.
 * @param   Copy_u32Delay: The desired delay in milliseconds.
 *
 * @note    This function configures the timer with the specified number for a periodic delay.
 *          The timer is set up to generate an interrupt after the specified delay.
 *          for TIMERS 1,3,4,9,10,11 MAXIMUM Allowable Delay is 65.536 sec
 *          for TIMER  2,5 MAXIMUM Allowable Delay is 49.71 DAY!!
 */
void MTIMER_vPeriodicMS(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delay) {
    // Get the base address of the specified timer
    TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);

    // Reset Control Register 1 Value
    TIMx->CR1 = 0;

    // Set the prescaler value to achieve a 1ms time base
    TIMx->PSC = SYS_CLOCK * 1000 - 1;

    // Set the auto-reload value to achieve the desired delay
    TIMx->ARR = Copy_u32Delay - 1;

    // Set the Update Interrupt Enable bit to enable the interrupt
    SET_BIT(TIMx->DIER, UIE);

    // Set the Counter Enable bit to start the timer
    SET_BIT(TIMx->CR1, CEN);
}


void MTIMER_vPWM(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec){
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);
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

	SET_BIT( TIMx->CR1 , CEN );// Enable timer1
	TIMx->CNT = 0xFFFFFFFF;
}


void MTIMER_vICU(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8Channel){
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);
		SET_BIT( TIMx->CR1 , ARPE );    // Enable auto-reload preload
		CLR_BIT( TIMx->CR1 , DIR ); 	// UP COUNT
		CLR_BIT( TIMx->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
		CLR_BIT( TIMx->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

		//01: CCx channel is configured as ICU
		SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
		CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

		//FILTERING
		SET_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF0 + ( ((Copy_u8Channel-1)%2)*8)));
		SET_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF1 + ( ((Copy_u8Channel-1)%2)*8)));
		CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF2 + ( ((Copy_u8Channel-1)%2)*8)));
		CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF3 + ( ((Copy_u8Channel-1)%2)*8)));

		// set prescaler
		TIMx->PSC = SYS_CLOCK * 100;
		TIMx -> ARR = 0xFFFFFFFF;

		//SET_BIT(TIMx->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
		SET_BIT( TIMx->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
		CLR_BIT( TIMx->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
		SET_BIT( TIMx-> DIER , Copy_u8Channel );

		SET_BIT( TIMx->CR1   , CEN );// Enable timer1
		TIMx-> CNT = 0xFFFFFFFF;

}

/**
  * @brief  Input Capture Unit (ICU) function.
  * @note   This function captures the time difference between rising and falling edges
  *         on Timer 1, Channel 4. It uses the capture/compare registers and sets the
  *         timer to capture the rising edge first, then the falling edge.
  * @return None
  */
void TIMER_ICU(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8ChannelNum) {
    static u8 captureState[29] = {0};
    static u32 captureValue1[29] = {0};
    static u32 captureValue2[29] = {0};
    TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum+1);
    if (captureState[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] == 0) {
        // Capture the time on the rising edge
        captureValue1[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = TIMx->CCR[Copy_u8ChannelNum];

        // Enable falling edge capture
        SET_BIT(TIMx->CCER, (CCxP + Copy_u8ChannelNum*4) );

        // Move to the next state
        captureState[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = 1;
    } else {
        // Capture the time on the falling edge
        captureValue2[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = TIMx->CCR[Copy_u8ChannelNum];

        // Enable rising edge capture
        CLR_BIT(TIMx->CCER, (CCxP + Copy_u8ChannelNum*4) );

        // Calculate the time difference
        Time[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = captureValue2[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] - captureValue1[(4*Copy_u8TimerNum+Copy_u8ChannelNum)];

        // Reset state value
        captureState[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = 0;
    }
}



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


/**
 * @brief   Set a callback function for a specific timer.
 *
 * @param   Copy_u8TimerNum: The timer number.
 * @param   ptr: A pointer to the callback function to be set.
 *
 * @return  None.
 *
 * @note    The callback function will be called when the specified timer triggers an interrupt.
 */
void MTIMER_CallBack(Enum_TIMER_NUM Copy_u8TimerNum, void (*ptr)(void)) {
    // Set the callback function pointer in the GLOBAL_Ptr array
    GLOBAL_Ptr[Copy_u8TimerNum - 1] = ptr;
}


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
    } else {
        // Check if the capture/compare interrupt flag for CH1 of TIM10 is set
        if (GET_BIT(TIM10->SR, 1)) {
            // Call the TIMER_ICU function for handling CH1 interrupt of TIM10
            TIMER_ICU(TIMER10 - 1, CH1 - 1);
            // Clear the capture/compare interrupt flag for CH1 of TIM10
            CLR_BIT(TIM10->SR, CH1);
        }
        // Check if the update interrupt flag of TIM10 is set
        if (GET_BIT(TIM10->SR, 0)) {
            // Check if a callback function is registered for TIM10 (at index 6 in GLOBAL_Ptr array)
            if (GLOBAL_Ptr[6] != STD_NULL) {
                // Call the callback function for TIM10
                GLOBAL_Ptr[6]();
                // Clear the update interrupt flag of TIM10
                CLR_BIT(TIM10->SR, 0);
            } else {
                // Clear the update interrupt flag of TIM10 without calling a callback function
                CLR_BIT(TIM10->SR, 0);
            }
        }
    }
}


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
    } else {
        // Check if the capture/compare interrupt flag for CH1 of TIM11 is set
        if (GET_BIT(TIM11->SR, 1)) {
            // Call the TIMER_ICU function for handling CH1 interrupt of TIM11
            TIMER_ICU(TIMER11 - 1, CH1 - 1);
            // Clear the capture/compare interrupt flag for CH1 of TIM11
            CLR_BIT(TIM11->SR, CH1);
        }
        // Check if the update interrupt flag of TIM11 is set
        if (GET_BIT(TIM11->SR, 0)) {
            // Check if a callback function is registered for TIM11 (at index 7 in GLOBAL_Ptr array)
            if (GLOBAL_Ptr[7] != STD_NULL) {
                // Call the callback function for TIM11
                GLOBAL_Ptr[7]();
                // Clear the update interrupt flag of TIM11
                CLR_BIT(TIM11->SR, 0);
            } else {
                // Clear the update interrupt flag of TIM11 without calling a callback function
                CLR_BIT(TIM11->SR, 0);
            }
        }
    }
}


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
    } else {
        // Check if the capture/compare interrupt flag for CH1 of TIM9 is set
        if (GET_BIT(TIM9->SR, 1)) {
            // Call the TIMER_ICU function for handling CH1 interrupt of TIM9
            TIMER_ICU(TIMER9 - 1, CH1 - 1);
            // Clear the capture/compare interrupt flag for CH1 of TIM9
            CLR_BIT(TIM9->SR, CH1);
        } else if (GET_BIT(TIM9->SR, 2)) {
            // Call the TIMER_ICU function for handling CH2 interrupt of TIM9
            TIMER_ICU(TIMER9 - 1, CH2 - 1);
            // Clear the capture/compare interrupt flag for CH2 of TIM9
            CLR_BIT(TIM9->SR, CH2);
        }
        // Check if the update interrupt flag of TIM9 is set
        if (GET_BIT(TIM9->SR, 0)) {
            // Check if a callback function is registered for TIM9 (at index 5 in GLOBAL_Ptr array)
            if (GLOBAL_Ptr[5] != STD_NULL) {
                // Call the callback function for TIM9
                GLOBAL_Ptr[5]();
                // Clear the update interrupt flag of TIM9
                CLR_BIT(TIM9->SR, 0);
            } else {
                // Clear the update interrupt flag of TIM9 without calling a callback function
                CLR_BIT(TIM9->SR, 0);
            }
        }
    }
}

/**
 * @brief   Interrupt handler for TIM1 capture/compare interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) of TIM1 triggers an interrupt.
 */
void TIM1_CC_IRQHandler(void) {
    // Check if the capture/compare interrupt flag for CH1 of TIM1 is set
    if (GET_BIT(TIM1->SR, 1)) {
        // Call the TIMER_ICU function for handling CH1 interrupt of TIM1
        TIMER_ICU(TIMER1 - 1, CH1 - 1);
        // Clear the capture/compare interrupt flag for CH1 of TIM1
        CLR_BIT(TIM1->SR, CH1);
    } else if (GET_BIT(TIM1->SR, 2)) {
        // Call the TIMER_ICU function for handling CH2 interrupt of TIM1
        TIMER_ICU(TIMER1 - 1, CH2 - 1);
        // Clear the capture/compare interrupt flag for CH2 of TIM1
        CLR_BIT(TIM1->SR, CH2);
    } else if (GET_BIT(TIM1->SR, 3)) {
        // Call the TIMER_ICU function for handling CH3 interrupt of TIM1
        TIMER_ICU(TIMER1 - 1, CH3 - 1);
        // Clear the capture/compare interrupt flag for CH3 of TIM1
        CLR_BIT(TIM1->SR, CH3);
    } else {
        // Call the TIMER_ICU function for handling CH4 interrupt of TIM1
        TIMER_ICU(TIMER1 - 1, CH4 - 1);
        // Clear the capture/compare interrupt flag for CH4 of TIM1
        CLR_BIT(TIM1->SR, CH4);
    }
}

/**
 * @brief   Interrupt handler for TIM2 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or the update interrupt of TIM2 triggers an interrupt.
 */
void TIM2_IRQHandler(void) {
    // Check if the capture/compare interrupt flag for CH1 of TIM2 is set
    if (GET_BIT(TIM2->SR, 1)) {
        // Call the TIMER_ICU function for handling CH1 interrupt of TIM2
        TIMER_ICU(TIMER2 - 1, CH1 - 1);
        // Clear the capture/compare interrupt flag for CH1 of TIM2
        CLR_BIT(TIM2->SR, CH1);
    } else if (GET_BIT(TIM2->SR, 2)) {
        // Call the TIMER_ICU function for handling CH2 interrupt of TIM2
        TIMER_ICU(TIMER2 - 1, CH2 - 1);
        // Clear the capture/compare interrupt flag for CH2 of TIM2
        CLR_BIT(TIM2->SR, CH2);
    } else if (GET_BIT(TIM2->SR, 3)) {
        // Call the TIMER_ICU function for handling CH3 interrupt of TIM2
        TIMER_ICU(TIMER2 - 1, CH3 - 1);
        // Clear the capture/compare interrupt flag for CH3 of TIM2
        CLR_BIT(TIM2->SR, CH3);
    } else if (GET_BIT(TIM2->SR, 4)) {
        // Call the TIMER_ICU function for handling CH4 interrupt of TIM2
        TIMER_ICU(TIMER2 - 1, CH4 - 1);
        // Clear the capture/compare interrupt flag for CH4 of TIM2
        CLR_BIT(TIM2->SR, CH4);
    }

    // Check if the update interrupt flag of TIM2 is set
    if (GET_BIT(TIM2->SR, 0)) {
        // Check if a callback function is registered for TIM2 (at index 2 in GLOBAL_Ptr array)
        if (GLOBAL_Ptr[1] != STD_NULL) {
            // Call the callback function for TIM2
            GLOBAL_Ptr[1]();
            // Clear the update interrupt flag of TIM2
            CLR_BIT(TIM2->SR, 0);
        } else {
            // Clear the update interrupt flag of TIM2 without calling a callback function
            CLR_BIT(TIM2->SR, 0);
        }
    }
}


/**
 * @brief   Interrupt handler for TIM3 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or the update interrupt of TIM3 triggers an interrupt.
 */
void TIM3_IRQHandler(void) {
    // Check if the capture/compare interrupt flag for CH1 of TIM3 is set
    if (GET_BIT(TIM3->SR, 1)) {
        // Call the TIMER_ICU function for handling CH1 interrupt of TIM3
        TIMER_ICU(TIMER3 - 1, CH1 - 1);
        // Clear the capture/compare interrupt flag for CH1 of TIM3
        CLR_BIT(TIM3->SR, CH1);
    } else if (GET_BIT(TIM3->SR, 2)) {
        // Call the TIMER_ICU function for handling CH2 interrupt of TIM3
        TIMER_ICU(TIMER3 - 1, CH2 - 1);
        // Clear the capture/compare interrupt flag for CH2 of TIM3
        CLR_BIT(TIM3->SR, CH2);
    } else if (GET_BIT(TIM3->SR, 3)) {
        // Call the TIMER_ICU function for handling CH3 interrupt of TIM3
        TIMER_ICU(TIMER3 - 1, CH3 - 1);
        // Clear the capture/compare interrupt flag for CH3 of TIM3
        CLR_BIT(TIM3->SR, CH3);
    } else if (GET_BIT(TIM3->SR, 4)) {
        // Call the TIMER_ICU function for handling CH4 interrupt of TIM3
        TIMER_ICU(TIMER3 - 1, CH4 - 1);
        // Clear the capture/compare interrupt flag for CH4 of TIM3
        CLR_BIT(TIM3->SR, CH4);
    }

    // Check if the update interrupt flag of TIM3 is set
    if (GET_BIT(TIM3->SR, 0)) {
        // Check if a callback function is registered for TIM3 (at index 3 in GLOBAL_Ptr array)
        if (GLOBAL_Ptr[2] != STD_NULL) {
            // Call the callback function for TIM3
            GLOBAL_Ptr[2]();
            // Clear the update interrupt flag of TIM3
            CLR_BIT(TIM3->SR, 0);
        } else {
            // Clear the update interrupt flag of TIM3 without calling a callback function
            CLR_BIT(TIM3->SR, 0);
        }
    }
}

/**
 * @brief   Interrupt handler for TIM4 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or the update interrupt of TIM4 triggers an interrupt.
 */
void TIM4_IRQHandler(void) {
    // Check if the capture/compare interrupt flag for CH1 of TIM4 is set
    if (GET_BIT(TIM4->SR, 1)) {
        // Call the TIMER_ICU function for handling CH1 interrupt of TIM4
        TIMER_ICU(TIMER4 - 1, CH1 - 1);
        // Clear the capture/compare interrupt flag for CH1 of TIM4
        CLR_BIT(TIM4->SR, CH1);
    } else if (GET_BIT(TIM4->SR, 2)) {
        // Call the TIMER_ICU function for handling CH2 interrupt of TIM4
        TIMER_ICU(TIMER4 - 1, CH2 - 1);
        // Clear the capture/compare interrupt flag for CH2 of TIM4
        CLR_BIT(TIM4->SR, CH2);
    } else if (GET_BIT(TIM4->SR, 3)) {
        // Call the TIMER_ICU function for handling CH3 interrupt of TIM4
        TIMER_ICU(TIMER4 - 1, CH3 - 1);
        // Clear the capture/compare interrupt flag for CH3 of TIM4
        CLR_BIT(TIM4->SR, CH3);
    } else if (GET_BIT(TIM4->SR, 4)) {
        // Call the TIMER_ICU function for handling CH4 interrupt of TIM4
        TIMER_ICU(TIMER4 - 1, CH4 - 1);
        // Clear the capture/compare interrupt flag for CH4 of TIM4
        CLR_BIT(TIM4->SR, CH4);
    }

    // Check if the update interrupt flag of TIM4 is set
    if (GET_BIT(TIM4->SR, 0)) {
        // Check if a callback function is registered for TIM4 (at index 4 in GLOBAL_Ptr array)
        if (GLOBAL_Ptr[3] != STD_NULL) {
            // Call the callback function for TIM4
            GLOBAL_Ptr[3]();
            // Clear the update interrupt flag of TIM4
            CLR_BIT(TIM4->SR, 0);
        } else {
            // Clear the update interrupt flag of TIM4 without calling a callback function
            CLR_BIT(TIM4->SR, 0);
        }
    }
}

/**
 * @brief   Interrupt handler for TIM5 capture/compare and update interrupts.
 *
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or the update interrupt of TIM5 triggers an interrupt.
 */
void TIM5_IRQHandler(void) {
    // Check if the capture/compare interrupt flag for CH1 of TIM5 is set
    if (GET_BIT(TIM5->SR, 1)) {
        // Call the TIMER_ICU function for handling CH1 interrupt of TIM5
        TIMER_ICU(TIMER5 - 1, CH1 - 1);
        // Clear the capture/compare interrupt flag for CH1 of TIM5
        CLR_BIT(TIM5->SR, CH1);
    } else if (GET_BIT(TIM5->SR, 2)) {
        // Call the TIMER_ICU function for handling CH2 interrupt of TIM5
        TIMER_ICU(TIMER5 - 1, CH2 - 1);
        // Clear the capture/compare interrupt flag for CH2 of TIM5
        CLR_BIT(TIM5->SR, CH2);
    } else if (GET_BIT(TIM5->SR, 3)) {
        // Call the TIMER_ICU function for handling CH3 interrupt of TIM5
        TIMER_ICU(TIMER5 - 1, CH3 - 1);
        // Clear the capture/compare interrupt flag for CH3 of TIM5
        CLR_BIT(TIM5->SR, CH3);
    } else if (GET_BIT(TIM5->SR, 4)) {
        // Call the TIMER_ICU function for handling CH4 interrupt of TIM5
        TIMER_ICU(TIMER5 - 1, CH4 - 1);
        // Clear the capture/compare interrupt flag for CH4 of TIM5
        CLR_BIT(TIM5->SR, CH4);
    }

    // Check if the update interrupt flag of TIM5 is set
    if (GET_BIT(TIM5->SR, 0)) {
        // Check if a callback function is registered for TIM5 (at index 5 in GLOBAL_Ptr array)
        if (GLOBAL_Ptr[4] != STD_NULL) {
            // Call the callback function for TIM5
            GLOBAL_Ptr[4]();
            // Clear the update interrupt flag of TIM5
            CLR_BIT(TIM5->SR, 0);
        } else {
            // Clear the update interrupt flag of TIM5 without calling a callback function
            CLR_BIT(TIM5->SR, 0);
        }
    }
}



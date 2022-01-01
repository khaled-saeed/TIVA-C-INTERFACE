#include "TM4C123.h"                    // Device header
#include "timers.h"

/**
	in arm we have 6 timer modules  consist of two 16 bit registers each register can be used alone or compined with
		another to form 32 bit register
		and another 6 timers modules consist of two 32 bit registers each register can be used alone or compined with
		another to form 64 bit register
*/

void Input_Edge_Time_Mode(void)	// catching the time between events
{
		/************* TIMER INITIALIZATION ************/
	SYSCTL->RCGCTIMER |= TIMER1_CLK  ;
	TIMER1->CTL &= ~0x01U ; 				// disable while configuration
	TIMER1->CFG |= 0x04 ; 					// selecting 16 bit timer
	TIMER1->TAMR |= CAPTURING_MODE | TIME_COUNT |COUNT_UP ;
	TIMER1->CTL |= BOTH_EDGES ; 			// capture both edges
	TIMER1->TAPR |= 0xFF ; 					// use a prescaler the value to cout to as we're using count up
	TIMER1->TAILR |= 0xFFFF ; 				// count up to 65535 before the flag
	TIMER1->ICR |= (1U<<2) ; 				// clear the  capture mode interrupt
	TIMER1->CTL |= 0x01 ;					// enable the timer

	/*********** ALTERNATIVE FUNCTION INITIALIZATION PB4 **********/
  		/********* using PB4 as the pin for capturing ********/
	SYSCTL->RCGCGPIO |= PORTB_CLK ;
	GPIOB->DIR &= ~(1U<<4) ; 				// bit 4 as input
	GPIOB->AFSEL |=  (1U<<4) ;
	GPIOB->PCTL &= ~(0xFU<<16) ;
	GPIOB->PCTL |= (7U<<16) ;
	GPIOB->DEN |= (1U<<4) ;

}

void Input_Edge_Count_Mode(void)			// counting the no of events
{
	/************* TIMER INITIALIZATION ************/
	SYSCTL->RCGCTIMER |= TIMER2_CLK ;
	TIMER2->CTL &= ~TIMER_EN ; 						//Ensure the timer is disabled (the TnEN bit is cleared) before making any changes.
	TIMER2->CFG |= 0x04 ; 							//selecting 16 bit timer
	TIMER2->TAMR |= CAPTURING_MODE |COUNT_UP   ;
	TIMER2->CTL |= POSTIVE_EDGE ;
	TIMER2->TAILR |= 0xFFFF ;
	TIMER2->IMR |= EVENT_CAPTURE_INT ;
	TIMER2->CTL |= TIMER_EN ;
	TIMER2->ICR |= EVENT_CAPTURE_INT ;

	/*********** ALTERNATIVE FUNCTION INITIALIZATION PB0 **********/
	SYSCTL->RCGCGPIO |= PORTB_CLK ;
	GPIOB->DIR &= ~(1U<<0) ; 						// bit 0 as input
	GPIOB->AFSEL |= (1U<<0) ;
	GPIOB->PCTL &= ~(0xFU<<0) ;
	GPIOB->PCTL |= (0x07U<<0);
	GPIOB->DEN |= (1U<<0) ;

}

void TIMER0_PERIODIC_MODE_MICRO(void)  // using timer0 to produce a delay in microseconds
{
	SYSCTL->RCGCTIMER |= TIMER0_CLK ;
	TIMER0->CTL &= ~TIMER_EN ;
	TIMER0->CFG |= 0x04 ;							// 16 bit configuration
	TIMER0->TAMR |= PERIDIC_MODE | COUNT_UP ;
	TIMER0->TAILR |= 16-1 ;
	TIMER0->ICR |= TIMEOUT_FLAG ;					// clear the time out interrupt flag
	TIMER0->CTL |= TIMER_EN ;
}
void DELAY_TIMER_MICROS(unsigned long micros)
{
	while(micros--)
	{
		while((TIMER0->RIS & TIMEOUT_FLAG) != 1 ) ;
		TIMER0->ICR |= TIMEOUT_FLAG ;
	}

}
void TIMER3_PERIODIC_MODE_MILLIS(void) 	// using timer 3 to produce delay in milliseconds
{
	SYSCTL->RCGCTIMER |= TIMER3_CLK ;
	TIMER3->CTL &= ~TIMER_EN ;
	TIMER3->CFG |= 0x04 ;					// 16 bit configuration
	TIMER3->TAMR |= PERIDIC_MODE | COUNT_UP ;
	TIMER3->TAILR |= 16000-1 ;
	TIMER3->ICR |= TIMEOUT_FLAG ;			// clear the time out interrupt flag
	TIMER3->CTL |= TIMER_EN ;
}
void DELAY_TIMER_MILLIS(unsigned long MS)
{
	while(MS--)
	{
		while((TIMER3->RIS & TIMEOUT_FLAG) != 1 ) ;
		TIMER3->ICR |= TIMEOUT_FLAG ;
	}
}

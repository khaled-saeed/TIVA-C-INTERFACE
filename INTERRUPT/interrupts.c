#include "TM4C123.h"                    // Device header
#include "interrupts.h" 
#include "lights.h"

void PORTF_INT_INIT(void)
{
	SYSCTL->RCGCGPIO |= PORTF_CLK ; 
	GPIOF->LOCK |= LOCK_KEY ; 
	GPIOF->CR |= 0x01 ; 
	GPIOF->DIR &= ~(SW1 )|~( SW2) ; 
	GPIOF->PUR |= (SW1 | SW2) ;
	GPIOF->DEN |= (SW1 |SW2 ) ;
	GPIOF->IS |= (SW1|SW2) ; 
	GPIOF->IEV &= ~(SW1 & SW2) ; // clearing the bits means we're triggering the interrupt at falling edge
	GPIOF->IM |= (SW1 | SW2) ; 	// setting a bit allows it to send interrupt trigger 
	NVIC->ISER[0] |= PORTF_NVIC_INT ; 
}

/**


8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
Register (GPTMICR).
If the TnMIE bit in the GPTMTnMR register is set, the RTCRIS bit in the GPTMRIS register is set,
and the timer continues counting. In One-Shot mode, the timer stops counting after the time-out
event. To re-enable the timer, repeat the sequence. A timer configured in Periodic mode reloads
the timer and continues counting after the time-out event.




*/
void TIMER0A_INT_INIT(void) 
{
	SYSCTL->RCGCTIMER |= 	TIMER0_CLK ; 
	TIMER0->CTL |= 0x00 ; 
	TIMER0->CFG |= 0x04 ;									 // for 16 bit config in 16/32 mode 
	TIMER0->TAMR |= (UP_COUNT| PERIODIC_MODE) ; 
	TIMER0->TAPR |= 250;
	TIMER0->TAILR |= 64000-1 ;						 // configure for a one second 
	TIMER0->IMR |= TIME_OUT_INT ; 				// timeout interrupt mode 
	TIMER0->ICR |= 0x01 ; 								// clear the interrupt 
	TIMER0->CTL |= 0x01 ; 								// enable te interrupt 
	NVIC->ISER[0] |= NVIC_TIMER0A ; 
	
}

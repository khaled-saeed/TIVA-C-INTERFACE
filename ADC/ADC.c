#include "TM4C123.h"                    // Device header
#include "ADC_BSP.h" 


void ADC_INIT (void)
{
	SYSCTL->RCGCADC |= 0x01 ; // ADC0 
	SYSCTL->RCGCGPIO |= PORT_E ;  // AN0 --> PE3 

	/*************  The GPIO pin for  ADC *****************/
	GPIOE->AFSEL |= AN0 ; 
	GPIOE->DEN &= ~AN0 ; 
	GPIOE->AMSEL |= AN0 ; 
	/********** ADC0 sample sequencer config ***************/
	ADC0->ACTSS &= ~SS3 ;  // start by disabling SS3 before config 
	ADC0->EMUX &= ~(0xFU<<12); // clear the EM3 to choose trigger sampling via software  by setting SSn bit in ADCPSSI
	ADC0->SSMUX3 = 0;					// choosing SS3 AND AN0 in SS3 
	ADC0->SSCTL3 |= (1U<<1)|(1U<<2);// one sample at a time and use interrupt  
	ADC0->PC = 0x3;						// configure the sampling rate to 250 KSPS 
	/****** if with interrupt *******/ 
	ADC0->IM |= SS3 ; 			// enable interrupt 
	ADC0->ACTSS |= SS3 ; 		// enable SS3 
	NVIC->ISER[0] |= 0x00020000 ;

}


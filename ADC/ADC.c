#include "TM4C123.h"                    // Device header
#include "ADC_BSP.h"
/**
!brief : initializing ADC0 using one sample with SS3 @ sampling rate 250 KSPS the sampling starts using interrupt
*/

void ADC0_INIT (void)
{
	SYSCTL->RCGCADC |= ADC0 ; 				// Enable ADC0 clock
	SYSCTL->RCGCGPIO |= PORT_E ;  			// Enable PORTE clock

	/*************  The GPIO pin for  ADC *****************/
	GPIOE->AFSEL |= AN0 ; 					//Enable alternative function for pin PE3
	GPIOE->DEN &= ~AN0 ; 					//disable the digital functionality  for pin PE3
	GPIOE->AMSEL |= AN0 ; 					//Enable analog functionality for PE3
	/********** ADC0 sample sequencer configuration ***************/
	ADC0->ACTSS &= ~SS3 ;  					// start by disabling SS3 before configuration
	ADC0->EMUX &= ~(0xFU<<12); 				// clear the EM3 to choose trigger sampling via software by setting SSn bit in ADCPSSI
	ADC0->SSMUX3 = 0;						// choosing SS3 AND AN0 in SS3
	ADC0->SSCTL3 |= (1U<<1)|(1U<<2);		// one sample at a time and use interrupt
	ADC0->PC = 0x3;							// configure the sampling rate to 250 KSPS
	/****** if with interrupt *******/
	ADC0->IM |= SS3 ; 						// enable interrupt
	ADC0->ACTSS |= SS3 ; 					// enable SS3
	NVIC->ISER[0] |= 0x00020000 ;			// enable the interrupt in NVIC

}

/** if we're using interrupts we mus include this ISR in the main module
void ADC0SS3_Handler(void){

	adc_value = ADC0->SSFIFO3; // read adc coversion result from SS3 FIFO
	ADC0->ISC = 8;          	//clear coversion clear flag bit
  ADC0->PSSI |= (1<<3);        // Enable SS3 conversion or start sampling data from AN0

}
*/

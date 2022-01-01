#include "TM4C123GH6PM.h"
#include "PWM.h"

/*!

@brief : Intializing PWM0 Gen0 with DIV = 2  to freq = 1 KHz and duty cycle 50% for channle A and 75% for channle B
*/

void PWM0G0_MODE_INIT(void)
{

	/********** PWM INITIALIZATION **************/ // M0PWM0 (PB6) & M0PWM1 (PB7)
	SYSCTL->RCGCPWM |= (1U<<0)	 ;
	SYSCTL->RCC |= (0x01U<<20) ; 									// select PWMDIV
	SYSCTL->RCC &= ~(0x7U<<17) ; 									// DIV = 2 (16MHz / 2 = 8MHz)
	PWM0->_0_CTL &= ~(0x01U<<0);  									// disable module 0 genrator 0 for confiuration contains M0PWM0 & M0PWM1
	PWM0->_0_CTL |= COUNT_UP ;
	PWM0->_0_LOAD |= 8000 ;												// for a 1KHz PWM  (8 MHz / 1 KHz )
	PWM0->_0_CMPA |= 4000 ; 											// duty cycle 50% then the compare value = 50% of load value
	PWM0->_0_CMPB |= 6000 ; 											// duty cycle for channl B is 75%
	PWM0->_0_GENA |= (0x03U<<2) |(0x02U<<4);							// go high at reload value and down at compare value for both A & B
	PWM0->_0_GENB |= (0x03U<<2) |(0x02U<<4);
	PWM0->_0_CTL |= (0x01U<<0);  										// enable PWM

	/********** GPIO MODUL INITIALIZATION ************/
	SYSCTL->RCGCGPIO |= (1U<<1) ;   								// PORTB
	GPIOB->DIR |= M0PWM0 | M0PWM1 ;
	GPIOB->AFSEL |= M0PWM0 | M0PWM1 ;
	GPIOB->PCTL &= ~(0xFU<<28) | ~(0xFU<<24) ;
	GPIOB->PCTL |= (0x4U<<28) | (0x4U<<24) ;
	GPIOB->DEN |= M0PWM0 | M0PWM1 ;
	PWM0->ENABLE |= (0x01U<<0)|(0x01<<1) ;
}

/*!
@brief : Intializing PWM1 Gen3 No DIV   to freq = 50Hz and duty cycle 50% for channle A
*/
void PWM1G3_MODE_INIT(void)
{
	/************ PWM Initialization **************/
	SYSCTL->RCGCPWM |= (1U<<1) ; 						// enable PWM module 1
	SYSCTL->RCC |= (1U<<20);					  	  // USE DIVIDER , the system clock is the source of the clock
	SYSCTL->RCC |= (2U<<17);							  // divid by 8 , then the PWM module freq = 2 MHz
	PWM1->_3_CTL &= ~(1U<<0) ;						  // disable Generatr 3 while configuration
	PWM1->_3_CTL |= COUNT_UP ;
	PWM1->_3_GENA |=(0x3U<<2) | (0x2U<<4);	// go high at load value and low at comprator value for PWM6
	PWM1->_3_GENB |=(0x2U<<2) | (0x3U<<8);	// go low at load value and high at comprator value for PWM7
	PWM1->_3_LOAD |= 40000 ; 								// load value = clock / needed freq =2000000/50 = 40000
	PWM1->_3_CMPA |= 20000 ; 								// for duty cycle 50% CMPA = 50% * LOAD value
	PWM1->_3_CMPB |= 20000 ; 								// for duty cycle 50% CMPB = 50% * LOAD value
	PWM1->_3_CTL |= (0x1U<<0) ;							// enable Generatr 3
	PWM1->ENABLE = (1U<<6)|(1U<<7) ;				// enable module M1PWM6,M1PWM7

	/************ GPIO Intialization ***************/
	SYSCTL->RCGCGPIO |= (1U<<5) ; 					// enable port F
	GPIOF->AFSEL |= M1PWM6 |M1PWM7 ; 				// alternative function selection
	GPIOF->PCTL &= ~(0xFU<<8) | ~(0xFU<<12);
	GPIOF->PCTL |= (0x5U<<8) | (0x5U<<12);
	GPIOF->DEN |= M1PWM6 | M1PWM7 ;

}



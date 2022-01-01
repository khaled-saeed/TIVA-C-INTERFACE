#include "TM4C123GH6PM.h"
#include "DC_MOTOR.h"

void DC_MOTOR_INIT(void)
{
	SYSCTL->RCGCPWM |= (1U<<1) ; 						// enable PWM module 1
	SYSCTL->RCC |= (1U<<20);					 	  	// USE DIVIDER , the system clock is the source of the clock
	SYSCTL->RCC |= (2U<<17);						    // divid by 8 , then the PWM module freq = 2 MHz
	PWM1->_3_CTL &= ~(1U<<0) ;						    // disable Generatr 3 while configuration
	PWM1->_3_CTL |= COUNT_UP ;
	PWM1->_3_GENA |=(0x3U<<2) | (0x2U<<4);				// go high at load value and low at comprator value for PWM6


	/************ GPIO Initialization ***************/
	SYSCTL->RCGCGPIO |= (1U<<5) ; 						// enable port F
	GPIOF->AFSEL |= M1PWM6  ; 							// alternative function selection
	GPIOF->PCTL &= ~(0xFU<<8) | ~(0xFU<<12);
	GPIOF->PCTL |= (0x5U<<8) | (0x5U<<12);
	GPIOF->DEN |= M1PWM6  ;
}
void MOTOR_DIRECTION(enum DIR dir)
{
	SYSCTL->RCGCGPIO |= PORTA_CLK ;
	GPIOA->DIR |= CCW_DIR | CW_DIR ;  					// connecting the direction pins to PA5 and PA6
	GPIOA->DEN |=  CCW_DIR | CW_DIR ;

	if(dir == CW)
	{
		GPIOA->DATA = CW_DIR ;
	}
	else
	{
		GPIOA->DATA = CCW_DIR ;
	}
}
void MOTOR_SPEED(enum SPEED speed)
{
	if(speed == LOW)
	{
		PWM1->_3_LOAD |= 40000 ; 								// load value = clock / needed freq =2000000/50 = 40000
		PWM1->_3_CMPA |= 4000 ; 								// for duty cycle 10% CMPA = 10% * LOAD value
		PWM1->_3_CTL |= (0x1U<<0) ;								// enable Generator 3
		PWM1->ENABLE = (1U<<6) ;								// enable module M1PWM6
	}
	else if(speed == MEDIUM)
	{
		PWM1->_3_LOAD |= 40000 ; 								// load value = clock / needed freq =2000000/50 = 40000
		PWM1->_3_CMPA |= 20000 ; 								// for duty cycle 50% CMPA = 50% * LOAD value
		PWM1->_3_CTL |= (0x1U<<0) ;								// enable Generator 3
		PWM1->ENABLE = (1U<<6) ;								// enable module M1PWM6,M1PWM7
	}
	else
	{
		PWM1->_3_LOAD |= 40000 ; 								// load value = clock / needed freq =2000000/50 = 40000
		PWM1->_3_CMPA |= 36000 ; 								// for duty cycle 90% CMPA = 90% * LOAD value
		PWM1->_3_CTL |= (0x1U<<0) ;								// enable Generator 3
		PWM1->ENABLE = (1U<<6) ;								// enable module M1PWM6
	}

}

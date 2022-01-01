#include "TM4C123.h"                    // Device header
#include "BLUETOOTH.h"
#include "timers.h"
/**************** BLUETOOTH MODULE  **********************/

void HC05_INIT(void)
{
		/*************** UART CONF ************/
#if POLLING
	SYSCTL->RCGCUART |= UART5_CLK ;
	SYSCTL->RCGCGPIO |= PORTE_CLK ;
	UART5->CTL &= ~(1U<<0) ; 									// disable uart for configuration
	UART5->IBRD |= 104 	;										//16 MHz / 16* baudrate = 16000000/(16*9600) = 104.167 , IBRD = 104
	UART5->FBRD |= 11 	;										// (0.167 * 64 +0.5 ) = 11
	UART5->LCRH |= WORD_8 ; 									// size of the word
	UART5->CC &= ~(1U<<0) ; 									// clock config system clock 16 MHz
	UART5->CTL |= (1U<<0) | (3U<<8) ;							// enable UART1 , RX ,Tx

#endif
#if INTERRUPT
	SYSCTL->RCGCUART |= UART1_CLK ;
	UART1->CTL &= ~(1U<<0) ;
	UART1->IBRD |= 104 	;									//16 MHz / 16* baudrate = 16000000/(16*9600) = 104.167 , IBRD = 104
	UART1->FBRD |= 11 	;									// (0.167 * 64 +0.5 ) = 11
	UART1->LCRH |= WORD_8 ; 								// parameters for the frame
	UART1->CC &= ~(1U<<0) ; 								// system clock 16 MHz
	UART1->ICR |= (1U<<4) ; 								// clear the interrupt RxIM
	UART1->IM |= (1U<<4) ;									//	interrupt happens when the level of data in Rx passed 7/8 RxIM
	NVIC->ISER[0] |= (1U<<6) ; 								// enable interrupt for uart1
#endif
	/************** GPIO CONF *************/
		GPIOE->AFSEL |= U5Rx | U5Tx ;
		GPIOE->PCTL |= (0x01<<16) | (0x01<<20) ;
		GPIOE->DEN |= U5Rx |U5Tx  ;
}

void BLUETOOT_WRITE(char ch)
{
		while((UART5->FR &(1U<<5)) == 1) ; 					// while the Transmitter FIFO is not FULL
		UART5->DR =  ch ;
}
void BLUETOOTH_WRITE_STRING (char * str)
{
		int i;
	for(i = 0 ; str[i] != '\0' ; i++)
	{
		BLUETOOT_WRITE(str[i]);
		DELAY_TIMER_MILLIS(10);

	}
}
char BLUETOOTH_READ(void)
{
	char data ;
		while((UART5->FR &(1U<<4)) == 1 ) ; 				// while the reciver FIFO is Empty
		data = (char)UART5->DR ;
		return data ;
}


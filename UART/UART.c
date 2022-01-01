#include "TM4C123.h"                    // Device header
#include "UART.h"
#include "lights.h"

/*!UART0_INIT
	@breif configuring the UART0 to a baudrate of 9600
	No parity
	No FIFOs
	8-bit Word
	System Clock
*/

void UART0_INIT(void)
{
	/*************** UART CONF ************/
#if POLLING
	SYSCTL->RCGCUART |= UART0_CLK ;
	SYSCTL->RCGCGPIO |= PORTA_CLK ;
	UART0->CTL &= ~(1U<<0) ; 									// disable uart for configuration
	UART0->IBRD |= 104 	;										//16 MHz / 16* baudrate = 16000000/(16*9600) = 104.167 , IBRD = 104
	UART0->FBRD |= 11 	;										// (0.167 * 64 +0.5 ) = 11
	UART0->LCRH |= WORD_8 ; 									// size of the word
	UART0->CC &= ~(1U<<0) ; 									// clock config system clock 16 MHz
	UART0->CTL |= (1U<<0) | (3U<<8) ;							// enable UART0 , RX ,Tx

#endif
#if INTERRUPT
	SYSCTL->RCGCUART |= UART0_CLK ;
	UART0->CTL &= ~(1U<<0) ;
	UART0->IBRD |= 104 	;										//16 MHz / 16* baudrate = 16000000/(16*9600) = 104.167 , IBRD = 104
	UART0->FBRD |= 11 	;										// (0.167 * 64 +0.5 ) = 11
	UART0->LCRH |= WORD_8 ; 									// parmeters for the frame
	UART0->CC &= ~(1U<<0) ; 									// system clock 16 MHz
	UART0->ICR |= (1U<<4) ; 									// clear the interrupt RxIM
	UART0->IM |= (1U<<4) ;										//	interrupt happens when the level of data in Rx passed 7/8 RxIM
	NVIC->ISER[0] |= (1U<<5) ; 									// enable interrupt for uart0
#endif
	/************** GPIO CONF *************/
		GPIOA->AFSEL |= U0Rx | U0Tx ;
		GPIOA->PCTL |= (0x01<<0) | (0x01<<4) ;
		GPIOA->DEN |= U0Rx |U0Tx  ;
}

/************** POLLING METHOD ***************/

void SEND_CHAR_U0(char ch)
{
	while((UART0->FR &(1U<<5)) != 0) ;
	UART0->DR =  ch ;
}
void SEND_STRING_U0 (char * str)
{
	int i;
	for(i = 0 ; str[i] != '\0' ; i++)
	{
		SEND_CHAR_U0(str[i]);
	}
}
char RECIEVE_CHAR_U0(void)
{
	char data ;
		while((UART0->FR &(1U<<4)) != 0) ;
		data = (char)UART0->DR ;
		return data ;
}
/**************** UART 1 **********************/

void UART1_INIT(void)
{
		/*************** UART CONF ************/
#if POLLING
	SYSCTL->RCGCUART |= UART1_CLK ;
	SYSCTL->RCGCGPIO |= PORTB_CLK ;
	UART1->CTL &= ~(1U<<0) ; 									// disable uart for configuration
	UART1->IBRD |= 104 	;										//16 MHz / 16* baudrate = 16000000/(16*9600) = 104.167 , IBRD = 104
	UART1->FBRD |= 11 	;										// (0.167 * 64 +0.5 ) = 11
	UART1->LCRH |= WORD_8 ; 									// size of the word
	UART1->CC &= ~(1U<<0) ; 									// clock config system clock 16 MHz
	UART1->CTL |= (1U<<0) | (3U<<8) ;							// enable UART1 , RX ,Tx

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
		GPIOB->AFSEL |= U1Rx | U1Tx ;
		GPIOB->PCTL |= (0x01<<0) | (0x01<<4) ;
		GPIOB->DEN |= U1Rx |U1Tx  ;
}

void SEND_CHAR_U1(char ch)
{
		while((UART1->FR &(1U<<5)) == 1) ; 					// while the Transmitter FIFO is not FULL
		UART1->DR =  ch ;
}
void SEND_STRING_U1 (char * str)
{
		int i;
	for(i = 0 ; str[i] != '\0' ; i++)
	{
		SEND_CHAR_U1(str[i]);
	}
}
char RECIEVE_CHAR_U1(void)
{
	char data ;
		while((UART1->FR &(1U<<4)) == 1 ) ; 				// while the receiver FIFO is Empty
		data = (char)UART1->DR ;
		return data ;
}

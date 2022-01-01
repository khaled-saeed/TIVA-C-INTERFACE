#ifndef __UART_H__
#define __UART_H__



/*********** UART0 **************/
void UART0_INIT(void);
void SEND_CHAR_U0(char ch);
void SEND_STRING_U0 (char * str);
char RECIEVE_CHAR_U0(void) ; 

#define UART0_CLK 				(1U<<0) 
#define U0Rx							(1U<<0)
#define U0Tx 							(1U<<1)
#define PORTA_CLK 				(1U<<0) 

/*********** UART1 **************/
void UART1_INIT(void);
void SEND_CHAR_U1(char ch);
void SEND_STRING_U1 (char * str);
char RECIEVE_CHAR_U1(void) ; 

#define UART1_CLK 				(1U<<1) 
#define U1Rx							(1U<<0) //PB0
#define U1Tx 							(1U<<1)	//PB1
#define PORTB_CLK 				(1U<<1) 


#endif //__UART_H__

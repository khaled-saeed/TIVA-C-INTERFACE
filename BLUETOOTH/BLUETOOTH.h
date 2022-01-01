#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

/*********** BLUETOOTH MODULE **************/
void HC05_INIT(void);
void BLUETOOT_WRITE(char ch);
void BLUETOOTH_WRITE_STRING (char * str);
char BLUETOOTH_READ(void) ;

#define UART5_CLK 				(1U<<5)
#define U5Rx					(1U<<4) //PB0
#define U5Tx 					(1U<<5)	//PB1
#define PORTE_CLK 				(1U<<4)


#define WORD_8					(3U<<5)
#define FIFO_EN					(1U<<4)
#define POLLING					1
#define INTERRUPT 				0
#endif //__BLUETOOTH_H__

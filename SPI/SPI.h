#ifndef __ISP_H__
#define __ISP_H__

void SSI2_INIT(void) ; 
void SSI2_MASTER_WRITE(unsigned int data ) ; 
unsigned int SSI2_MASTER_RECIEVE(void) ; 
#define SSI2_CLK	(1U<<2) 
#define PORTB_CLK (1U<<1) 
#define SSI2CLK		(1U<<4)
#define SSI2Fss		(1U<<5)
#define SSI2Rx		(1U<<6)
#define SSI2Tx		(1U<<7)
#define SSI_BUSY  (1U<<4)
#define SSI_TRANSMIT_FIFO_NOT_FULL (1U<<1)
#define SSI_RECIEVER_FIFO_FULL	(1U<<3)
#endif //__ISP_H__

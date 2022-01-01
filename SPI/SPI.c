#include "TM4C123.h"                    // Device header
#include "SPI.h"


/*!
@beirf SSI0_INIT : initialize and configure SSI0 SS
				SSI2CLK = PB4 , SSI2Fss = PB5 , SSI2Rx = PB6  , SSI2Tx = PB7
				*/
void SSI2_INIT(void)
{
	SYSCTL->RCGCSSI |= SSI2_CLK ; 										// enable clock for SSI2
	SYSCTL->RCGCGPIO |= PORTB_CLK ; 									// enable clock for PORTB
	GPIOB->DEN |= SSI2Fss |  SSI2CLK | SSI2Tx|SSI2Rx ;	  				// enable digital functionality for the pins
	GPIOB->AFSEL |= SSI2Fss |  SSI2CLK | SSI2Tx |SSI2Rx ;				// enable alternative function for the pins
	GPIOB->AMSEL &= ~(SSI2CLK | SSI2Fss) ; 								// disable analog function for the pins
	GPIOB->PCTL &= ~(0xFFFF0000U) ; 											// select SSI2 as the alternative function
	GPIOB->PCTL |= 0x22220000 ;
	GPIOB->DATA |= SSI2Fss ; 											// make the slave selection high

	SSI2->CR1 &= ~(1U<<1) ; 											// disable SSI
	SSI2->CR1 &= ~(1U<<2) ;												// select master
	SSI2->CC  = 0x0	  		; 											// system clock
	SSI2->CR0 |= 7 ; 													// for 8 bit data
	SSI2->CPSR |= 4;													// SSI0 clk = 16000000 / 4 = 4000000 Hz
	SSI2->CR1 |= 0x02	;												// enable SSI2

}
void SSI2_MASTER_WRITE(unsigned int data )
{
	GPIOB->DATA &= ~ SSI2Fss ; 										// start the transmission by sending 0 to the slave selection
	while((SSI2->SR &SSI_TRANSMIT_FIFO_NOT_FULL)==0) ;  			// keep looping while the transmission FIFO is full CAN'T WRITE ANYTHING TO IT
	SSI2->DR |= data ; 												// send the data
	while(SSI2->SR & SSI_BUSY) ; 									// wait until the trnmission finishes
	GPIOB->DATA |= SSI2Fss ; 										// end the trnsmission
}

unsigned int SSI2_MASTER_RECIEVE(void)
{
	unsigned int data ;
	GPIOB->DATA &= ~(SSI2Fss) ; 											 // START TRANSMISSION
	while((SSI2->SR & SSI_RECIEVER_FIFO_FULL) == 0) ;						 // KEEP LOOPING AS THE RECIEVER FIFO IS NT FULL NOTHING YET TO READ
	data = SSI2->DR ;
	while (SSI2->SR &SSI_BUSY) ; 											 // CHECK THE BUS THAT THE DATA IS RECIEVED
	GPIOB->DATA |= SSI2Fss ; 											   	 // END TRANSMISION
	return data  ;

}

#include "TM4C123.h"                    // Device header
#include "I2C.h"
#include <stdlib.h>


int I2C1_Wait_Until_done(void)
{
	while(I2C1->MCS & CONT_BUSY_RO) ; 														// wait while busy bit is set
	return I2C1->MCS &(SEND_ERROR_RO|DATA_ACK_RO|ADDRESS_ACK_RO) ; // check for error after sending or data is not acknowlaged or address is not acknowlaged 1 there is an error . 0 there is no error

}


void I2C1_INIT(void)
{

	SYSCTL->RCGCI2C |= I2C_1 ; 									// ENABLE THE I2C MODULE BY SETTING THE CLOCK FOR IT
	SYSCTL->RCGCGPIO |=  PORTA ; 								// ENABLE THE CROSPONDING GPIO PORT
	GPIOA->DEN |= I2C1_SDA | I2C1_SCL ; 						// ENABLE DIGITAL FUNCTION FOR THE BITS USED FR SDA AND SCL
	GPIOA->AFSEL |= I2C1_SDA | I2C1_SCL ; 				  		// CHOOSE THE ALTERNATIVE FUNCTION FOR THE BITS
	GPIOA->PCTL &= ~(0xFF000000) ;
	GPIOA->PCTL |= (0x33000000) ; 								// SELECT THE I2C FUNCTIONS
	GPIOA->ODR |=I2C1_SDA ; 									// I2C DATA BUS MUST BE OPEN DRAIN FOR THE DEVICES TO KNOW WHEATHER THE BUS IS USED OR NOT
	I2C1->MCR |= (1U<<4) ; 										// MASTER FUNCTION ENABLED
	I2C1->MTPR |= 7 ;											// TPR = (16MHz/(2*(6+4)*SCL_CLK))-1; with SCL_CLK = 100 KHz
}

/*!I2C1_Write_Multible
	@brief function recieves the data and the slave address and the memory address of the salve and the no of bytes to be sent
*/
int I2C1_Write_Multible(unsigned char * data , unsigned int slave_add ,unsigned int slave_memory_add, unsigned long no_bytes )
{
	int error ;
	if(no_bytes <= 0)															// nothing to send
	{
		return (-1) ;
	}
																								// we have something to send
														// initiate the connection by sending the slave address and the slave memory address
		I2C1->MSA |= (slave_add <<1)  ; 				// send the slave address with transmit order
		I2C1->MDR |= slave_memory_add ;
		I2C1->MCS |= ENABLE_WO |GEN_START_WO ;			// enable I2C1 and send start condition
		error = I2C1_Wait_Until_done() ;				// check if any error occurs or acknowlages not recievd
		if(error)
		{
			return error 		; 						// if there is an error return error
		}
														// sending of data
		while(no_bytes > 1)
		{
			no_bytes-- ;
			I2C1->MDR |= *data++ ; 						// send the current data and go to the next data
			I2C1->MCS |= ENABLE_WO ;
			error = I2C1_Wait_Until_done() ; 			// check if any error occurs or acknowlages not recievd
			if(error)
			{
				return error 		;					// if there is an error return error
			}
		}
														// ending the transmission
		I2C1->MDR |= *data++ ;
		I2C1->MCS |= ENABLE_WO | GEN_STOP_WO ;
		error = I2C1_Wait_Until_done() ; 				// check if any error occurs or acknowlages not recievd
		while(I2C1->MCS & BUS_BUSY_RO);
		if(error)
			{
				return error 		; 					// if there is an error return error
			}
		return 0 ;

}
int I2C1_Recieve_Multible ( unsigned char * data ,unsigned int slave_add ,unsigned int slave_memory_add,unsigned long no_bytes )
{
	int error  ;
	if(no_bytes <= 0 )
	{
		return -1 ;
	}
	else
	{
														// initiate the transmission
		I2C1->MSA |= (slave_add<<1) ;
		I2C1->MDR |= slave_memory_add ;
		I2C1->MCS |= ENABLE_WO | GEN_START_WO ;
		error = I2C1_Wait_Until_done();					// check for error
		if(error)
		{
			return error ;
		}
														//Data receiving
		while(no_bytes > 1)
		{
			I2C1->MSA |= (slave_add<<1) | RECIEVE ;
			*data++ = (unsigned char) I2C1->MDR ;
			I2C1->MCS |= ENABLE_WO |Rec_ACK_WO ;
			no_bytes-- ;
			error = I2C1_Wait_Until_done() ;
			if(error)
			{
				return error;
			}
		}
														// ending transmission
		*data++ =(unsigned char) I2C1->MDR ;
		I2C1->MCS |= ENABLE_WO | GEN_STOP_WO ;
		while(I2C1->MCS &BUS_BUSY_RO);
		error = I2C1_Wait_Until_done() ;
		if(error)
		{
			return error ;
		}
		return 0 ;
	}



}


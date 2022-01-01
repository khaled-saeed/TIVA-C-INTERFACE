#ifndef __I2C_H__
#define __I2C_H__

#define I2C_0 						(1U<<0)
#define I2C_1 						(1U<<1)
#define PORTB						(1U<<1)
#define PORTA						(1U<<0)
#define I2C0_SDA 					(1U<<2)
#define I2C0_SCL					(1U<<3)
#define I2C1_SDA					(1U<<7)  //PA7
#define I2C1_SCL					(1U<<6)	 //pA6
#define DATA_ACK_RO					(1U<<3)
#define ADDRESS_ACK_RO				(1U<<2)
#define SEND_ERROR_RO				(1U<<1)
#define CONT_BUSY_RO				(1U<<0)
#define BUS_BUSY_RO					(1U<<6)
#define ENABLE_WO					(1U<<0)
#define GEN_START_WO				(1U<<1)
#define GEN_STOP_WO					(1U<<2)
#define Rec_ACK_WO					(1U<<3)
#define RECIEVE 					(1U<<0)
#define TRANSMIT					(0U<<0)

void I2C1_INIT(void) ;
int I2C1_Write_Multible(unsigned char * data , unsigned int slave_add ,unsigned int slave_memory_add, unsigned long no_bytes);
int I2C1_Recieve_Multible ( unsigned char * data ,unsigned int slave_add ,unsigned int slave_memory_add,unsigned long no_bytes );
#endif //__I2C_H__

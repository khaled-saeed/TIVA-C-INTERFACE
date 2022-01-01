#include "TM4C123.h"                    // Device header
#include "LCD.h"
#include "Delay.h"

void LCD_INIT(void)
{
	SYSCTL->RCGCGPIO |= PORTB_CLK ;
	GPIOB->DIR |= 0xFF ; 				// all pins are output
	GPIOB->DEN |= 0xFF ; 				// enable digital function
	LCD_CMD(LCD_4BIT_MODE) ;
	LCD_CMD(CLEAR_DISP) ;
	LCD_CMD(CURSOR_BLINKS) ;

}
void LCD_WRTIE(unsigned char data , unsigned char commands) // first argument is for data and commands , 2nd argument is for  R/W,EN,RS
{

		data &= 0xF0;      		 			/* Extract upper nibble for data */
    commands &= 0x0F;    					/* Extract lower nibble for control */
    GPIOB->DATA = data | commands;      	 /* Set RS and R/W to zero for write operation */
    GPIOB->DATA = data | commands | LCD_EN;  /* Provide Pulse to Enable pin to perform write operation */
    Delay_Micro(100);
    GPIOB->DATA = data; 					 /*Send data */
    GPIOB->DATA = 0; 						 /* stop writing data to LCD */

}

void LCD_CMD(unsigned char CMD)
{
		/* we need to send the command in two peices upper half and lower half*/
		LCD_WRTIE(CMD &0xF0  , LCS_WRTIE_COMMAND ) ;
		Delay_MS(10) ;
		LCD_WRTIE((unsigned char)(CMD<<4) , LCS_WRTIE_COMMAND ) ;
		Delay_MS(10) ;
}

void LCD_WRITE_CHAR(unsigned char ch )
{
	LCD_WRTIE(ch & 0xF0 ,LCD_WRITE_DATA) ;
	Delay_MS(10);
	LCD_WRTIE((unsigned char)(ch<<4) ,LCD_WRITE_DATA) ;
	Delay_MS(2);
}
void LCD_WRITE_STRING(unsigned char * str )
{
	int i = 0 ;
	while(str[i] != '\0')
	{
		LCD_WRITE_CHAR(str[i]) ;
		i++;
	}

}

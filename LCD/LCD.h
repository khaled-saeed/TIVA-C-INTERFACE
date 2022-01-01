#ifndef __LCD_H__
#define __LCD_H__
/************ CONNECTIONS ************/
/*
1-VSS -> to Ground 
2-VDD	-> to 5 V
3-VE -> the output of 10K potontiometer  // controls the contrast of the LCD 
4-REGISTER SELECT -> to PB0 		// when set we can write data to LCD and when cleared we write commands 
5-READ/WRITE -> to PB1 		// when high we can read from LCD , when low we can write to the LCD 
6-ENABLE -> PB2 					// enable / disable LCD 
// those 8 bits are used to send data 
7-DATA PIN (0:3) -> not connected coz we're using 4 bit mode 
8-DATA PIN 4 -> to PB4
9-DATA PIN 5 -> to PB5
10-DATA PIN 6 -> to PB6
11-DATA PIN 7 -> to PB7
// those 2 bits provide the backlight 
12-LED POSITIVE -> 5V 
13-LED NEGATIVE -> ground 
*/

/************* LCD COMMANDS **********/ 

#define CLEAR_DISP 								 0x01 
#define RETURN_HOME								 0x02
#define SHIFT_DISP_RIGHT				   0x1C
#define SHIFT_DISP_LEFT					   0x18
#define CURSOR_BLINKS							 0x0F
#define DISP_ON									 	 0x0C
#define DISP_OFF									 0x08
#define CURSOR_TO_ROW1	 					 0x80
#define CURSOR_TO_ROW2	 					 0xC0
#define LCD_4BIT_MODE 						 0x28
#define LCD_8BIT_MODE							 0x38

#define PORTB_CLK					(1U<<1) 
#define LCD_EN						(1U<<2)
#define LCD_READ					(1U<<1)
#define LCD_WRITE_DATA		(1U<<0)
#define LCS_WRTIE_COMMAND	(0U<<0) 


/************* 4 BIT MODE ****************/ 
// in 4 bit mode we need to use only 6 GPIO pins 


/************* 8 BIT MODE ****************/ 
// in 8 bit mode we need to use  10 GPIO pins 

void LCD_INIT(void) ;
void LCD_WRTIE(unsigned char data , unsigned char commands);
void LCD_CMD(unsigned char CMD) ;
void LCD_WRITE_CHAR(unsigned char ch );
void LCD_WRITE_STRING(unsigned char * str ) ; 
#endif //__LCD_H__

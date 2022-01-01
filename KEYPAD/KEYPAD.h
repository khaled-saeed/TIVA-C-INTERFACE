#ifndef __KEYPAD_H__
#define __KEYPAD_H__

void keypad_init(void) ;
char keypad_read(void) ;

#define PORTE_CLK 				(1U<<4)
#define PORTC_CLK				(1U<<2)
#define R1						(1U<<0)
#define R2						(1U<<1)
#define R3						(1U<<2)
#define R4						(1U<<3)
#define C1						(1U<<4)
#define C2						(1U<<5)
#define C3						(1U<<6)
#define C4						(1U<<7)
#define RowSize					4
#define ColomnSize 				4



#endif //__KEYPAD_H__

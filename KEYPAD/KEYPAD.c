#include "TM4C123.h"                    // Device header
#include "KEYPAD.h"
#include "timers.h"

static unsigned char symbols[RowSize][ColomnSize] ={ {'1','2','3','/'}
													,{'4','5','6','*'}
													,{'7','8','9','-'}
													,{'C','0','=','+'}};

void keypad_init(void)
{
	SYSCTL->RCGCGPIO |= PORTC_CLK | PORTE_CLK ;
	GPIOC->DEN |= C1 | C2 |C3 | C4 ;
	GPIOC->DIR|= C1 | C2 |C3 | C4 ; 				// colomns as output
	GPIOC->CR |= 0xF0 ;
	GPIOE->DIR &= ~(R1 | R2 | R3 | R4) ; 			// rows as input
	GPIOE->PDR |= R1 | R2 | R3 | R4 ;				// when i press the button we read high
	GPIOE->DEN |= R1 | R2 | R3 | R4 ;
	GPIOE->CR |= 0x0F ;
}

char keypad_read(void)
{
	unsigned int c, r , i , j  ;
	while(1)
	{
		j = 0 	;
		for(c = 0x10 ; c<= 0x80 ;c = (c<<1),	j++)
		{
			GPIOC->DATA = c ;
			i = 0 ;
			for(r = 0x01 ; r <= 0x08 ; r = (r<<1),i++ )
			{
				if((GPIOE->DATA & r))
				{
					return symbols[i][j] ;
				}
			}
		}
	}
}

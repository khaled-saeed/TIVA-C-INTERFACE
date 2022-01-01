#include "TM4C123.h"                    // Device header
#include "ULTRASONIC.h"
#include "timers.h"

unsigned long ULTRASONIC_DISTANCE(void)
{
	 unsigned int lastEdge, thisEdge;

	  /* Given 10us trigger pulse */
	  GPIOB->DATA &= ~(1U<<4); 			/* make trigger  pin high */
	  DELAY_TIMER_MICROS(10); 			/*10 seconds delay */
	  GPIOB->DATA |= (1<<4); 			/* make trigger  pin high */
	  DELAY_TIMER_MICROS(10); 			/*10 seconds delay */
	  GPIOB->DATA &= ~(1U<<4); 			/* make trigger  pin low */

    TIMER1->ICR = 4;            	  	/* clear timer0A capture flag */
    while((TIMER1->RIS & 4) == 0) ;   	/* wait till captured */
	  if(GPIOB->DATA & (1<<4))	    	/*check if rising edge occurs */
		{
			lastEdge = TIMER1->TAR;     			/* save the timestamp */
							/* detect falling edge */
			TIMER1->ICR = 4;            			/* clear timer0A capture flag */
			while((TIMER1->RIS & 4) == 0) ;   		/* wait till captured */
			thisEdge = TIMER1->TAR;     			/* save the timestamp */
				return ((thisEdge - lastEdge)* 10625)/16000000; /* return the time difference */
		}
}

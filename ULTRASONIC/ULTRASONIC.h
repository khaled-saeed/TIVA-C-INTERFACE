#ifndef	__ULTRASONIC_H__
#define __ULTRASONIC_H__

#define TRIG	(1U<<5)		// PB5
#define ECHO 	(1U<<4)		//PB4, TIMER1 
unsigned long ULTRASONIC_DISTANCE(void) ; 
#endif //__ULTRASONIC_H__

#ifndef __PWM_H__
#define __PWM_H__


/************* PWM MODE **************/ 

#define TIMER3_CLK 					(1U<<3)
#define PWM_CLK 						(1U<<5)
#define PWM_MODE 						(1U<<3)
#define M0PWM0							(1U<<6) 
#define M0PWM1							(1U<<7) 
#define COUNT_UP						(1U<<1)
#define M1PWM6							(1U<<2)
#define M1PWM7							(1U<<3)

void PWM0G0_MODE_INIT(void) ; 	

void PWM1G3_MODE_INIT(void) ; 

#endif //__PWM_H__

#ifndef __INTERRUTS_H__
#define __INTERRUTS_H__

#define PORTF_CLK (1U<<5) 
#define PORTF_NVIC_INT (1U<<30)
#define SW1 (1U<<0) 
#define SW2 (1U<<4)
#define LOCK_KEY 0x4C4F434B

#define TIMER0_CLK (1U<<0)  
#define UP_COUNT (1U<<4)
#define PERIODIC_MODE (1U<<1) 
#define TIME_OUT_INT (1U<<0) 
#define NVIC_TIMER0A (1U<<19) 


void PORTF_INT_INIT(void);

void TIMER0A_INT_INIT(void) ; 

#endif //__INTERRUTS_H__

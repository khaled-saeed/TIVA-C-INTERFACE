#ifndef __TIMERS_H__
#define __TIMERS_H__

#define CAPTURING_MODE 				(3U<<0)
#define TIME_COUNT 					(1U<<2)
#define COUNT_UP 					(1U<<4)
#define COUNT_DOWN 				  	(0U<<4)
#define BOTH_EDGES 					(3U<<2)
#define PORTB_CLK 					(1U<<1)
#define POSTIVE_EDGE 				(0U<<2)
#define TIME_OUT_INT 				(1U<<0)
#define EVENT_CAPTURE_INT 			(1U<<2)
#define TIMER_EN					(1U<<0)
/************* TIME CAPTURING MODE **********/
#define TIMER1_CLK 					(1U<<1)
void Input_Edge_Time_Mode(void); 	// timer1

/************* COUNT CAPTURING MODE **********/

#define TIMER2_CLK 					(1U<<2)
void Input_Edge_Count_Mode(void); 	// timer2

/************* PERIODIC MODE **************/
#define TIMER0_CLK 					(1U<<0)
#define TIMER3_CLK					(1U<<3)
#define PERIDIC_MODE				(1U<<1)
#define TIMEOUT_FLAG				(1U<<0)

void TIMER0_PERIODIC_MODE_MICRO(void) ;
void TIMER3_PERIODIC_MODE_MILLIS(void) ;
void DELAY_TIMER_MICROS(unsigned long micros);
void DELAY_TIMER_MILLIS(unsigned long MS);

#endif //__TIMERS_H__



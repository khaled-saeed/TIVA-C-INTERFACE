#ifndef __DC_MOTOR_H__
#define __DC_MOTOR_H__
#define COUNT_UP						(1U<<1)
#define M1PWM6							(1U<<2)
#define PORTA_CLK 						(1U<<0)
#define CW_DIR							(1U<<5)
#define CCW_DIR							(1U<<6)

enum DIR{CW,CCW};
enum SPEED{LOW,MEDIUM,HIGH};

void DC_MOTOR_INIT(void) ;
void MOTOR_DIRECTION(enum DIR) ;
void MOTOR_SPEED(enum SPEED);
#endif //__DC_MOTOR_H__

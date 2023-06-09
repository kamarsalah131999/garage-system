/*
 * CFile1.c
 *
 * Created: 6/9/2023 4:10:59 AM
 *  Author: kamar
 */ 

#include <avr/io.h>
#include "macros.h"


void Timer1_Fast_pwmA(double value)
{
	/* set OC1A as outpiu pin */
	SET_BIT(DDRD,5);
	
	/*select Fast PWM (14 mode)*/
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	/*load value in OCR1 and ICR1*/
	OCR1A =value*1000;                                             // where value is the ON period
	ICR1= 19999;                                                     // top value 
	
	/* select timer clock , No prescalring */
	SET_BIT(TCCR1B,CS10);
	
	/* clear OC1A on compare match , set OC1A at BOTTOM (non_inverting mode) */
	SET_BIT(TCCR1A,COM1A1);
}
	
void Timer1_Fast_pwmB(double value)
{
	/* set OC1B as outpiu pin */
	SET_BIT(DDRD,4);
	
	/*select Fast PWM (14 mode)*/
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	/*load value in OCR1 and ICR1*/
	OCR1B =value*1000;                                             // where value is the ON period
	ICR1= 19999;                                                     // top value 
	
	/* select timer clock , No prescalring */
	SET_BIT(TCCR1B,CS10);
	
	/* clear OC1A on compare match , set OC1A at BOTTOM (non_inverting mode) */
	SET_BIT(TCCR1A,COM1B1);
}
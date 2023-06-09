/*
 * garge system.c
 * 
 * Created: 6/9/2023 4:36:33 AM
 * Author : kamar
 */ 

#include <avr/io.h>
#include "LCD driver.h"
#include "Timer1.h"
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
   LCD_vinit ();
   LCD_vsend_sring ("There are 0 cars");
   LCD_vmove_cursor (2, 1);
   LCD_vsend_sring ("garage have space");
   
   signed char flag1=0, flag2=0, counter=0, IR1, IR2;
   
    while (1) 
    {
		/* open entry door */
		IR1=DIO_u8read_pin('D', 0);                                  // check if IR sensor reseved signal or not (reseved=1 , not reseved =0)
		if(IR1==1 && flag1==0 && counter<3)
		{
			counter++;
			LCD_vmove_cursor (1, 11);
			LCD_vsend_char (counter+48);
			flag1=1;
			
			if (counter==3)
			{
				LCD_vclear_screen ();
				LCD_vsend_sring ("There are 3 cars");
                LCD_vmove_cursor (2, 1);
                LCD_vsend_sring ("garag is full");
			}
			Timer1_Fast_pwmB(0.999999);                          // rotate servo motor to open the door
			_delay_ms (5000);
			Timer1_Fast_pwmB(1.499999);                          // rotate servo motor to close the door 
		}
		
		else if (IR1=0)
		{ 
			flag1=0;
		}
		
		
		/* open exit door */
		IR2= DIO_u8read_pin('D', 1);
		if (IR2==1 && flag2==0 && counter>0)
		{
			counter--;
			LCD_vmove_cursor (1, 11);
			LCD_vsend_char (counter+48);
			flag2=1;
			
			LCD_vclear_screen ();
			LCD_vsend_sring ("There are ");
			LCD_vsend_char (counter+48);
			LCD_vsend_sring (" cars ");
            LCD_vmove_cursor (2, 1);
            LCD_vsend_sring ("garage have space");
			
			
			Timer1_Fast_pwmA(0.999999);                          // rotate servo motor to open the door
			_delay_ms (5000);
			Timer1_Fast_pwmA(1.499999);                          // rotate servo motor to close the door 
		}	
			
		else if (IR2=0)
		{
			flag2=0;
		}
				
    }
}


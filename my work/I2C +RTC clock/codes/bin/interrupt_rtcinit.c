/*
 * GccApplication1.c
 *
 * Created: 12/31/2016 6:56:40 PM
 * Author : Tanmay_2
 */ 

#define F_CPU 1000000UL // 1 MHz
#include <avr/io.h>
#include <avr/interrupt.h>
 volatile uint8_t ctr0_ovrflw;



 void timer0_init()
 {
	 TCCR1B |= (1<<CS10) | (1<<CS11);
	 TCNT1 =0;
	 ctr0_ovrflw=0;
 }
int main(void)
{
    DDRB = 0xFF;
	timer0_init();
	float sec=1;
	int sett= 15626*sec;
    while (1) 
    {
		sett= 15626*sec;
	   if(TCNT1 >= sett)
	  {
		   PORTB ^=(1<<0);
		   TCNT1=0;
		   if(sec<0.5)
		    sec-=0.002f;
			else
		   sec-=0.05;	
	  }
    }
}


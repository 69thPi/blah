/*
 * IR_ADC.c
 *
 * Created: 7/8/2017 6:04:19 PM
 * Author : Tanmay_2
 */ 

#define F_CPU 1000000UL
#define Led_On(PORT,PIN) PORT |= 1<<PIN;
#define Led_Off(PORT,PIN) PORT &= ~(1<<PIN);

#include <avr/io.h>


int main(void)
{
    unsigned int ADC_val;
	DDRB |=0x01;  // pinb0 set as output
	PORTB &=0x00; //output low
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0); //enable ADC and set  division factor as 32 (101)
	ADMUX =0b01000001;
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		ADC_val=ADC;
		if(ADC_val < 100)
			{
				Led_Off(PORTB,0);
			}
			else
			{
			    Led_On(PORTB,0);
			}
		  
	}
	
}


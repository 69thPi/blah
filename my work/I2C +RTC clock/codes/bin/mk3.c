/*
 * mark3
 * countdown.c
 *
 * Created: 2/8/2016 3:23:25 PM
 * Author : Tanmay
 * function:IT COUNTS DOWN FROM DESIRED INPUT NMBER IN THE MAIN FN.
 */ 

#include<avr/io.h>
#include<util/delay.h>


int val[6]={0,0,0,0,0,0};//h1,h1,m1,m1,s1,s1
long int num=0;

void display(int n)//big SSD display thru ULN 2003A
{
	switch(n)
	{
		case 0:PORTD=0b10000000; break;
		case 1:PORTD=0b11111001; break;
		case 2:PORTD=0b10100100; break;
		case 3:PORTD=0b10110000; break;
		case 4:PORTD=0b10011001; break;
		case 5:PORTD=0b10010010; break;
		case 6:PORTD=0b10000010; break;
		case 7:PORTD=0b11111000; break;
		case 8:PORTD=0b10000000; break;
		case 9:PORTD=0b10010000; break;
	}
}
void display_sec(int n)//small SSD direct thru D-FLIP FLOP
{
	switch(n)
	{
		case 0:PORTD=0b01111111; break;
		case 1:PORTD=0b00000110; break;
		case 2:PORTD=0b01011011; break;
		case 3:PORTD=0b01001111; break;
		case 4:PORTD=0b01100110; break;
		case 5:PORTD=0b01101101; break;
		case 6:PORTD=0b01111101; break;
		case 7:PORTD=0b00000111; break;
		case 8:PORTD=0b01111111; break;
		case 9:PORTD=0b01101111; break;
	}
}
void get_display()     ///fn that gets the values and displays
{
	for(int i=0;i<5;i++)
	{
		display_sec(val[i]);
		PORTB=1<<i;
		_delay_ms(50);
		PORTB=0<<i;
	}
	for(int i=5;i<7;i++)
	{
		display_sec(val[i]);
		PORTB=1<<i;
		_delay_ms(50);
		PORTB=0<<i;
	}
}

void counter()//size of int =4 bytes
{
	int i=5;
	while(num>0)//assigns number to val
	{
		val[i]=num%10;
		num/=10;
		i--;
	}
	num--;
}
int main()
{
	DDRD=0b11111111;//led multiplexing
	DDRB=0b11111111;//cp
	PORTD=0b01111111;//0-6 gives high
	num=100000;
	while(1)
	{
		get_display();
		counter();
		_delay_ms(1000);
	}
	
}


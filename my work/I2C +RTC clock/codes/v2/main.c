/*
 * wall_clock_final.c
 *
 * Created: 1/14/2018 2:52:24 PM
 * Author : Tanmay_2
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "rtc.h"

int digits[6] = {0,0,0,0,0,0};
long int num = 3600;

void assign_num()
{
	uint8_t hr=0,mm=0,ss=0;
	rtc_read(hr,mm,ss);
	uint8_t temp=ss;
	int dig[]={0,0,0,0,0,0};
	dig[5]=(ss & 0b00001111);
	dig[4]=(temp>>4);
	temp=mm;
	dig[3]=(mm & 0b00001111);
	dig[2]=(mm>>4);
	temp=hr;
	dig[1]=(hr & 0b00001111);
	dig[0]=(temp>>4)&0b00000011;
	//digits assigned

	int h,m,s;
	h=(digits[5]*10)+digits[4];
	m=(digits[3]*10)+digits[2];
	s=(digits[1]*10)+digits[0];
	num = s+(m*60)+(h*3600);
	//num assigned
}

void assign_digits()
{
	int ss=num%60;
	int mm= (num/60)%60;
	int hh= (num /(3600))%12;//%24 for 24 hour version
	digits[5]=ss%10;
	ss/=10;
	digits[4]=ss;
	digits[3]=mm%10;
	mm/=10;
	digits[2]=mm;
	digits[1]=hh%10;
	hh/=10;
	digits[0]=hh;
	num--;
}

void set_dgt_port(int n)//common anode
{
	switch(n)
	{
		case 0: PORTD = 0b11000000;
		break;
		case 1: PORTD = 0b11111001;
		break;
		case 2: PORTD = 0b10100100;
		break;
		case 3: PORTD = 0b10110000;
		break;
		case 4: PORTD = 0b10011001;
		break;
		case 5: PORTD = 0b10010010;
		break;
		case 6: PORTD = 0b10000010;
		break;
		case 7: PORTD = 0b11111000;
		break;
		case 8: PORTD = 0b10000000;
		break;
		case 9: PORTD = 0b10010000;
		break;
	}
}

void set_display()
{
	PORTB = 0x00;
	for(int i=0;i<6;i++)
	{
		set_dgt_port(digits[i]);//set port value
		PORTB |= 1<<i; //cp
		_delay_ms(50);
		PORTB |= 0<<i;  //cp
	}
	_delay_ms(950);
}

int main(void)
{
	DDRB |=0xff;
	DDRC |=0xff;
	DDRD |=0Xff;
	PORTB |=0xff;
	PORTC |=0x00;
	PORTD |=0x00;//initial condition all led glow;
	//EITHER/OR
	//write routiene 1st time
	//  rtc_init();
	//read routiene
	  //assign_num();//once
	//update num & assign digits & display
	while(1)
	{
		assign_digits();
		set_display();
	}
}

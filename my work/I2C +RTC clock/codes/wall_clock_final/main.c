/*
 * wall_clock_final.c
 *
 * Created: 1/14/2018 2:52:24 PM
 * Author : Tanmay_2
 */

#include <avr/io.h>
#include <util/delay.h>


#include "const.h"
#include "rtc.h"
#include "USART_32.h"




int digits[6] = {0,0,0,0,0,0};
long int num = 60;//number of seconds


void read_from_rtc()// read from RTC and assign "num"
{
	uint8_t hr=1,mm=1,ss=1;
	rtc_read(&hr,&mm,&ss);  //read from rtc
	uint16_t temp=ss;	
	int dig[]={0,0,0,0,0,0};
	dig[5]=(ss & 0b00001111);//extract first 4 bits
	dig[4]=((temp & 0xF0)>>4);		 //extract next four bits
	temp=mm;
	dig[3]=(mm & 0b00001111);//extract first 4 bits
	dig[2]=((temp & 0xF0)>>4);		 //extract next four bits
	temp=hr;
	dig[1]=(hr & 0x0F);//extract first 4 bits
	dig[0]=((temp & 0xF0)>>4)&0b00000111;		 //extract next 2 bits of the 4

	//digits assigned
	long int h,m,s;
	h=(dig[0]*10)+dig[1];	
	m=(dig[2]*10)+dig[3];
	s=(dig[4]*10)+dig[5];
 	num = s+(m*60)+(h*3600);
	//num assigned	
}

void set_display_val()
{
	int PM=0;
	int ss=num%60;
	int mm= (num/60)%60;
	if((num /(3600))>12)
	PM =1;
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
	num++;
	USART_TransmitNumber(digits[0]);
	USART_TransmitNumber(digits[1]);
	USART_Transmitchar('-');
	USART_TransmitNumber(digits[2]);
	USART_TransmitNumber(digits[3]);
	USART_Transmitchar('-');
	USART_TransmitNumber(digits[4]);
	USART_TransmitNumber(digits[5]);
		if(PM==1)
				USART_TransmitString(" PM");
		else
				USART_TransmitString(" AM");
	
	USART_Transmitchar(0x0D);
}

void set_dgt_port_small(int n)//common anode
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

void set_dgt_port_big(int n)//common anode big ssd thru ULN (common cathode)
{
	switch(n)
	{
		case 0: PORTD = 0b00111111;
		break;
		case 1: PORTD = 0b00000110;
		break;
		case 2: PORTD = 0b01011011;
		break;
		case 3: PORTD = 0b01001111;
		break;
		case 4: PORTD = 0b01100110;
		break;
		case 5: PORTD = 0b01101101;
		break;
		case 6: PORTD = 0b01111101;
		break;
		case 7: PORTD = 0b00000111;
		break;
		case 8: PORTD = 0b01111111;
		break;
		case 9: PORTD = 0b01101111;
		break;
	}
}

void display_ssd()
{
	PORTB = 0x00; // all CP low
	for(int i=0;i<4;i++)
	{
		set_dgt_port_big(digits[i]);//set port value
		PORTB |= 1<<i; //cp
		_delay_ms(10);
		PORTB |= 0<<i;  //cp
	}
	for(int i=4;i<6;i++)
	{
		set_dgt_port_small(digits[i]);//set port value
		PORTB |= 1<<i; //cp
		_delay_ms(10);
		PORTB |= 0<<i;  //cp
	}
	_delay_ms(930);
}

void normal_mode()
{
	set_display_val(); // set the display value
	display_ssd();    // display procedure
}

int main(void)
{
	DDRB |=0xff; // clock pulse port
	DDRC |=0xff; //RTC DS-1307
	DDRD |=0Xff; //multiplexing signals
     
	 // all set as output pins
    
	PORTB |=0x02; //cp high
	PORTC |=0x00; //ds1307 all low
	PORTD |=0x00;//initial condition all low;
	USART_Init(103);
	//EITHER/OR
	//write routiene 1st time
	rtc_init(); //to set up rtc
	read_from_rtc();
	
	//  mode 1: normal time display
	//  mode 2: timer setting
	//  mode 3: stopwatch
	//  mode 4: alarm

	
	int mode =1;
	while(1)
	{
		normal_mode();
	}
}

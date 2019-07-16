/*
 * DRISHTI_GateLock.c
 *
 * Created: 9/30/2018 2:31:26 PM
 * Author : Tanmay
 *
 */ 

#define F_CPU 8000000UL

#include <avr/io.h >
#include <avr/interrupt.h >
#include <util/delay.h>
#include "USART_32.h"

char ref_id[20];
int flag=0;


int main()
{
	USART_Init(51);
	sei();
	USART_InterruptEnable();

	while(1)
	{
		//USART_TransmitNumber(5);
	}
	
}

ISR (USART_RX_vect)
{
	//USART_TransmitString("0000-");
	char x;
	x = USART_Receive();
	USART_TransmitNumber(1);
}


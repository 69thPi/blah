
#define F_CPU 1000000UL
#include <avr/io.h>

#define toggle(port,pin) port ^=1<<pin

/*void prime(int n)
{
   int i,flag=1;
   for(i=2;i<n;i++)
   {
	   if(n%i==0)
	   {
		  flag=0; 
	   }
   }
   if(flag==1)
     toggle(PORTB,1);
     
}
*/
int prime(int n)
{
	int i,flag=1;
	for(i=2;i<n;i++)
	{
		if(n%i==0)
		{
			flag=0;
		}
	}
	if(flag==1)
	return 1;
	else
	return 0;
	
}
int main(void)
{
	DDRB = 0xFE;
	PORTB = 0x02;
	int n=0;
	while(1)
	{
		if(bit_is_set(PINB,0))
		{
			if(prime(++n))
			 PORTB = 0b00000010;
			//PORTB |=(1<<1);
			while(bit_is_set(PINB,0));
			PORTB = 0b00000000;
			
		}
		else
		continue;
		//PORTB &=(0<<1);
	}
}
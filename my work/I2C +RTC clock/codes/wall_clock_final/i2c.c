#include <avr/io.h>
#include <avr/delay.h>
#include "const.h"

#define prescaler 1 //4^prescalar bits
#define TWBR_val (((F_CPU/F_dev)-16)/2) //defines value of bit rate for TWI




void i2c_init()
{
	TWBR=0x20; //20 or 47 //32
	TWCR=0x00; //initalize TWI control register
	TWCR = 1<<TWEN;
}

int i2c_start()/// CODE::while(1){i2c_start();}
{
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //enable start,inilze.& flag regs. to set to start chnl
	while(!(TWCR & (1<<TWINT)));//wait for transmission
	if((TWSR & 0xF8) == 0x08 )  // true is write mode is set
		return 1;
	else
		return 0;
}

void i2c_stop()
{
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
}

int i2c_write(uint8_t dat)
{
	TWDR=dat;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));//wait for transmission
	//TWSR check if written if yes then return 1 else return 0;
	if(((TWSR & 0xF8) == 0x40) | (TWSR & 0xF8 == 0x28) | (TWSR & 0xF8 == 0x18))//25 for data,18 for addressR/W
	return 1;
	else
	return 0;
}

int i2c_read_ack(uint8_t *a)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) == 0x50)//check
	{
		*a=TWDR;
		return 1;
	}
	else
	return 0;
}

int i2c_read_nack(uint8_t *a)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) == 0x58)//check
	{
		*a=TWDR;
		return 1;
	}
	else
	return 0;
}

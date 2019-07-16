#define F_dev 100000UL //freq of device
#define prescaler 1 //4^prescalar bits
#define TWBR_val ((((F_CPU/F_dev)/prescaler)-16)/2) //defines value of bit rate for TWI


void i2c_init()
{
 TWBR=TWBR_val;
}

void i2c_start()/// CODE::while(1){i2c_start();}
{
  TWCR=0x00; //initalize TWI control register
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //enable start,inilze.& flag regs. to set to start chnl
  while(!(TWCR & (1<<TWINT)));//wait for transmission
  if((TWSR & 0xF8) == 0x08 )
   break;
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
 if(((TWSR & 0xF8) != 0x28) | (TWSR & 0xF8 != 0x18))//25 for data,18 for addressR/W
    return 0;
 else
    return 1;
}

int i2c_read_ack(uint8_t &a)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8) == 0x50)//check
	{
	  a=TWDR;
	  return 1;
	}
	else
		return 0;
}


int i2c_read_nack(uint8_t &a)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	a=TWDR;
	if ((TWSR & 0xF8) == 0x58)//check
		{
		  a=TWDR;
 		 return 1;
		}
	else
		return 0;
}

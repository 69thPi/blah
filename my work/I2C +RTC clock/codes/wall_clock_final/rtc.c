
#define RTC_write 0xD0 //DS1307 WRITE ID
#define RTC_read 0xD1  //DS1307 READ ID

#include "i2c.h"


void rtc_init()
{
	// time to be set
	uint8_t hr  = 0b00100011; // 24 hr format 00
	uint8_t min = 0x59;
	uint8_t sec = 0x55;  //35 sec
	uint8_t day = 0x05;
	uint8_t date= 0x10;
	uint8_t mon = 0x05;
	uint8_t yr  = 0x18;
	//
	i2c_init();
	while(!i2c_start());

	int flag=1,complete=0;
	while(!complete){
		while(flag){
			flag=i2c_write(RTC_write);//select device by sending address
			flag=i2c_write(0x00);//select register
			flag=i2c_write(sec);//send 1st register values
			flag=i2c_write(min);//send 2nd register values
			flag=i2c_write(hr);//send 3rd register values
			flag=i2c_write(day);//send 4th register values
			flag=i2c_write(date);//send 5th register values
			flag=i2c_write(mon);//send 6th register values
			flag=i2c_write(yr);//send 6th register values
			complete=1;
			flag=0;
		}
		if(complete==0)
		{
			TWCR=(1<<TWINT) | (1<<TWSTA);//restart condition
			while(!(TWCR & (1<<TWINT)));//wait for transmission
		}
	}
	i2c_stop();
}

void rtc_read(uint8_t  *hr,uint8_t *min,uint8_t *sec)//point to actual location
{
	i2c_init();
	while(!i2c_start());
	//set pointer
	i2c_write(RTC_write);
	i2c_write(0x00);
	i2c_stop();
	// pointer set to 0x00;
	i2c_start();
	//
	
	int flag=1,complete=0;
	while(!complete){
		while(flag){
			flag=i2c_write(RTC_read);//select device by sending address
			flag=i2c_read_ack(sec);//read 1st register values
			
			flag=i2c_read_ack(min);//read 2nd register values
			
			flag=i2c_read_nack(hr);//read 3rd register values
			
			complete=1;
			flag=0;
			
		}
		
		if(!complete)
		{
			TWCR=(1<<TWINT) | (1<<TWEN) |(1<<TWSTA);//restart condition
			while(!(TWCR & (1<<TWINT)));//wait for transmission
			
		}
	}
	i2c_stop();
}

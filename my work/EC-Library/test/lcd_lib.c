#include "lcd_lib.h"
//transmit data and then the positon after
//0x01 for cls and return home

//Atmega128 PORT D- data line
// PINB0 = RS //datareg //cmdreg
// PINB1 = R/W
// PINB2 = E //+-/-+ trigger

void flash()//trigger send //toggle enable
{
  control_p |=1<<e;
  asm volatile ("nop");
  asm volatile ("nop");
  //_delay_ms(2);
  control_p &=~(1<<e);
}

void busy()//check status register
{
  //if busy; toggle enable
  //set to read mode
  data_d =0;
  control_p &= ~(1<<rs);
  control_p |=  (1<<rw);
  //compare data
  //anti_flash
  //if busy then flash till busy
  while(data_p >= 0x80)
  {
    flash();
  }
  //set to write mode
  data_d=0xff;
}

void cmd(uint8_t a)//uint8_t
{
  busy();
   data_p = a;
  control_p &= ~(1<<rs);//set to write and cmd mode
  control_p &= ~(1<<rw);
   flash();
  data_p = 0;
}
int len=0;
void send_char(unsigned char b)
{
  busy();
  control_p |= (1<<rs);//set to data mode
  control_p &= ~(1<<rw);//set to write
  data_p = b;
  flash();
  data_p = 0;
  _delay_us(800);
}
void string(char *s)
{
  len=0;
  while(*s > 0)
  {
    send_char(*s++);
    len++;
    if(len == 16)
     {
       cmd(0xC0);
       len=0;
	   s--;
     }
  }
}
void Num (int value)
{
	char number[100];
	itoa(value,number,10);
	string(number);//displaying number
}

void dec_Num (double j)
{
	char number[100];
	dtostrf(j,8,2, number);
	string(number);
}

void goto_loc(int x,int y)
{
  if(y==2)
  {
    cmd(0x80 + 64 + x - 1);
    _delay_us(4500);
  }
  else if(y==1)
  {
    cmd(0x80 + x -1);
    _delay_us(4500);
  }
}

void lcd_init()
{
  control_d |= (1<<e) |(1<<rs)|(1<<rw);//PORTB set as output
  //data_d = 1;//PORTD set as output works without as first busy() is called
  ////initialsation instruction
  _delay_ms(15);
  cmd(0x38);//8bit -2 line mode
  _delay_us(4500);
  cmd(0x38);//8bit-2 line
  _delay_us(4500);
  cmd(0x38);//8bit -2 line
  _delay_us(150);
  cmd(0x01);//cls & cursor 0,0
  _delay_ms(2);
  cmd(0x0C);//display + cursor on +LCD blink off
  _delay_ms(2);
}

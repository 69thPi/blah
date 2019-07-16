#ifndef lcd_lib

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#define rs PINB0
#define rw PINB1
#define e PINB2
#define data_d DDRD       //data direction register
#define data_p PORTD      //store values
#define control_p PORTB
#define control_d DDRB

void flash(void);
void busy(void);
void cmd(uint8_t);
void send_char(unsigned char);
void string(char *);
void Num (int);
void dec_Num (double);
void lcd_init(void);
void goto_loc(int,int);

#endif

#ifndef i2c
#define i2c
#include <avr/io.h>

void i2c_init();
int i2c_start();
void i2c_stop();
int i2c_write(uint8_t dat);
int i2c_read_ack(uint8_t *a);
int i2c_read_nack(uint8_t *a);

#endif
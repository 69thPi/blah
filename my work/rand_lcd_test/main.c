/*
 * rand_test.c
 *
 * Created: 5/6/2018 5:54:44 PM
 * Author : Tanmay
 */ 

// #include <util/delay.h>
// #define F_CPU 1000000UL
// #include "lcd_lib.h"
// 
// int main(void)
// {
// 	lcd_init();
// 	//goto_loc(1,1);
// 	//string("hey you!");
// }
// 
/*
 * rand_test.c
 *
 * Created: 5/6/2018 5:54:44 PM
 * Author : Tanmay
 */ 

#include <util/delay.h>
#define F_CPU 1000000UL
#include "lcd_lib.h"

int main(void)
{
	lcd_init();
	goto_loc(1,1);
	string("Aloo World!");
}



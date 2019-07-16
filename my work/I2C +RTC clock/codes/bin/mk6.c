/*
 * mark 6
 * multiplexing1.c
 *
 * Created: 7/1/2016 1:57:27 PM
 * Author : Tanmay
 */ 

#include <avr/io.h>


long int num;
int dv[6][8];
long int disp=123456;
int val[6];
void set(int n)//common anode(+) tf. glow=0;
{
	case 0:num=11000000;
	break;
	case 1:num=11111100;
	break;
	case 2:num=10010010;
	break;
	case 3:num=10011000;
	break;
	case 4:num=10101100;
	break;
	case 5:num=10001001;
	break;
	case 6:num=10000001;
	break;
	case 7:num=11011100;
	break;
	case 8:num=10000000;
	break;
	case 9:num=10001000;
	break;
}

void play()
{
	int temp=disp;
	int t,i=5;
		while(disp>0)
		{
			t=disp%10;
			val[i]=t;
			i--;
		}
		temp-=1;
		disp=temp;
}

void map()//array value set
{
	for(int i=0;i<6;i++)
	{
		set(val[i]);
		//at this point num has to be set to each element in array
		int j=8,t;
		while(num>0)
		{
			t=num%10;
			dv[i][j]=t;
			num/=10;
			j--;
		}
	}
}

void display()
{
	//check value for each element if 0 then that pin should display 0 all else should b 1;
	//run it for all eight values;
}
int main(void)
{
    /* make a function to set an 8 digit
	   make a 2d array 6x8
	   set each array element according to the number */
	
    while (1) 
    {
    }
}


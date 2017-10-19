// c51_delay.c

#include "c51_delay.h"

// Perform delay in microseconds using Timer1
void delay_us(unsigned int dval)
{
	dval = 0xFFFF - dval; // timer counts up
	// for 12MHz clock Timer ticks every 1us (CLK_FREQ / 12)
	TMOD |= 0x10;   // Timer 1, mode 1 (16-bit)  
	TL1 = dval;     // load TL1; lower bits
	TH1 = dval>>8;	// load TH1; higher bits
	TR1 = 1;		// turn on Timer 1
	while (TF1==0);	// wait for TF1 to roll over
	TR1 = 0;		// turn off Timer 1
	TF1 = 0;		// clear TF1
}

// do delay in miliseconds
void delay_ms(unsigned int dval)
{
	while (dval--)
	{
		delay_us(1000);
	}
}

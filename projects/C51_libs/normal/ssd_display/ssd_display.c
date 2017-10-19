// ssd_display.c

#include "ssd_display.h"

// Timer0 Init
void Init_Timer0(void)
{
	TMOD |= 0x01;		// use 16bit timer	(0x02 for 8bit count)
	EA=1;          		// interrupt enable
	ET0=1;           	// timer 0 overflow interrupt enable
	TR0=1;          	// start timer
}

void InitLEDSSD(void)
{
	 Init_Timer0();
}

// Update LED SSD dynamically on Timer0 interrupt
// Timer0 overflow interrupt
void Timer0_isr(void) interrupt 1 using 1
{
    // each 400 Hz we will get interrupt
	//TH0=(65536-2500)/256;	// MSB	   
 	TH0=0xF6;  
	//TL0=(65536-2500)%256;	// LSB
   	TL0=0x3C;

	// light off previous digit
	P1 = 0xFF;
	LATCH1 = 1;
	LATCH1 = 0;
	// write data to latch for next digit select
	P1 = digit_control[current_digit];
	LATCH2 = 1;
	LATCH2 = 0;
	// write data to latch for current digit
	P1 = digit_input[digit_values[current_digit]];
	LATCH1 = 1;
	LATCH1 = 0;

	if (++current_digit >= LED_SSD_DIGITS_MAX)
	{
		current_digit = 0;
	}
}
   
// Set number to show on display on Right LSB 4 bits
void Display_LSB(unsigned int number)
{
	unsigned char i;
	for (i=0; i<4; i++)
	{
	    if (number || i==0)
		{
   			digit_values[i] = number%10;
		}
		else
		{
			 digit_values[i] = 17; // blank digit
		}
		number = number/10;
	}
}

// Set number to show on display on Left MSB 4 bits
void Display_MSB(unsigned int number)
{
	unsigned char i;
	for (i=0; i<4; i++)
	{
	    if (number || i==0)
		{
   			digit_values[i+4] = number%10;
		}
		else
		{
			 digit_values[i+4] = 17; // blank digit
		}
		number = number/10;
	}
}

// Set number to show on whole 8 digits of display
void Display_All(unsigned long number)
{
	unsigned char i;
	for (i=0; i<8; i++)
	{
	    if (number || i==0)
		{
   			digit_values[i] = number%10;
		}
		else
		{
			 digit_values[i] = 17; // blank digit
		}
		number = number/10;
	}
}

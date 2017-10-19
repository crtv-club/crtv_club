// ultrasonic_sensor.c

#include "ultrasonic_sensor.h"

// do delay in microseconds
unsigned int getPulseWidth_us(void)
{
	// for 12MHz clock Timer ticks every 1us (CLK_FREQ / 12)
	TMOD |= 0x10;   // Timer 1, mode 1 (16-bit)  
	TL1 = 0x00;     // load TL1
	TH1 = 0x00;	// load TH1
	TR1 = 1;		// turn on Timer 1
	while (S_ECHO==1 && TF1==0);   // !(S_ECHO==0 || TF1==1) // wait impulse end or wait for TF1 to roll over
	TR1 = 0;		// turn off Timer 1
	TF1 = 0;		// clear TF1
	return ((TH1 << 8) + TL1);
}

// get the distance to object from ultrasonic sensor (in cm)
unsigned int measureDistanceCm(void)
{
	unsigned int imp_duration = 0;
	unsigned int distance = 0;
	// send trigger 10us impulse 
	S_TRIG = 1;
	delay_us(10);
	S_TRIG = 0;
	// wait echo impulse
	while (S_ECHO==0); //TODO: add check later
	imp_duration = getPulseWidth_us();
	if (imp_duration > 100) // don't ask me about - that's very magic number)
	{
		 distance = imp_duration / 58;
	}
	return distance;
}

// ultrasonic_sensor.h

#ifndef _ULTRASONIC_SENSOR__H_
#define _ULTRASONIC_SENSOR__H_

#include <reg52.h>
#include <c51_delay.h>

/**
 * 	Ultrasonic sensor C51 library (HC-SR04 kit) by Shurick
 *	Provide measurement of distance to object in front of US sensor
 *	Uses Timer1 in C51 for synchronization
 *	Uses <c51_delay.h> library for trigger impulse provide.
 *	NOTE: S_TRIG and S_ECHO should be declared like sbit.
 * 	Provided Interface:
 *		unsigned int measureDistanceCm(void) : Get distance to the object in front of US sensor
 */

/// Define sensor ports in this way:
/// sbit S_TRIG=P2^0;
/// sbit S_ECHO=P2^1;
 
/// Measure ultarasonic sensor pulse responce
unsigned int getPulseWidth_us(void);

/// Get distance to the object in front of US sensor
unsigned int measureDistanceCm(void);


#endif // _ULTRASONIC_SENSOR__H_

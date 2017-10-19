// c51_sw_spi.h

#ifndef _C51_SW_SPI__H_
#define _C51_SW_SPI__H_

#include <reg52.h>

/**
 * 	C51 Software SPI library by Shurick
 *	Provide software Serial Peripheral Interface on C51 core
 *	Data exchange rate is very slow: 
 * 	for 12 MHz core clock approximately timings: SPI Clock = 76.923 kHz.
 * 	C51 Timers not used in this library.
 *	All interrupts disabled during SPI transaction, spi0_end() enable interrupts again.
 *	NOTE: SPI0_MISO, SPI0_MOSI, SPI0_SCK and SPI0_SS should be declared like sbit.
 * 	Provided Interface:
 *		void spi0_init(void) : Initialize SPI before first use
 * 		void spi0_start(void) : Start SPI packet sending - SPI0_SS pin to active
 *		void spi0_end(void) : Finish SPI packet sending - SPI0_SS pin to idle
 * 		unsigned char spi0_send(unsigned char spi_data) : Send and receive one byte via SPI
 */

/// Declare SPI connections in this way:
/// sbit SPI0_MISO=P3^2;
/// sbit SPI0_MOSI=P3^3;
/// sbit SPI0_SCK =P3^5;
/// sbit SPI0_SS  =P3^6;
 
/// Defines:
#define ENABLE_INTERRUPTS { EA = 1; }
#define DISABLE_INTERRUPTS { EA = 0; }
// defines for different SPI mode
#define SPI_SS_ACTIVE 0
#define SPI_SS_IDLE 1
#define SPI_CLK_ACTIVE 1
#define SPI_CLK_IDLE 0
//#define SPI_LSB 0
//#define SPI_MSB 1

/// Initialize SPI 
void spi0_init(void);

/// Start SPI packet sending - SPI0_SS pin to active
void spi0_start(void);

/// Finish SPI packet sending - SPI0_SS pin to idle
void spi0_end(void);

/// Send and receive one byte via SPI
unsigned char spi0_send(unsigned char spi_data);

// = = = = = = = = = = = = = = = = = = = = = = D E F I N I T I O N = = = = = = = = = = = = = = = = = = = = = =

void spi0_init(void)
{
	// Initialize here...
}

// set SS bit to active 
void spi0_start(void)
{
	// Prevent Interrupt execute during transmission
	DISABLE_INTERRUPTS
	// Select SPI Slave for transmission
	SPI0_SS	= SPI_SS_ACTIVE;
}

// reset SS bit to idle 
void spi0_end(void)
{
	// Disable SPI Slave after transmission
	SPI0_SS	= SPI_SS_IDLE;
	ENABLE_INTERRUPTS
}

// SPI Send input data via MOSI	and read data from MISO
// for 12 MHz approximately timings:
// SPI Clock = 	76.923 kHz	
unsigned char spi0_send(unsigned char spi_data)
{
	// _nop_ ();    // delay 1/12 us
	
	// take 13 cycles * 12 clocks = 156 clocks total
	// SPI Clock = 	76.923 kHz for 12MHz
	unsigned char i = 8; // 8 bit per time	 
	while (i)
	{
		// set idle clock signal
		SPI0_SCK = SPI_CLK_IDLE;
	    // Set output bit
		if (spi_data & 0x80)
		{
			SPI0_MOSI = 1;
		}
		else
		{
			SPI0_MOSI = 0;
		}	
		// shift current bit
		spi_data <<= 1;
		// set active clock signal
		SPI0_SCK = SPI_CLK_ACTIVE;
		// read input bit
		if (SPI0_MISO)
		{
			spi_data += 0x01;
		}
		// decrement counter
		--i;
	}
	
/*
    // HW specific code for AT89S52
    // take 9 cycles * 12 clocks = 108 clocks total
	// SPI Clock = 	111.11 kHz for 12MHz
#pragma asm
	MOV     A,R7
	
	?M001_SPI_SEND_LOOP:
	CLR SPI0_SCK									   
	MOV C,ACC.7
	MOV SPI0_MOSI,C
	MOV C,SPI0_MISO 									   
	SETB SPI0_SCK									   
	RLC A									   
	DJNZ R6,?M001_SPI_SEND_LOOP
	
	MOV     R7,A
#pragma endasm
*/

	// Clear SPI outputs
	SPI0_SCK = SPI_CLK_IDLE;
	SPI0_MOSI = 0;

  	return spi_data;
}

#endif // _C51_SW_SPI__H_
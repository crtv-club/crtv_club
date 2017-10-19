// c51_sw_spi.c

#include "c51_sw_spi.h"

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

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


#endif // _C51_SW_SPI__H_
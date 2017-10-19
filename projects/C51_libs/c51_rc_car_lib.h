// c51_rc_car_lib.h

#ifndef _C51_RC_CAR_LIB__H_
#define _C51_RC_CAR_LIB__H_

#include <reg52.h>
#include <c51_delay.h>
#include <c51_sw_spi.h>

/**
 * 	RC car control library for C51 by Shurick
 *	Provides rc car control based on C51 and motors drivers (L293D)
 * 	Uses <c51_delay.h> library for delays.
 *	
 *	NOTE: RF24_IRQ and RF24_CE should be declared like sbit.
 * 	Provided Interface:
 *		TBD
 */

/// Define motors pins in this way:
/// sbit M1_OUT1=P1^0;
/// sbit M1_OUT2=P1^1;
/// sbit M2_OUT1=P1^2;
/// sbit M2_OUT2=P1^3;
/// sbit M1_EN=P1^4;
/// sbit M2_EN=P1^5;

// macroses for backward/forvard move
#define MOVE_FORWARD  M1_OUT1=1; M1_OUT2=0;
#define MOVE_BACKWARD M1_OUT1=0; M1_OUT2=1;
#define MOVE_ENABLE   M1_EN=1;
#define MOVE_DISABLE  M1_EN=0;

// macroses for right/left rotate
#define ROTATE_RIGHT   M2_OUT1=0; M2_OUT2=1;
#define ROTATE_LEFT    M2_OUT1=1; M2_OUT2=0;
#define ROTATE_ENABLE  M2_EN=1;
#define ROTATE_DISABLE M2_EN=0;

// for usability
#define DISABLE_ALL  M1_OUT1=0; M1_OUT2=0; M2_OUT1=0; M2_OUT2=0; M1_EN=0; M2_EN=0;

// List of possible RC device commands
typedef enum {
		RC_STOP 			= 0, // Stops device any movement		
	   	RC_MOVE_FORWARD 	= 1, // Move forward for some distance
		RC_MOVE_BACKWARD 	= 2, // Move backward for some distance
		RC_MOVE_STOP		= 3, // Disable current forward/backward move
		RC_TURN_RIGHT 		= 4, // Turn right 
		RC_TURN_LEFT 		= 5, // Turn left
		RC_TURN_STOP		= 6, // Disable current turn left/right move	
		RC_BLINK_ON			= 7, // LED blinker switch on
		RC_BLINK_OFF		= 8, // LED blinker switch off
		RC_BEEP_BEEP		= 9,	 // "Get out of my way!"
		RC_DO_THE_BARREL_ROLL = 10 // Do the barrel roll - just for lulz
} rc_device_commands_type;


// Perform RC car selected command
void do_rc_car_command( unsigned char received_command );

// Receive remote RF command and decode it
void receive_rf_command( void );

// Encode command and send via RF
void send_rf_command( unsigned char rc_command );

// = = = = = = = = = = = = = = = = = = = = = = D E F I N I T I O N = = = = = = = = = = = = = = = = = = = = = =

// Perform RC car selected command
void do_rc_car_command( unsigned char received_command )
{
	switch ( received_command )
	{
	 	case RC_STOP:
		   	DISABLE_ALL
			break;
			
		case RC_MOVE_FORWARD:
			MOVE_FORWARD
			MOVE_ENABLE
			break;
			
		case RC_MOVE_BACKWARD:
			MOVE_BACKWARD
			MOVE_ENABLE
			break;
			
		case RC_MOVE_STOP:
			MOVE_DISABLE
			break;
			
		case RC_TURN_RIGHT:
			ROTATE_RIGHT
			ROTATE_ENABLE
			//delay_ms(200);
			//ROTATE_DISABLE
			break;
			
		case RC_TURN_LEFT:
			ROTATE_LEFT
			ROTATE_ENABLE
			//delay_ms(200);
			//ROTATE_DISABLE
			break;
			
		case RC_TURN_STOP:
			ROTATE_DISABLE
			break;
		
		case RC_BLINK_ON:
			break;
			
		case RC_BLINK_OFF:
			break;
			
		case RC_BEEP_BEEP:
			break;
			
		case RC_DO_THE_BARREL_ROLL:
			// really? OK:
			MOVE_FORWARD
			MOVE_ENABLE
			ROTATE_RIGHT
			ROTATE_ENABLE
			delay_ms(2000);
			ROTATE_DISABLE
			MOVE_DISABLE
			// Hmm... Not impressive, but that's 2D space only
			break;
			
		default: // RC_STOP
		 //	DISABLE_ALL
		 MOVE_FORWARD
			MOVE_ENABLE
			delay_ms(500);
			MOVE_DISABLE
			delay_ms(500);
			MOVE_ENABLE
			delay_ms(500);
			MOVE_DISABLE
			delay_ms(500);
	} 
}

// Receive remote RF command and decode it
void receive_rf_command( void )
{
	unsigned char received_command = nrf24_fifo_read_byte(); //getCommand();

	Display_LSB(received_command);
		/*
	switch ( received_command )
	{
	 	case RC_STOP:
		   	DISABLE_ALL
			break;
		case RC_MOVE_FORWARD:
			MOVE_FORWARD
			MOVE_ENABLE
			delay_ms(500);
			MOVE_DISABLE
			break;
		case RC_MOVE_BACKWARD:
			MOVE_BACKWARD
			MOVE_ENABLE
			delay_ms(500);
			MOVE_DISABLE
			break;
		case RC_TURN_RIGHT:
			ROTATE_RIGHT
			ROTATE_ENABLE
			delay_ms(200);
			ROTATE_DISABLE
			break;
		case RC_TURN_LEFT:
			ROTATE_LEFT
			ROTATE_ENABLE
			delay_ms(200);
			ROTATE_DISABLE
			break;
		case RC_BLINK_ON:
	
			break;
		case RC_BLINK_OFF:
	
			break;
		case RC_BEEP_BEEP:
	
			break;
		case RC_DO_THE_BARREL_ROLL:
			// really? OK:
			MOVE_FORWARD
			MOVE_ENABLE
			ROTATE_RIGHT
			ROTATE_ENABLE
			delay_ms(2000);
			ROTATE_DISABLE
			MOVE_DISABLE
			// Hmm... Not impressive, but that's 2D space only
			break;
		default: // RC_STOP
		 //	DISABLE_ALL
		 MOVE_FORWARD
			MOVE_ENABLE
			delay_ms(500);
			MOVE_DISABLE
			delay_ms(500);
			MOVE_ENABLE
			delay_ms(500);
			MOVE_DISABLE
			delay_ms(500);
	} */
}

// Encode command and send via RF
void send_rf_command( unsigned char rc_command )
{
	//nrf24_fifo_write_byte( rc_command );
	nrf24_fifo_write_data_test(rc_command);
	delay_ms(1);
	nrf24_tx_send();
#ifdef BOARD_TX_MODE_ENABLED
	Display_LSB(rc_command);
#endif
	delay_ms(1000);
}

#endif // _C51_RC_CAR_LIB__H_

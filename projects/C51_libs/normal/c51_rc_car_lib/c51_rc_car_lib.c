// c51_rc_car_lib.c

#include "c51_rc_car_lib.h"

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

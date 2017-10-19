#include <reg52.h>
#include <c51_delay.h>

sbit S_TRIG=P2^0;
sbit S_ECHO=P2^1;
#include <ultrasonic_sensor.h>

// Define used pins
sbit MOTOR1_A = P1^1;
sbit MOTOR1_B = P1^0;
sbit MOTOR1_EN = P1^4;

sbit MOTOR2_A = P1^3;
sbit MOTOR2_B = P1^2;
sbit MOTOR2_EN = P1^5;

// car movement
void car_init(void);
void move_forward(void);
void move_backward(void);
void move_stop(void);
void move_disable(void);


// car rotate
void rotate_right(void);
void rotate_left(void);
void rotate_disable(void);


void main(void)
{
unsigned int distance = 0;
   car_init();	

	 move_forward();
	  delay_ms(2000);
   while(1)
   {
	  /*
	  // drift! ;)
	  move_forward();

	  delay_ms(3000);
      rotate_right();
	  delay_ms(250);
	  rotate_left();
	  delay_ms(150);
	  rotate_right();
	  delay_ms(50);
	  rotate_left();
	  delay_ms(500);
	  rotate_disable();
	  	  delay_ms(1000);
	  move_stop();

	  delay_ms(1000);	*/

	  move_forward();
	  delay_ms(100);
	  distance = measureDistanceCm();
	  if ((distance < 50) || (distance > 350))
	  {
		 move_stop();
		 delay_ms(500);
		 rotate_right();
		 move_backward();
	  	delay_ms(1000);
		  rotate_disable();
		  move_stop();
		  delay_ms(1000);
	  }


   }
}

void car_init(void)
{
    // init motors
    move_forward();
	move_backward();
	move_stop();
	rotate_right();
	rotate_left();
	// disable all
	move_disable();
	rotate_disable();
}

void move_forward(void)
{
   	 // move forward
	 MOTOR1_A = 0; 
	 MOTOR1_B = 1;
	 MOTOR1_EN = 1;
}

void move_backward(void)
{
	   // move backward
	   MOTOR1_A = 1;
	   MOTOR1_B = 0;
	   MOTOR1_EN = 1;   
}

void move_stop(void)
{
	   // stop it!
	   MOTOR1_A = 0;
	   MOTOR1_B = 0;
	   MOTOR1_EN = 1;   
}

void move_disable(void)
{
    MOTOR1_A = 0;
	MOTOR1_B = 0;
   	MOTOR1_EN = 0;
}

void rotate_right(void)
{
     MOTOR2_A = 1; 
	 MOTOR2_B = 0;
	 MOTOR2_EN = 1;
}

void rotate_left(void)
{
     MOTOR2_A = 0; 
	 MOTOR2_B = 1;
	 MOTOR2_EN = 1;
}

void rotate_disable(void)
{
   // stop it!
	   MOTOR2_A = 0;
	   MOTOR2_B = 0;
	   MOTOR2_EN = 0; 
}


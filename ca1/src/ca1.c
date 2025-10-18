/*
 * Programmer: Matas Noreika 2025-10-15 12:00
 * Purpose: Frequency counter application using timer 1 on ICP1. Falling edge trigger is used.
*/

#include <stdio.h>
#include <avr/interrupt.h>
#include "usart_atmega.h" // include custom usart library

#define F_TIMER 15625
//#define ADJUST 1108

//global variable that is incramented during an interrupt causes by input capture pin ICP1
uint16_t last_count = 0;
volatile float freq;

void main(void){//start of main method
  
  //create configuration struct to initialise USART
  usart_config_t usart_data = {
    .usart_num = 0,
    .baudrate = 9600,
    .usart_mode = USART_MODE_ASYNC,
    .frame_size = 8,
    .stop_bits = USART_STOP_BIT_1,
    .parity_mode = USART_PARITY_OFF
  };

  //manually set the transmit speed to double
  UCSR0A |= (1<<U2X0);

  //initialise usart using data
  usart_init(&usart_data);

  //set PB4 as output
  DDRB |= ( (1<<DDB4));
  PORTB ^= (1<<DDB4);

  //enable interrupts for Input capture
  TIMSK1 |= (1<<ICIE1);

  //starts the timer
  //set clock division for timer ~= 64us per tick
  TCCR1B |= ((1<<CS11) | (1<<CS10) );

  //enable global interrupts
  sei();

  uint16_t previous_count;
  char output_str[25];
  
  while(1){//start of program loop
    
    if( TCNT1 - previous_count >= F_TIMER){
      
      //send output string
      sprintf(output_str, "%u %u %u\n", (uint16_t) freq, ICR1, last_count);
      usart_sendString(0, output_str);
      previous_count = TCNT1;
    }
    
  }//end of program loop

}//end of main method

//Interrupt service routine of input capture
ISR(TIMER1_CAPT_vect){
  //calculate frequency
  freq = F_TIMER/(ICR1 - last_count);
  //assign the last count
  last_count = ICR1;
  //toggle debug led
  PORTB ^= (1<<DDB4);
}


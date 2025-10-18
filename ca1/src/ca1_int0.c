/*
 * Programmer: Matas Noreika 2025-10-18 17:09
 * Purpose: Prints out the frequency of a input square wave on int0 using timer 1
*/

#include <stdio.h>
#include <avr/interrupt.h>
#include "usart_atmega.h" // include custom usart library

#define F_TIMER 1000000//1MHz

volatile uint32_t count = 0;
volatile uint32_t previous_count = 0;

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

  //enable overflow interrupt
  TIMSK1 |= (1<<TOIE1);

  //enable int0 rising edge interrupt
  EIMSK |= (1<<0);
  EICRA |= ((1<<ISC01) | (1<<ISC00));

  //starts the timer
  //set clock division for timer ~= 1us per tick
  TCCR1B |= ((0<<CS11) | (1<<CS10) );
  
  //enable interrupts
  sei();
  
  char output_str[25];

  while(1){//start of program loop

    if( previous_count >= F_TIMER){
      //send output string
      sprintf(output_str, "freq: %u\n",count);
      usart_sendString(0, output_str);
      previous_count = 0;
      count = 0;
    }

  }//end of program loop

}//end of main method

//interrupt service routine of timer 1 overflow
ISR(TIMER1_OVF_vect){
  cli();
  previous_count += 65536;
  sei();
}

//interrupt service routine for int0
ISR(INT0_vect){
  cli();
  count++;
  PORTB ^= (1<<DDB4);
  sei();
}


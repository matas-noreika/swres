/*
 * Programmer: Matas Noreika 2025-11-17 16:10
 * Purpose: Simulation of race condition using interrupt on INT0 and output on PB5, using debugger to step and show race condition
*/

#include <avr/io.h> //GPIO register macros
#include <avr/interrupt.h> // interrupt functionality

#define F_CPU 1000000 //set CPU frequency to 1MHz used by delay header
#include <util/delay.h> //definition of _delay_ms macro

//decleration of two global variables
static volatile int temperatures[2];

void main(void){//start of main method

  //set PD2 as an input pull-up (active low pin)
  PORTD |= (1<<2);

  //set INT0 as an interrupt
  //set falling edge trigger
  EICRA |= (1<<ISC01);
  //enable INT0 interrupt flag
  EIMSK |= (1<<0);

  //set PB5 as an output
  DDRB |= (1<<5);
  
  //enable global interrupts
  sei();

  while(1){//start of program loop
    
    _delay_ms(500);
    //critical section of code
    if(temperatures[0] != temperatures[1]){

      //turn on PB5
      PORTB |= (1<<5);

    }
  
  }//end of program loop

}//end of main method

//defintion of ISR for INT0
ISR(INT0_vect){
  //incrament both temperatures
  temperatures[0]++;
  temperatures[1]++;
}

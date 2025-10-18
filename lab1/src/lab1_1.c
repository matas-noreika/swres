/*
 * Programmer: Matas Noreika Mon Sep 15 04:47:54 PM IST 2025
 * Purpose: AVR c program to read number of user presses on a button
*/

#include <stdio.h>
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"

//count variable used to store total number of button presses
uint16_t count;

//ISR decleration for PD2 (INT0)
ISR(INT0_vect){
	
	//incrament the count vairable
	count++;

}

void main(void){//start of main method
	
	//variable to hold output string of count through serial
	char str[25];
	//variable used to hold the string to output for input clock
	char str_feq[25];

	//pe-initialise the count variable
	count = 0;

	//configure PD2 as input pull-up
	DDRD |= (1<<2);
	PORTD |= (1<<2);
	
	//configure INT0 as a falling edge triggered interrupt	
	EICRA |= (1<<ISC01) | (0<<ISC00);
	EIMSK |= (1<<0);//enable the external iterrupt function of INT0	

	//enable global interrupts
	sei();

	//enable the USART
	usartInit();
	
	usartSendString("Usart should be working\n");
	
	uint16_t startCount;

	while(1){//start of program loop

		sei(); //re-enable interrupts once count is updated		
		_delay_ms(1000);
		sprintf(str, "count is: %u\n", count);
		sprintf(str_feq, "feq is: %.2f\n", (count-startCount)/1.0);
		usartSendString(str);
		usartSendString(str_feq);
	}//end of program loop

}//end of main method

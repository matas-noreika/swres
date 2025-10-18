/*
Programmer: Matas Noreika Fri Feb 28 03:37:03 PM GMT 2025
Student ID: B00163844
Purpose: Holds the definitions for the USART API
*/

#include "usart.h"

//initialisation function for usart
void usartInit(void){

	//ENABLE RX & TX
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	
	//set the USART in asynchronous mode
	//UCSR0C &= ~( (1<<UMSEL00) | (1<<UMSEL01) );

	//set no parity mode
	//UCSR0C &= ~( (1<<UPM00) | (1<<UPM01) );
	
	//set to 1 stop bit
	//UCSR0C &= ~( (1<<USBS0) );
	
	//set buffer size for 8 bit communication
	//UCSR0B &= ~(1<<UCSZ02);
	//UCSR0C |= ( (1<<UCSZ00) | (1<<UCSZ01) );
	
	//set the bit for BAUD RATE control
	UCSR0A |= (1<<U2X0);
	
	//set the baud rate to 9600
	UBRR0 = 12;

}

//function to send a single character over uart
void usartSendChar(char c){
		
		//load the buffer with the character argument
		UDR0 = c;
			
		//yield until the character is successfully sent
		while(!usartCharSent());	
	
}

//function to send a string over uart
void usartSendString(const char* str){	

	//while the character is not a null terminator char
	while(*str != '\0'){

		//load the character into the usart data register
		UDR0 = *str;
		
		//incrament the pointer to point to next character
		str++;	

		//yield until the character is successful transmitted
		while(!usartCharSent());

	}

}

//function that returns a positive integer value if a character
//has been recieved in usart data buffer
int8_t usartCharRecieved(){
	
	//mask out the value of the recieved flag
	int8_t recievedFlag = (UCSR0A & (1<<RXC0) ); 	

	//will be greater than 0 if character is recieved
	//or will be 0 if nothing is recieved
	return recievedFlag;

}

//function that returns if the usart finished char transmission
//function checks if the transmit buffer is empty and returns
//the status of the buffer
int8_t usartCharSent(){
	
	//copy the usart control status register a into a variable
	int8_t regStatus = UCSR0A;

	//use a mask to mask out the desired value of bit
	regStatus &= (1<<UDRE0);
	
	//return the value of the regStatus bit
	return regStatus;

}

char usartReadChar(){

	char ch = UDR0;

	return ch;

}


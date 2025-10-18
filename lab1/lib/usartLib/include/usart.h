/*
Programmer: Matas Noreika Fri Feb 28 03:35:48 PM GMT 2025
Student ID: B00163844
Purpose: API for the usart SFR on the atmega328p
*/

#include <avr/io.h>//include the avr standard I/O header
#include <stdint.h>// include standard c header for int size type definitions

//header guard
#ifndef __USART_H__
#define __USART_H__

	/****************************************
	initialisating function for the usart SFR
	9600 BAUD RATE 8 BITS N PARITY 1 STOP BIT	
	****************************************/	
	void usartInit(void);

	/******************************************
	function that sends a single character 
	serially and yields until successfully sent	
	******************************************/	
	void usartSendChar(char);

	/******************************************
	function that sends a string of characters 
	serially and yields until successfully sent	
	******************************************/	
	void usartSendString(const char*);

	/********************************************
	function that returns a positive int if char
	is recieved in buffer or 0 if buffer is empty	
	********************************************/	
	int8_t usartCharRecieved(void);
	
	/********************************************
	function that returns a positive int if char
	is sent from buffer or 0 content isn't sent	
	********************************************/	
	int8_t usartCharSent(void);	

	/********************************************
	function that returns a character from the 
	usart buffer.	
	********************************************/		
	char usartReadChar(void);	


#endif

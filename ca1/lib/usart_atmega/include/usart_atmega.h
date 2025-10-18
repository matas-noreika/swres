/*
 * Programmer: Matas Noreika 2025-10-05 16:14
 * Purpose: usart library for simplifying development on atmega328p and similar microcontrollers 
*/

//Header guard
#ifndef __USART_ATMEGA_H__
#define __USART_ATMEGA_H__

#include <avr/io.h> //avr library for register macros
#include <math.h>//libc math header -> round()
#define F_CPU 1000000UL //change to your cpu frequency

//definition of usart mode types
typedef enum{
  USART_MODE_ASYNC = 0,
  USART_MODE_SYNC = 0x40
}usart_mode_t;

//definition of usart stop bit mode types
typedef enum{
  USART_STOP_BIT_1 = 0x00,
  USART_STOP_BIT_2 = 0x08
}usart_stop_bit_t;

//definition of usart parity mode types 
typedef enum{
  USART_PARITY_OFF = 0x00,
  USART_PARITY_EVEN = 0x20,
  USART_PARITY_ODD = 0x30
}usart_parity_t;

//definition of usart_config_t
typedef struct usart_config_t {
  uint8_t usart_num; // the number of the target usart index
  uint16_t baudrate; //baudrate variable
  usart_mode_t usart_mode; //switches between async and sync mode for transmission optional for spi master
  uint8_t frame_size; //frame size definition
  usart_stop_bit_t stop_bits; //the number of stop bits
  usart_parity_t parity_mode; //sets odd, even or disabled parity
}usart_config_t;

//definition of usart_config_ptr
typedef usart_config_t *usart_config_ptr;

//function to calculate target baudrate from cpu clock speed and target baudrate
uint8_t usart_calc_baud(uint8_t usart_num, uint16_t baudrate);

//Function to set the baud rate for a specific usart
void usart_set_baud(uint8_t usart_num, uint16_t baudrate);

//Function to set the frame size of usart transmission
void usart_set_frame_size(uint8_t usart_num, uint8_t frame_size);

//Function to set the mode of the usart communication
void usart_set_mode(uint8_t usart_num, usart_mode_t mode);

//Function to set the parity mode of the usart communication
void usart_set_parity(uint8_t usart_num, usart_parity_t parity);

//Function to set the stop bits of the usart communication
void usart_set_stopbits(uint8_t usart_num, usart_stop_bit_t stop_bits);

//init function for usart
void usart_init(usart_config_ptr config_data);

//function to send a single character using the usart
void usart_sendChar(uint8_t usart_num, char c);

//function to send a string using the usart
void usart_sendString(uint8_t usart_num, char* string);

#endif

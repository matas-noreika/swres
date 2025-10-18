/*
 * Programmer: Matas Noreika 2025-10-05 16:34 
 * Purpose: implementation of usart library
*/

#include "usart_atmega.h"

//function to calculate target baudrate from cpu clock speed and target baudrate
uint8_t usart_calc_baud(uint8_t usart_num, uint16_t baudrate){
  volatile uint8_t *ucsr_a;

  switch (usart_num){
    case 0:
      ucsr_a = &UCSR0A;
      break;
    default:
      //assert error
      break;
  }

  double baudValue;
  //check if the double transmission speed flag is set
  if (*ucsr_a & (1<<U2X0)){
    baudValue = (F_CPU/(8.00*baudrate)) - 1;
  }else{
    baudValue = (F_CPU/(16.00*baudrate)) - 1;
  }
  
  //return the rounded value
  return round(baudValue);
}

//Function to set the buadrate of a specific usart
void usart_set_baud(uint8_t usart_num, uint16_t baudrate){
  //create a vairable to hold the location of the UBBRn register related to usart
  volatile uint16_t *ubbr_reg;
  
  //retrieve the UBRRn register 
  switch (usart_num){
    case 0:// usart 0
      ubbr_reg = &UBRR0;
      break;
    default: // invalid usart
      //assert an error
      break;
  }

  //set the baudrate to the value calculate from baudrate
  *ubbr_reg = usart_calc_baud(usart_num, baudrate);

}

//Function to set the frame size of the usart transmission for usart x
void usart_set_frame_size(uint8_t usart_num, uint8_t frame_size){
  //pointer variables to usart x registers
  volatile uint8_t *ucsr_c;
  volatile uint8_t *ucsr_b;
  
  //set the registers based on usart number
  switch(usart_num){
    case 0:
      ucsr_b = &UCSR0B;
      ucsr_c = &UCSR0C;
      break;
    default:
      //assert an error
      break;
  }
  
  //usart frame size switch case 
  switch (frame_size){
    case 6:
      *ucsr_c |= (1<<UCSZ00);
      break;
    case 7:
      *ucsr_c |= (1<<UCSZ01);
      break;
    case 8:
      *ucsr_c |= (1<<UCSZ01) | (1<<UCSZ00);
      break;
    case 9:
      *ucsr_b |= (1<<UCSZ02); 
      *ucsr_c |= (1<<UCSZ01) | (1<<UCSZ00);
      break;
    default:
      //assert and error message saying the frame size is unsupported
      break;
  }

}

//Function to set the mode of the usart communication
void usart_set_mode(uint8_t usart_num, usart_mode_t mode){
  //pointer variables to usart x registers
  volatile uint8_t *ucsr_c;
  
  //set the registers based on usart number
  switch(usart_num){
    case 0:
      ucsr_c = &UCSR0C;
      break;
    default:
      //assert an error
      break;
  }

  *ucsr_c |= mode;
}

//Function to set the parity of the usart communication
void usart_set_parity(uint8_t usart_num, usart_parity_t parity){
  //pointer variables to usart x registers
  volatile uint8_t *ucsr_c;
  volatile uint8_t *ucsr_b;
  
  //set the registers based on usart number
  switch(usart_num){
    case 0:
      ucsr_b = &UCSR0B;
      ucsr_c = &UCSR0C;
      break;
    default:
      //assert an error
      break;
  }

  *ucsr_c |= parity;

}

void usart_set_stopbits(uint8_t usart_num, usart_stop_bit_t stop_bits){
  //pointer variables to usart x registers
  volatile uint8_t *ucsr_c;
  
  //set the registers based on usart number
  switch(usart_num){
    case 0:
      ucsr_c = &UCSR0C;
      break;
    default:
      //assert an error
      break;
  }

  *ucsr_c |= stop_bits;
}

//init function for usart
void usart_init(usart_config_ptr config_data){
  
  //pointer variables to usart x registers
  volatile uint8_t *ucsr_c;
  volatile uint8_t *ucsr_b;
  
  //set the registers based on usart number
  switch(config_data->usart_num){
    case 0:
      ucsr_b = &UCSR0B;
      ucsr_c = &UCSR0C;
      break;
    default:
      //assert an error
      break;
  }

  //set the correct baudrate
  usart_set_baud(config_data->usart_num, config_data->baudrate);
  
  //set the usart frame size
  usart_set_frame_size(config_data->usart_num, config_data->frame_size);
  
  //set the usart transmission mode
  usart_set_mode(config_data->usart_num, config_data->usart_mode);

  //set the parity mode
  usart_set_parity(config_data->usart_num, config_data->parity_mode);
  
  //set the stop bits for the usart
  usart_set_stopbits(config_data->usart_num, config_data->stop_bits);

  //enable reciever & tramsmitter
  *ucsr_b |= (1<<RXEN0) | (1<<TXEN0);
}

//function to send a single character using the usart
void usart_sendChar(uint8_t usart_num, char c){
  volatile uint8_t *ucsr_a;
  volatile uint8_t *udr;

  //switch case to switch between which usart is used
  switch (usart_num){
    case 0:
      ucsr_a = &UCSR0A;
      udr = &UDR0;
      break;
    default:
      //assert an error
      break;
  }

  while ((*ucsr_a & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
	*udr = c;
}

//function to send a string using the usart
void usart_sendString(uint8_t usart_num, char* string){
  uint8_t i = 0;
  
  while(string[i] != '\0'){
    usart_sendChar(usart_num, string[i++]);
  }
}


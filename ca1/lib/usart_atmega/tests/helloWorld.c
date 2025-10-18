/*
 * Programmer: Matas Noreika 2025-10-06 17:44 
 * Purpose: Hello world example to show how to send a hello world string over the usart
*/

#include "usart_atmega.h"
#include <util/delay.h>

void main(void){
  
  //create configuration struct for the usart
  usart_config_t configData= {
    .usart_num = 0,
    .frame_size = 8,
    .usart_mode = USART_MODE_ASYNC,
    .baudrate = 9600,
    .stop_bits = USART_STOP_BIT_1,
    .parity_mode = USART_PARITY_OFF
  };

  //manually set the transmit speed to double
  UCSR0A |= (1<<U2X0);

  usart_init(&configData);

  while (1){
    usart_sendString(configData.usart_num,"Hello world\n");
    _delay_ms(250);
  }
}

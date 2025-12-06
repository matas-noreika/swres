/*
 * Programmer: Matas Noreika 2025-12-04 11:40
 * Purpose: Generate a blink program that will change the blink frequency based on the input provided through usart
 * a more detailed overview is provided in the README.md found in this project directory
*/

//include libc headers
#include <stdio.h>
//include avr-libc headers
#include <avr/io.h>
//include usart headers
#include "usart_atmega.h"
//include freeRTOS headers
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//communication between taskA -> taskB
QueueHandle_t queue1 = NULL;
//communication between taskB -> taskA
QueueHandle_t queue2 = NULL;

//function prototypes
static void taskA(void *pvParameters);
static void taskB(void *pvParameters);

void main (void){//start of main method

  /////////////////USART CONFIG/////////////////////
  //configure the usart properties
  usart_config_t usart_config = {
    .usart_num = 0,
    .baudrate = 9600,
    .usart_mode = USART_MODE_ASYNC,
    .frame_size = 8,
    .stop_bits = USART_STOP_BIT_1,
    .parity_mode = USART_PARITY_OFF
  };

  //manually set the transmit speed to double
  UCSR0A |= (1<<U2X0);

  //initialise the usart with config data
  usart_init(&usart_config);
  ////////////////////////////////////////////////


  ////////////////////QUEUE CONFIG/////////////////
  //create queue1
  queue1 = xQueueCreate(
    NULL,
    256,
    NULL,
    2,
    NULL
  );

  //create queue2
  queue2 = xQueueCreate(
    NULL,
    256,
    NULL,
    2,
    NULL
  );
  ////////////////////////////////////////////////

  //start the scheduler
  vTaskStartScheduler();

}//end of main method

//task that reads from serial and echos back the content
static void taskA(void *pvParameters){
  
}

//task that just blinks an LED at t interval
static void taskB(void *pvParameters){
  
}

/*
 * Programmer: Matas Noreika 2025-12-01 17:19
 * Purpose: Implementation of nuclear reactor system that checks if two temperatures are equal. If they are not an alarm is triggered
*/

//include libc headers
#include <stdio.h>

//include avr-libc headers
#include <avr/io.h>
#include <avr/interrupt.h>

//include USART library
#include "usart_atmega.h"

//include FREErtos
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//global variables
//pre-intialised with 0
static volatile uint16_t temperatures[2] = {0};

//Function prototypes
static void updateTempsTask(void * pvParameters);
static void alarmTask(void *pvParameters);

//USART semaphore
SemaphoreHandle_t usart_semphr = NULL;
//signalling semaphore
SemaphoreHandle_t sig_semphr = NULL;
//temperature access semaphore
SemaphoreHandle_t temp_semphr = NULL;

void main(void){//start of main method

  ///////////////USART  SETUP///////////////
  usart_config_t usart_config = {
    .usart_num = 0,
    .baudrate = 9600,
    .usart_mode = USART_MODE_ASYNC,
    .frame_size = 8,
    .stop_bits = USART_STOP_BIT_1,
    .parity_mode = USART_PARITY_OFF
  };

  //enable double output data rate
  UCSR0A |= (1<<U2X0);

  //call method to intialise usart
  usart_init(&usart_config);
  /////////////////////////////////////////
  
  /////////////SEMAPHORE SETUP//////////////
  //USART semaphore
  usart_semphr = xSemaphoreCreateBinary();
  xSemaphoreGive(usart_semphr); //enable the usart to be available by default
  //task signalling semaphore
  sig_semphr = xSemaphoreCreateBinary();
  //temperature access semaphore
  temp_semphr = xSemaphoreCreateBinary();
  xSemaphoreGive(temp_semphr); //enable the temp to be available by default
  /////////////////////////////////////////
  
  ////////////////GPIO SETUP////////////////
  //configure INT0 interrupt properties
  DDRD |= (1<<2); //set PD2 as Input
  PORTD |= (1<<2); //set internal pull-up resistors on PD2
  EICRA |= (1<<ISC01); //set the INT0 edge trigger as falling edge
  EIMSK |= (1<<INT0); //set INT0 as active interrupt
  sei(); //enable global interrupts
  /////////////////////////////////////////
  

  ////////////////TASK SETUP////////////////

  //creates the task to handle the temperature incramenting
  xTaskCreate(
    updateTempsTask,
    NULL,
    256,
    NULL,
    3,
    NULL
  );

  //creates the task to handle the alarm checking
  xTaskCreate(
    alarmTask,
    NULL,
    256,
    NULL,
    2,
    NULL
  );

  /////////////////////////////////////////

  //start the scheduler
  vTaskStartScheduler();

}//end of main method

//set the ISR for INT0 (PD2)
ISR(INT0_vect){

  //Give the signalling semaphore
  xSemaphoreGiveFromISR(sig_semphr, NULL);

}

//Task that will update the global variables only when the task signalling semaphore is available
static void updateTempsTask(void * pvParameters){

  //usart string buffer for printing temperatures
  char usart_str[50] = {0};

  while(1){//start of task loop
    
    //attempt to take signalling semaphore or yield until available
    xSemaphoreTake(sig_semphr, portMAX_DELAY);

    //attempt to take temperature semaphore or yield until available
    xSemaphoreTake(temp_semphr, portMAX_DELAY);

    //incrament both temperatures
    temperatures[0]++;
    temperatures[1]++;

    //copy the contents of temperatures into string buffer
    sprintf(usart_str,"temp1: %d\ntemp2: %d\n",temperatures[0], temperatures[1]);

    //give back the temp semaphore to allow other tasks to access temperatures
    xSemaphoreGive(temp_semphr);

    //attempt to take usart semaphore or yield until available
    xSemaphoreTake(usart_semphr, portMAX_DELAY);

    //print the contents of buffer out
    usart_sendString(0, usart_str);

    //give back the usart semaphore to allow other tasks to access temperatures
    xSemaphoreGive(usart_semphr);


  }//end of task loop

}

//Task that will check to see if two temperatures are equal
static void alarmTask(void *pvParameters){
  
  //variable to hold the status of the alarm
  uint8_t alarm_status = 0;
  //create local variables to store contents of global variables
  uint16_t temp1, temp2;
  //usart string buffer
  char usart_str[30] = {0};

  while(1){//start of task loop
    
    //attempt to take temp semaphore or yield until available
    xSemaphoreTake(temp_semphr, portMAX_DELAY);
    
    //copy the global variables
    temp1 = temperatures[0];
    temp2 = temperatures[1];

    //give back the temp semaphore to allow other tasks to access temperatures
    xSemaphoreGive(temp_semphr);
    
    //set the alarm status to 1 if two temperatures dont match
    alarm_status = (temp1 != temp2) ? 1 : 0;

    //if the alarm is trrigered
    if(alarm_status){
      //set the led on
      PORTB |= (1<<5);
    }

    //configure the string buffer
    sprintf(usart_str,"Alarm status: %d\n", alarm_status);

    //attempt to take usart semaphore or yield until available
    xSemaphoreTake(usart_semphr, portMAX_DELAY);

    //send string over usart
    usart_sendString(0, usart_str);

    //give back the usart semaphore to allow other tasks to access temperatures
    xSemaphoreGive(usart_semphr);

    //wait roughly 500ms +- portTICK_PERIOD_MS (15ms)
    vTaskDelay(500 / portTICK_PERIOD_MS);

  }//end of task loop

}

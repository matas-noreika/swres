/*
 * Programmer: Matas Noreika 2025-12-04 11:40
 * Purpose: Generate a blink program that will change the blink frequency based on the input provided through usart
 * a more detailed overview is provided in the README.md found in this project directory
*/

//include libc headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include avr-libc headers
#include <avr/io.h>
//include usart headers
#include "usart_atmega.h"
//include freeRTOS headers
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//Settings
static const uint8_t buff_len = 127; //length of read buffer
static const uint8_t blink_max = 100; //max number of blinks to perform
static const char command[] = "delay "; //the command string to match delay time change with
static const uint8_t queue1_len = 5; //length of queue entries in queue 1
static const uint8_t queue2_len = 5; //length of queue entries in queue 2

//Definition of message type for communication between tasks
typedef struct {
  char body[20];
  uint8_t count;
} Message;

//communication between taskA -> taskB
static QueueHandle_t queue1 = NULL;
//communication between taskB -> taskA
static QueueHandle_t queue2 = NULL;

//function prototypes
static void taskA(void *pvParameters);
static void taskB(void *pvParameters);

void main(void){//start of main method

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
  queue1 = xQueueCreate(queue1_len, sizeof(Message));

  //create queue2
  queue2 = xQueueCreate(queue2_len, sizeof(uint16_t));
  ////////////////////////////////////////////////


  ////////////////////TASK CONFIG/////////////////
  xTaskCreate(
    taskA,
    NULL,
    512,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    taskB,
    NULL,
    512,
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
  Message rcv_msg;
  uint16_t new_delay = 0;
  //definition of local read buffer to hold the contents of usart RX
  char read_buffer[buff_len];
  uint8_t cmd_len = strlen(command); //retrieve the length of the command string
  uint8_t cursor = 0; //current cursor to position in buffer
  char c;//read character

  // Clear whole buffer
  memset(read_buffer, 0, buff_len);

  while(1){//start of task loop

    //if queue content is recieved
    if(xQueueReceive(queue1, (void*)&rcv_msg, 0) == pdTRUE){
      usart_sendString(0,rcv_msg.body);
    }

    // check to see if serial content is available
    if(usart_available(0)){

      //read character from serial
      c = usart_readChar(0);

      //if the buffer is not yet full
      if(cursor < buff_len - 1){
        read_buffer[cursor] = c;
        cursor++;
      }

      //if termination characters are sent
      if(c == '\n' || c == '\r'){

        //write control characters back
        usart_sendString(0, "\r\n");

        //check if delay command is sent
        if(memcmp(read_buffer,command,cmd_len) == 0){
          
          //get the tail of command
          char* str_tail = read_buffer + cmd_len;
          new_delay = atoi(str_tail);
          new_delay = abs(new_delay);

          //write the new delay time to queue 2
          if(xQueueSend(queue2, (void*)&new_delay, 10) != pdTRUE){
            //write error message in the case queue is full or unavailable
            usart_sendString(0,"ERROR: Failed to send new delay time!");
          }

        }

        //reset buffer + cursor
        memset(read_buffer, 0, buff_len);
        cursor = 0;

      }else{
        //echo back character to usart
        usart_sendChar(0, c);
      }

    }

  }//end of task loop

}

//task that just blinks an LED at time interval
static void taskB(void *pvParameters){
  
  Message msg; //Variable to use to add messages to queue
  uint8_t blink_count = 0;//variable used to count iterations of blinks
  uint16_t led_delay = 500;// default 500ms delay (will update with queue message recieved)

  //set PB5 as an output
  DDRB |= (1<<5);

  while(1){//start of task loop

    //no yielding check to see if content is recieved
    if(xQueueReceive(queue2, (void*)&led_delay, 0) == pdTRUE){
      strcpy(msg.body, "received msg ");
      msg.count = 1;
      xQueueSend(queue1, (void*)&msg, 10);
    }

    //blink
    PORTB |= (1<<5);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
    PORTB &= ~(1<<5);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);

    //incrament blink count
    blink_count++;

    //reached max blink count
    if(blink_count >= blink_max){
      strcpy(msg.body, "Blinked: ");
      msg.count = blink_count;
      //write message to task 1 queue will wait 10ms
      xQueueSend(queue1, (void*)&msg, 10);
      //reset counter
      blink_count = 0;
    }

  }//end of task loop

}

/*
 * Programmer: Matas Noreika 2025-11-26 11:15
 * Purpose: Showcase race conditions using two tasks accessing global variables
*/
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define INCDELAY 500 //1.5 seconds
#define ALARMDELAY 250 //0.25 seconds
#define READDELAY 250 //0.25 seconds

//initialises global temperatures with 0
static volatile uint8_t temperatures[2] = {0};

//create a object to hold the handler for the semaphore
SemaphoreHandle_t xSemaphore = NULL;

/*-----------------------------------------------------------*/
static void TaskIncValues(void *pvParameters);
static void TaskAlarm(void *pvParameters);
/*-----------------------------------------------------------*/

int main(void)
{

  xSemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(xSemaphore);
  //PB5 as alarm pin
  DDRB |= (1<<5);

  //ensure PB5 is off
  PORTB &= ~(1<<5);

  xTaskCreate(
    TaskIncValues, //task function pointer
    (const char *)"IncValues", // string label
    256, //local stack size
    NULL, //parameters
    3, //Priority of task
    NULL //task handler
  );

  xTaskCreate(
    TaskAlarm, //task function pointer
    (const char *)"Alarm", //string label
    256, //local stack size
    NULL, //parameters
    2, //priority of task
    NULL //task handler
  );

	vTaskStartScheduler();    //This never returns... control handed to the RTOS
}

/*-----------------------------------------------------------*/

static void TaskIncValues(void * pvParameters){
  while(1){
    if(xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE){
      temperatures[0]++;
      temperatures[1]++;
      vTaskDelay(INCDELAY / portTICK_PERIOD_MS);
      xSemaphoreGive(xSemaphore);
    }
  }
}

static void TaskAlarm(void * pvParameters){
  while(1){
    uint8_t temp1,temp2;
    if (xSemaphoreTake(xSemaphore, (TickType_t) 10) == pdTRUE){
      temp1 = temperatures[0];
      vTaskDelay(READDELAY / portTICK_PERIOD_MS);
      temp2 = temperatures[1];
      xSemaphoreGive(xSemaphore);
    }
    if(temp1 != temp2){
      PORTB |= (1<<5);
    }

    vTaskDelay(ALARMDELAY / portTICK_PERIOD_MS);
  }
}

/*---------------------------------------------------------------------------*/

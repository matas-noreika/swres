/*
 * Programmer: Matas Noreika 2025-12-01 17:19
 * Purpose: Implementation of nuclear reactor system that checks if two temperatures are equal. If they are not an alarm is triggered
*/

//include USART library

//include FREErtos
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//Function prototypes
void updateTempsTask(void * pvParameters);
void 

void main(void){

  //USART semaphore
  //task signalling semaphore
  //temperature access semaphore
  //

}

//Task that will update the global variables only when the task signalling semaphore is available
void updateTempsTask(void * pvParameters){

}

#include "Req.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

char rx_buffer[100];

TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;
void StartTask1(void *parameters);
void StartTask2(void *parameters);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
void vApplicationMallocFailedHook(void);
int main(void){

	
	BaseType_t status;
	
	SysClockConfig();
	gpio_uart2_init();
	gpio_led_init();
	
	//Task Creation
	status = xTaskCreate(StartTask1,"Task1",256,NULL,3,&Task1Handle);
	
	configASSERT(status == pdPASS);
	
	usart2_send_string("Task1 is created successfully\r\n");
	
	status = xTaskCreate(StartTask2,"Task2",256,NULL,2,&Task2Handle);
	
	configASSERT(status == pdPASS);
	
	usart2_send_string("Task2 is created successfully\r\n");
	
	
	//Start scheduler
	vTaskStartScheduler();
	
	
	
	
	while(1){

	}

	return 0;
}

void StartTask1(void *parameters){
	
	for(;;){
		
		usart2_send_string("Task 1 is on\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
		
	}


}


void StartTask2(void *parameters){

	for(;;){
	
		usart2_send_string("Task2 is on\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
		
	}

}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName){

	usart2_send_string("Stack overflow detected in task: ");
	usart2_send_string(pcTaskName);
	usart2_send_string("\n");
	
	while(1){
	
	}

}

void vApplicationMallocFailedHook(void)
{
    __BKPT(0); // Debugger burada duracak
    while (1);
}
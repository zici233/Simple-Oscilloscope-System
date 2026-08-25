#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "main.h"
#include "key1.h"
static KeyHandle_TypeDef hkey1;
static void Key1_ClickedCallback(void);
void Key_Task(void *pvParameters)
{
    hkey1.GPIO_Port = KEY1_GPIO_Port;
	hkey1.GPIO_Pin  = KEY1_Pin;
	hkey1.ClickedCallback =Key1_ClickedCallback;

	Key1_Init(&hkey1);
	while (1)
	{

		Key1_Scan(&hkey1);
		vTaskDelay(pdMS_TO_TICKS(10)); /* 10ms 轮询,兼作简易去抖 */
	}
}
static void Key1_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1, (uint8_t*)"Key1 Clicked!\r\n", 16, 1000);
}
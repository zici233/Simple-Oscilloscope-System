#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "key1.h"
static KeyHandle_TypeDef hkey1;
static void Key1_ClickedCallback(void);


void Key1_Init(void)
{
    hkey1.GPIO_Port = KEY1_GPIO_Port;
    hkey1.GPIO_Pin  = KEY1_Pin;
    hkey1.ClickedCallback = Key1_ClickedCallback;
    Key_Init(&hkey1);
    
}

void Key1_Scan(void)
{
    Key_Scan(&hkey1);
}
static void Key1_ClickedCallback(void)
{
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1, (uint8_t*)"Key1 Clicked!\r\n", 16, 1000);
}
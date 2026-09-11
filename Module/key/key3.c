#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "key3.h"
#include "buzzer.h"

static KeyHandle_TypeDef hkey3;
static void Key3_ClickedCallback(void);
void Key3_Init(void)
{

    hkey3.GPIO_Port = KEY3_GPIO_Port;
    hkey3.GPIO_Pin  = KEY3_Pin;
    hkey3.ClickedCallback = Key3_ClickedCallback;
    Key_Init(&hkey3);
}

void Key3_Scan(void)
{
Key_Scan(&hkey3);
}

static void Key3_ClickedCallback(void)
{
	Buzzer_Beep(); /* 按键音效 */
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1, (uint8_t*)"Key3 Clicked!\r\n", 16, 1000);
}
#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "key4.h"
#include "buzzer.h"

static KeyHandle_TypeDef hkey4;
static void Key4_ClickedCallback(void);
void Key4_Init(void)
{
    hkey4.GPIO_Port = KEY4_GPIO_Port;
    hkey4.GPIO_Pin  = KEY4_Pin;
    hkey4.ClickedCallback = Key4_ClickedCallback;
    Key_Init(&hkey4);
}

void Key4_Scan(void)
{
    Key_Scan(&hkey4);
}

static void Key4_ClickedCallback(void)
{Buzzer_Beep(); /* 按键音效 */
	
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1, (uint8_t*)"Key4 Clicked!\r\n", 16, 1000);
}
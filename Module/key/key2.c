#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "key2.h"
#include "buzzer.h"

static KeyHandle_TypeDef hkey2;
static void Key2_ClickedCallback(void);
void Key2_Init(void)
{

    hkey2.GPIO_Port = KEY2_GPIO_Port;
    hkey2.GPIO_Pin  = KEY2_Pin;
    hkey2.ClickedCallback = Key2_ClickedCallback;
    Key_Init(&hkey2);
}

void Key2_Scan(void)
{
   Key_Scan(&hkey2);
}


static void Key2_ClickedCallback(void)
{
	Buzzer_Beep(); /* 按键音效 */
	extern UART_HandleTypeDef huart1;
	HAL_UART_Transmit(&huart1, (uint8_t*)"Key2 Clicked!\r\n", 16, 1000);
}
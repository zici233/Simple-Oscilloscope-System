#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"

static KeyHandle_TypeDef hkeydown;
static void Keydown_ClickedCallback(void);

void Keydown_Init(KeyHandle_TypeDef* Handle)
{
    hkeydown.previous = GPIO_PIN_SET;
    hkeydown.current  = GPIO_PIN_SET;
}

void Keydown_Scan(KeyHandle_TypeDef* Handle)
{
    hkeydown.current = HAL_GPIO_ReadPin(hkeydown.GPIO_Port, hkeydown.GPIO_Pin);

    if (hkeydown.previous == GPIO_PIN_SET && hkeydown.current == GPIO_PIN_RESET)
    {
        hkeydown.ClickedCallback();   /* 调用点击回调函数 */
    }

    hkeydown.previous = hkeydown.current;
}
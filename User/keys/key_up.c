#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"

static KeyHandle_TypeDef hkeyup;
static void Keyup_ClickedCallback(void);

void Keyup_Init(KeyHandle_TypeDef* Handle)
{
    hkeyup.previous = GPIO_PIN_SET;
    hkeyup.current  = GPIO_PIN_SET;
}

void Keyup_Scan(KeyHandle_TypeDef* Handle)
{
    hkeyup.current = HAL_GPIO_ReadPin(hkeyup.GPIO_Port, hkeyup.GPIO_Pin);

    if (hkeyup.previous == GPIO_PIN_SET && hkeyup.current == GPIO_PIN_RESET)
    {
        hkeyup.ClickedCallback();   /* 调用点击回调函数 */
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin); /* 切换LED状态 */
    }

    hkeyup.previous = hkeyup.current;
}
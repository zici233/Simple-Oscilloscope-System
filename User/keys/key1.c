#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "key1.h"

void Key1_Init(KeyHandle_TypeDef* Handle)
{
    Handle->previous = GPIO_PIN_SET;
    Handle->current  = GPIO_PIN_SET;
}

void Key1_Scan(KeyHandle_TypeDef* Handle)
{
    Handle->current = HAL_GPIO_ReadPin(Handle->GPIO_Port, Handle->GPIO_Pin);

    if (Handle->previous == GPIO_PIN_SET && Handle->current == GPIO_PIN_RESET)
    {
        Handle->ClickedCallback();   /* 调用点击回调函数 */
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin); /* 切换LED状态 */
    }

    Handle->previous = Handle->current;
}
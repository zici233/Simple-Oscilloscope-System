/*
 * buzzer_task.c
 *
 * 应用层：等待模块层的鸣叫请求，收到后驱动蜂鸣器响 BUZZER_BEEP_MS 毫秒。
 */

#include "FreeRTOS.h"
#include "task.h"
#include "buzzer.h"
#include "buzzer_task.h"

void Buzzer_Task(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        if (Buzzer_WaitBeep(portMAX_DELAY) == pdTRUE)
        {
            Buzzer_On();
            vTaskDelay(pdMS_TO_TICKS(BUZZER_BEEP_MS));
            Buzzer_Off();
        }
    }
}

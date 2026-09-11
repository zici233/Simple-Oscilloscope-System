/*
 * buzzer.c
 *
 * 模块层：蜂鸣器设备模块实现
 *  按键等模块调用 Buzzer_Beep() 发出请求，应用层任务用 Buzzer_WaitBeep()
 *  取出请求后驱动蜂鸣器鸣叫。
 */

#include "FreeRTOS.h"
#include "semphr.h"
#include "main.h"
#include "buzzer.h"

static SemaphoreHandle_t buzzer_semaphore;

void Buzzer_Init(void)
{
    buzzer_semaphore = xSemaphoreCreateBinary();
    configASSERT(buzzer_semaphore != NULL);

    Buzzer_Off(); /* 上电确保蜂鸣器静音 */
}

void Buzzer_Beep(void)
{
    if (buzzer_semaphore != NULL)
    {
        xSemaphoreGive(buzzer_semaphore);
    }
}

BaseType_t Buzzer_WaitBeep(TickType_t xTicksToWait)
{
    if (buzzer_semaphore == NULL)
    {
        return pdFALSE;
    }
    return xSemaphoreTake(buzzer_semaphore, xTicksToWait);
}

void Buzzer_On(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
}

void Buzzer_Off(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}

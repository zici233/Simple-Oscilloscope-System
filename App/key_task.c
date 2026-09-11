/*
 * key_task.c
 *
 * 应用层：周期性轮询 4 个按键模块（初始化已在 App_Init() 中完成）。
 */

#include "FreeRTOS.h"
#include "task.h"
#include "key1.h"
#include "key2.h"
#include "key3.h"
#include "key4.h"
#include "key_task.h"

/* 轮询周期(ms)，兼作简易去抖 */
#define KEY_SCAN_PERIOD_MS      10

void Key_Task(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        Key1_Scan();
        Key2_Scan();
        Key3_Scan();
        Key4_Scan();
        vTaskDelay(pdMS_TO_TICKS(KEY_SCAN_PERIOD_MS));
    }
}

/*
 * app.c
 *
 * 应用层：统一完成模块层初始化与应用层任务创建。
 * 依赖方向：App -> Module -> Bsp -> Core/Drivers(厂商 HAL+CMSIS)/FreeRTOS
 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* 模块层 */
#include "key1.h"
#include "key2.h"
#include "key3.h"
#include "key4.h"
#include "buzzer.h"

/* 应用层 */
#include "key_task.h"
#include "buzzer_task.h"
#include "app.h"

/* 任务参数 */
#define APP_KEY_TASK_STACK          256
#define APP_KEY_TASK_PRIO           3
#define APP_BUZZER_TASK_STACK       256
#define APP_BUZZER_TASK_PRIO        3

void App_Init(void)
{
    /* ---- 模块层初始化 ---- */
    Key1_Init();
    Key2_Init();
    Key3_Init();
    Key4_Init();
    Buzzer_Init();

    /* ---- 应用层任务 ---- */
    configASSERT(xTaskCreate(Key_Task, "Key", APP_KEY_TASK_STACK,
                             NULL, APP_KEY_TASK_PRIO, NULL) == pdPASS);
    configASSERT(xTaskCreate(Buzzer_Task, "Buzzer", APP_BUZZER_TASK_STACK,
                             NULL, APP_BUZZER_TASK_PRIO, NULL) == pdPASS);
}

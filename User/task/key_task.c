#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "main.h"
#include "key1.h"
#include "key2.h"
#include "key3.h"
#include "key4.h"


void Key_Task(void *pvParameters)
{


	Key1_Init();
    Key2_Init();
    Key3_Init();
    Key4_Init();

	while (1)
	{
		Key1_Scan();
		Key2_Scan();
		Key3_Scan();
		Key4_Scan();
		vTaskDelay(pdMS_TO_TICKS(10)); /* 10ms 轮询,兼作简易去抖 */
	}
}

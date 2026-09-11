/*
 * buzzer.h
 *
 * 模块层：蜂鸣器设备模块
 *  - 对外只暴露"设备 API"（请求鸣叫 / 开关蜂鸣器 / 等待请求）
 *  - 具体什么时候鸣叫由应用层任务决定
 */

#ifndef MODULE_BUZZER_BUZZER_H_
#define MODULE_BUZZER_BUZZER_H_

#include "FreeRTOS.h"

/* 模块参数：单次鸣叫时长(ms) */
#define BUZZER_BEEP_MS      100

/* 初始化：创建内部信号量并确保蜂鸣器静音（调度器启动前调用） */
void Buzzer_Init(void);

/* 请求一次鸣叫：非阻塞，任何模块/任务上下文均可调用 */
void Buzzer_Beep(void);

/* 等待一次鸣叫请求，供应用层任务使用 */
BaseType_t Buzzer_WaitBeep(TickType_t xTicksToWait);

/* 蜂鸣器硬件开关，供应用层任务使用 */
void Buzzer_On(void);
void Buzzer_Off(void);

#endif /* MODULE_BUZZER_BUZZER_H_ */

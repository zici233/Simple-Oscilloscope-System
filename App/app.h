/*
 * app.h
 *
 * 应用层入口：main.c 只调用 App_Init()，其余初始化/任务创建都在应用层内完成。
 */

#ifndef APP_APP_H_
#define APP_APP_H_

/* 初始化模块层并创建应用层任务（调度器启动前调用） */
void App_Init(void);

#endif /* APP_APP_H_ */

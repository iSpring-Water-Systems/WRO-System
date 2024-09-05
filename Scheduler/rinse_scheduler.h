#ifndef RINSE_SCHEDULER_H
#define RINSE_SCHEDULER_H

#include "stm32f1xx_hal.h"

//队列定义
typedef enum {
  TASK_F1, TASK_F2, TASK_F3, TASK_F4, TASK_F5, TASK_F6
} TaskType;


#define QUEUE_SIZE 6


// 状态标志
extern __IO uint8_t isWaterTreatmentActive;
extern __IO uint8_t isLeakAlarm;
extern __IO uint8_t isRinsingActive;

// 模块接口
void FlushScheduler_Init(void);
void FlushScheduler_AddTasks(void);
void FlushScheduler_ExecuteTask(TaskType taskType);
void FlushScheduler_MainLoop(void);

//void RinseScheduler_Init(void);
//void RinseScheduler_Handler(void);


#endif // RINSE_SCHEDULER_H
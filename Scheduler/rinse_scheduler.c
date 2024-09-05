#include "rinse_scheduler.h"
#include "cmsis_os.h" // 引入操作系统头文件
#include "ntp_client.h" // 假设你有一个NTP客户端的实现


RTC_HandleTypeDef hrtc;

// 设置一个全局变量，用于保存之前获取的时间
RTC_TimeTypeDef savedTime = {0}; // 保存之前获取的时间
RTC_DateTypeDef savedDate = {0}; // 保存之前获取的日期

//使用临界保护区列队操作
osMutexId_t queueMutex = osMutexCreate(osMutex(QueueMutex));

void enter_critical_section(void) {
  osMutexAcquire(queueMutex, osWaitForever);
}

void exit_critical_section(void) {
  osMutexRelease(queueMutex);
}


// 静态变量
static TaskType taskQueue[QUEUE_SIZE];
static __IO uint8_t queueHead = 0;
static __IO uint8_t queueTail = 0;

// RTC中断服务程序    在漏水，超时等状态下不添加队列；在治水状态下延迟设计
void RTC_IRQHandler(void) {
  if (__HAL_RTC_ALARM_GET_FLAG(&hrtc) != RESET) {
    __HAL_RTC_ALARM_CLEAR_FLAG(&hrtc);
		
		 if (!isWaterTreatmentActive && !isLeakAlarm && !isRinsingActive) {
    FlushScheduler_AddTasks();
  }
}

// 添加任务到队列
void FlushScheduler_AddTasks(void) {
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;
  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  if (sTime.Hours == 1 && sTime.Minutes == 0 && sTime.Seconds == 0) {
		    enter_critical_section();
    if (queueTail < QUEUE_SIZE) {
			//添加常规冲洗任务
      taskQueue[queueTail++] = TASK_F1;
      taskQueue[queueTail++] = TASK_F2;
      taskQueue[queueTail++] = TASK_F3;
      taskQueue[queueTail++] = TASK_F4;
      taskQueue[queueTail++] = TASK_F5;
			// 检查是否为每月的第一天，如果是则添加F6任务
      if (sDate.Date == 1) {
        taskQueue[queueTail++] = TASK_F6;
    }
  }
}
}



// 执行任务
void FlushScheduler_ExecuteTask(TaskType taskType) {
  switch (taskType) {
    case TASK_F1: operateF1(); break; // 实现operateF1()函数
    case TASK_F2: operateF2(); break; // 实现operateF2()函数
		case TASK_F3: operateF3(); break;
		case TASK_F4: operateF4(); break;
		case TASK_F5: operateF5(); break;
		case TASK_F6: operateF6(); break;
    // ... 其他任务执行代码
    default: break;
  }
}

// 初始化
void FlushScheduler_Init(void) {
	// 初始化队列
    queueHead = 0;
    queueTail = 0;
  // 初始化硬件资源
		MX_RTC_Init();
}

// 主循环   当一天6个冲洗逻辑完成，队列未空，第二天继续添加队列
void FlushScheduler_MainLoop(void) {
    enter_critical_section();
    if (queueHead != queueTail) {
        TaskType currentTask = taskQueue[queueHead];
        FlushScheduler_ExecuteTask(currentTask);
        queueHead = (queueHead + 1) % QUEUE_SIZE;
    }
    exit_critical_section();
}


void MX_RTC_Init(void) {
	
    // RTC初始化代码
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    // 1. 启用PWR和BKP时钟
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();

    // 2. 解除备份寄存器的写保护
    HAL_PWR_EnableBkUpAccess();

    // 3. 初始化RTC并设置时间、日期
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND; // 自动产生1秒中断
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE; // 不输出时钟信号
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH; // 输出极性高
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN; // 开漏输出

    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        // 初始化错误处理
        Error_Handler();
    }
		
		 // 尝试从网络获取时间
    if (NTP_GetTime(&sTime, &sDate) == NTP_OK)
    {
        // 如果成功获取时间，保存时间并设置RTC
        savedTime = sTime;
        savedDate = sDate;
        if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
        {
            // 时间设置错误处理
            Error_Handler();
        }

        if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
        {
            // 日期设置错误处理
            Error_Handler();
        }
    }
    else
    {
        // 如果无法从网络获取时间，检查是否之前保存过时间
        if (savedTime.Hours != 0 || savedDate.Date != 0)
        {
            // 使用之前保存的时间设置RTC
            if (HAL_RTC_SetTime(&hrtc, &savedTime, RTC_FORMAT_BIN) != HAL_OK)
            {
                // 时间设置错误处理
                Error_Handler();
            }

            if (HAL_RTC_SetDate(&hrtc, &savedDate, RTC_FORMAT_BIN) != HAL_OK)
            {
                // 日期设置错误处理
                Error_Handler();
            }
        }
        else
        {
            // 如果之前没有保存过时间，使用默认时间
            sTime.Hours = 0x0;
            sTime.Minutes = 0x0;
            sTime.Seconds = 0x0;
            sTime.TimeFormat = RTC_HOURFORMAT_24;
            sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
            sTime.StoreOperation = RTC_STOREOPERATION_RESET;

            sDate.WeekDay = RTC_WEEKDAY_MONDAY;
            sDate.Month = RTC_MONTH_JANUARY;
            sDate.Date = 0x1;
            sDate.Year = 0x0;

            // 设置默认时间到RTC
            if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
            {
                // 时间设置错误处理
                Error_Handler();
            }

            if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
            {
                // 日期设置错误处理
                Error_Handler();
            }
        }
			}

}

void Error_Handler(void)
{
    // 可以在这里添加错误处理代码
    // 例如，进入死循环，或者使用LED闪烁等方法提示错误
    while(1)
    {
    }
}

//// 冲洗任务执行函数
//void RinseHandler(void) {
//  // 执行冲洗操作
//  isRinsingActive = 1; // 标记正在冲洗

//  // 等待冲洗完成
//  // ...
//  isRinsingActive = 0; // 清除冲洗标志
//}


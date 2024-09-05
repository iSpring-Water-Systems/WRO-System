#include "rinse_scheduler.h"
#include "cmsis_os.h" // �������ϵͳͷ�ļ�
#include "ntp_client.h" // ��������һ��NTP�ͻ��˵�ʵ��


RTC_HandleTypeDef hrtc;

// ����һ��ȫ�ֱ��������ڱ���֮ǰ��ȡ��ʱ��
RTC_TimeTypeDef savedTime = {0}; // ����֮ǰ��ȡ��ʱ��
RTC_DateTypeDef savedDate = {0}; // ����֮ǰ��ȡ������

//ʹ���ٽ籣�����жӲ���
osMutexId_t queueMutex = osMutexCreate(osMutex(QueueMutex));

void enter_critical_section(void) {
  osMutexAcquire(queueMutex, osWaitForever);
}

void exit_critical_section(void) {
  osMutexRelease(queueMutex);
}


// ��̬����
static TaskType taskQueue[QUEUE_SIZE];
static __IO uint8_t queueHead = 0;
static __IO uint8_t queueTail = 0;

// RTC�жϷ������    ��©ˮ����ʱ��״̬�²���Ӷ��У�����ˮ״̬���ӳ����
void RTC_IRQHandler(void) {
  if (__HAL_RTC_ALARM_GET_FLAG(&hrtc) != RESET) {
    __HAL_RTC_ALARM_CLEAR_FLAG(&hrtc);
		
		 if (!isWaterTreatmentActive && !isLeakAlarm && !isRinsingActive) {
    FlushScheduler_AddTasks();
  }
}

// ������񵽶���
void FlushScheduler_AddTasks(void) {
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;
  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  if (sTime.Hours == 1 && sTime.Minutes == 0 && sTime.Seconds == 0) {
		    enter_critical_section();
    if (queueTail < QUEUE_SIZE) {
			//��ӳ����ϴ����
      taskQueue[queueTail++] = TASK_F1;
      taskQueue[queueTail++] = TASK_F2;
      taskQueue[queueTail++] = TASK_F3;
      taskQueue[queueTail++] = TASK_F4;
      taskQueue[queueTail++] = TASK_F5;
			// ����Ƿ�Ϊÿ�µĵ�һ�죬����������F6����
      if (sDate.Date == 1) {
        taskQueue[queueTail++] = TASK_F6;
    }
  }
}
}



// ִ������
void FlushScheduler_ExecuteTask(TaskType taskType) {
  switch (taskType) {
    case TASK_F1: operateF1(); break; // ʵ��operateF1()����
    case TASK_F2: operateF2(); break; // ʵ��operateF2()����
		case TASK_F3: operateF3(); break;
		case TASK_F4: operateF4(); break;
		case TASK_F5: operateF5(); break;
		case TASK_F6: operateF6(); break;
    // ... ��������ִ�д���
    default: break;
  }
}

// ��ʼ��
void FlushScheduler_Init(void) {
	// ��ʼ������
    queueHead = 0;
    queueTail = 0;
  // ��ʼ��Ӳ����Դ
		MX_RTC_Init();
}

// ��ѭ��   ��һ��6����ϴ�߼���ɣ�����δ�գ��ڶ��������Ӷ���
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
	
    // RTC��ʼ������
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    // 1. ����PWR��BKPʱ��
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();

    // 2. ������ݼĴ�����д����
    HAL_PWR_EnableBkUpAccess();

    // 3. ��ʼ��RTC������ʱ�䡢����
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND; // �Զ�����1���ж�
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE; // �����ʱ���ź�
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH; // ������Ը�
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN; // ��©���

    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        // ��ʼ��������
        Error_Handler();
    }
		
		 // ���Դ������ȡʱ��
    if (NTP_GetTime(&sTime, &sDate) == NTP_OK)
    {
        // ����ɹ���ȡʱ�䣬����ʱ�䲢����RTC
        savedTime = sTime;
        savedDate = sDate;
        if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
        {
            // ʱ�����ô�����
            Error_Handler();
        }

        if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
        {
            // �������ô�����
            Error_Handler();
        }
    }
    else
    {
        // ����޷��������ȡʱ�䣬����Ƿ�֮ǰ�����ʱ��
        if (savedTime.Hours != 0 || savedDate.Date != 0)
        {
            // ʹ��֮ǰ�����ʱ������RTC
            if (HAL_RTC_SetTime(&hrtc, &savedTime, RTC_FORMAT_BIN) != HAL_OK)
            {
                // ʱ�����ô�����
                Error_Handler();
            }

            if (HAL_RTC_SetDate(&hrtc, &savedDate, RTC_FORMAT_BIN) != HAL_OK)
            {
                // �������ô�����
                Error_Handler();
            }
        }
        else
        {
            // ���֮ǰû�б����ʱ�䣬ʹ��Ĭ��ʱ��
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

            // ����Ĭ��ʱ�䵽RTC
            if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
            {
                // ʱ�����ô�����
                Error_Handler();
            }

            if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
            {
                // �������ô�����
                Error_Handler();
            }
        }
			}

}

void Error_Handler(void)
{
    // ������������Ӵ��������
    // ���磬������ѭ��������ʹ��LED��˸�ȷ�����ʾ����
    while(1)
    {
    }
}

//// ��ϴ����ִ�к���
//void RinseHandler(void) {
//  // ִ�г�ϴ����
//  isRinsingActive = 1; // ������ڳ�ϴ

//  // �ȴ���ϴ���
//  // ...
//  isRinsingActive = 0; // �����ϴ��־
//}


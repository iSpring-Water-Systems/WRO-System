#ifndef RTC_H
#define RTC_H

#include "stm32f1xx_hal.h"

// RTC模块初始化
void RTC_Init(void);

// 从云端获取时间并更新RTC
RTC_TimeTypeDef* RTC_UpdateTimeFromCloud(void);

// 获取当前RTC时间
void RTC_GetTime(RTC_TimeTypeDef* timeStruct);

// 获取当前RTC日期
void RTC_GetDate(RTC_DateTypeDef* dateStruct);

#endif // RTC_MODULE_H
#ifndef RTC_H
#define RTC_H

#include "stm32f1xx_hal.h"

// RTCģ���ʼ��
void RTC_Init(void);

// ���ƶ˻�ȡʱ�䲢����RTC
RTC_TimeTypeDef* RTC_UpdateTimeFromCloud(void);

// ��ȡ��ǰRTCʱ��
void RTC_GetTime(RTC_TimeTypeDef* timeStruct);

// ��ȡ��ǰRTC����
void RTC_GetDate(RTC_DateTypeDef* dateStruct);

#endif // RTC_MODULE_H
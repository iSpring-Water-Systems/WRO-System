#include "rtc.h"
#include "ntp_client.h" // ��������һ��NTP�ͻ��˵�ʵ��

RTC_HandleTypeDef hrtc;

void RTC_Init(void)
{
    // RTC��ʼ������...
}

RTC_TimeTypeDef* RTC_UpdateTimeFromCloud(void)
{
    static RTC_TimeTypeDef savedTime = {0};
    static RTC_DateTypeDef savedDate = {0};

    // ���Դ��ƶ˻�ȡʱ��
    if (NTP_TryToUpdateTime(&savedTime, &savedDate) == NTP_OK)
    {
        // ����ɹ���ȡʱ�䣬����RTC
        if (HAL_RTC_SetTime(&hrtc, &savedTime, RTC_FORMAT_BIN) != HAL_OK)
        {
            // ʱ�����ô�����
        }
        if (HAL_RTC_SetDate(&hrtc, &savedDate, RTC_FORMAT_BIN) != HAL_OK)
        {
            // �������ô�����
        }
    }

    // ����ָ�򱣴�ʱ���ָ��
    return &savedTime;
}

void RTC_GetTime(RTC_TimeTypeDef* timeStruct)
{
    if (HAL_RTC_GetTime(&hrtc, timeStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        // ʱ���ȡ������
    }
}

void RTC_GetDate(RTC_DateTypeDef* dateStruct)
{
    if (HAL_RTC_GetDate(&hrtc, dateStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        // ���ڻ�ȡ������
    }
}
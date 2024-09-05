#include "rtc.h"
#include "ntp_client.h" // 假设你有一个NTP客户端的实现

RTC_HandleTypeDef hrtc;

void RTC_Init(void)
{
    // RTC初始化代码...
}

RTC_TimeTypeDef* RTC_UpdateTimeFromCloud(void)
{
    static RTC_TimeTypeDef savedTime = {0};
    static RTC_DateTypeDef savedDate = {0};

    // 尝试从云端获取时间
    if (NTP_TryToUpdateTime(&savedTime, &savedDate) == NTP_OK)
    {
        // 如果成功获取时间，更新RTC
        if (HAL_RTC_SetTime(&hrtc, &savedTime, RTC_FORMAT_BIN) != HAL_OK)
        {
            // 时间设置错误处理
        }
        if (HAL_RTC_SetDate(&hrtc, &savedDate, RTC_FORMAT_BIN) != HAL_OK)
        {
            // 日期设置错误处理
        }
    }

    // 返回指向保存时间的指针
    return &savedTime;
}

void RTC_GetTime(RTC_TimeTypeDef* timeStruct)
{
    if (HAL_RTC_GetTime(&hrtc, timeStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        // 时间获取错误处理
    }
}

void RTC_GetDate(RTC_DateTypeDef* dateStruct)
{
    if (HAL_RTC_GetDate(&hrtc, dateStruct, RTC_FORMAT_BIN) != HAL_OK)
    {
        // 日期获取错误处理
    }
}
#include "./BSP/Valve/valve.h"

/**
 * @brief       初始化阀门相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void valve_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    FV1_GPIO_CLK_ENABLE(); // FV1时钟使能
    FV2_GPIO_CLK_ENABLE(); // FV2时钟使能
    FV3_GPIO_CLK_ENABLE(); // FV3时钟使能
    INV_GPIO_CLK_ENABLE(); // 进水阀时钟使能
    MIXV_GPIO_CLK_ENABLE(); // 双向阀时钟使能

    // FV1初始化
    gpio_init_struct.Pin = FV1_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(FV1_GPIO_PORT, &gpio_init_struct);

    // FV2初始化
    gpio_init_struct.Pin = FV2_GPIO_PIN;
    HAL_GPIO_Init(FV2_GPIO_PORT, &gpio_init_struct);

    // FV3初始化
    gpio_init_struct.Pin = FV3_GPIO_PIN;
    HAL_GPIO_Init(FV3_GPIO_PORT, &gpio_init_struct);

    // inV初始化
    gpio_init_struct.Pin = INV_GPIO_PIN;
    HAL_GPIO_Init(INV_GPIO_PORT, &gpio_init_struct);

    // MixV初始化
    gpio_init_struct.Pin = MIXV_GPIO_PIN;
    HAL_GPIO_Init(MIXV_GPIO_PORT, &gpio_init_struct);

    // 关闭所有阀门
    FV1_set(1);
    FV2_set(1);
    FV3_set(1);
    inV_set(1);
    MixV_set(1);
}

void FV1_set(int state)
{
    HAL_GPIO_WritePin(FV1_GPIO_PORT, FV1_GPIO_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void FV2_set(int state)
{
    HAL_GPIO_WritePin(FV2_GPIO_PORT, FV2_GPIO_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void FV3_set(int state)
{
    HAL_GPIO_WritePin(FV3_GPIO_PORT, FV3_GPIO_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void inV_set(int state)
{
    HAL_GPIO_WritePin(INV_GPIO_PORT, INV_GPIO_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void MixV_set(int state)
{
    HAL_GPIO_WritePin(MIXV_GPIO_PORT, MIXV_GPIO_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
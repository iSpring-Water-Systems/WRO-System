#include "./BSP/Valve/valve.h"

/**
 * @brief       ��ʼ���������IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void valve_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    FV1_GPIO_CLK_ENABLE(); // FV1ʱ��ʹ��
    FV2_GPIO_CLK_ENABLE(); // FV2ʱ��ʹ��
    FV3_GPIO_CLK_ENABLE(); // FV3ʱ��ʹ��
    INV_GPIO_CLK_ENABLE(); // ��ˮ��ʱ��ʹ��
    MIXV_GPIO_CLK_ENABLE(); // ˫��ʱ��ʹ��

    // FV1��ʼ��
    gpio_init_struct.Pin = FV1_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(FV1_GPIO_PORT, &gpio_init_struct);

    // FV2��ʼ��
    gpio_init_struct.Pin = FV2_GPIO_PIN;
    HAL_GPIO_Init(FV2_GPIO_PORT, &gpio_init_struct);

    // FV3��ʼ��
    gpio_init_struct.Pin = FV3_GPIO_PIN;
    HAL_GPIO_Init(FV3_GPIO_PORT, &gpio_init_struct);

    // inV��ʼ��
    gpio_init_struct.Pin = INV_GPIO_PIN;
    HAL_GPIO_Init(INV_GPIO_PORT, &gpio_init_struct);

    // MixV��ʼ��
    gpio_init_struct.Pin = MIXV_GPIO_PIN;
    HAL_GPIO_Init(MIXV_GPIO_PORT, &gpio_init_struct);

    // �ر����з���
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
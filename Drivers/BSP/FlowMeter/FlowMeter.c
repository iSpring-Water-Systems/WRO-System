//#include "stm32f1xx_hal.h"
//#include "./BSP/FlowMeter/FlowMeter.h"
//#include <stdio.h>


//// 全局变量
//FlowMeter flowMeter;

//// 假设使用了 GPIOA 的 PA0 引脚作为外部中断输入
//#define FLOWMETER_PIN GPIO_PIN_0
//#define FLOWMETER_GPIO_PORT GPIOA

//// 外部中断回调函数
//void exti0_callback(void) {
//    flowMeterCount(&flowMeter);
//}

//// 初始化 FlowMeter
//void init_flow_meter() {
//    // 配置 GPIO 为输入模式
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    __HAL_RCC_GPIOA_CLK_ENABLE();  // 启用 GPIOA 时钟
//    GPIO_InitStruct.Pin = FLOWMETER_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // 假设使用上升沿触发
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(FLOWMETER_GPIO_PORT, &GPIO_InitStruct);

//    // 配置外部中断
//    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
//    HAL_GPIO_EXTI_ConfigPort(FLOWMETER_GPIO_PORT);

//    // 创建 FlowMeter 结构体
//    FlowMeter flowMeter;
//    flowMeterInit(&flowMeter, FLOWMETER_PIN, FS300A, exti0_callback, EXTI_MODE_RISING);
//    flowMeterReset(&flowMeter);
//}

//// 外部中断处理函数
//void EXTI0_IRQHandler(void) {
//    HAL_GPIO_EXTI_IRQHandler(FLOWMETER_PIN);
//}


//#include "stm32f1xx_hal.h"
//#include "./BSP/FlowMeter/FlowMeter.h"
//#include <stdio.h>


//// ȫ�ֱ���
//FlowMeter flowMeter;

//// ����ʹ���� GPIOA �� PA0 ������Ϊ�ⲿ�ж�����
//#define FLOWMETER_PIN GPIO_PIN_0
//#define FLOWMETER_GPIO_PORT GPIOA

//// �ⲿ�жϻص�����
//void exti0_callback(void) {
//    flowMeterCount(&flowMeter);
//}

//// ��ʼ�� FlowMeter
//void init_flow_meter() {
//    // ���� GPIO Ϊ����ģʽ
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    __HAL_RCC_GPIOA_CLK_ENABLE();  // ���� GPIOA ʱ��
//    GPIO_InitStruct.Pin = FLOWMETER_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // ����ʹ�������ش���
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(FLOWMETER_GPIO_PORT, &GPIO_InitStruct);

//    // �����ⲿ�ж�
//    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
//    HAL_GPIO_EXTI_ConfigPort(FLOWMETER_GPIO_PORT);

//    // ���� FlowMeter �ṹ��
//    FlowMeter flowMeter;
//    flowMeterInit(&flowMeter, FLOWMETER_PIN, FS300A, exti0_callback, EXTI_MODE_RISING);
//    flowMeterReset(&flowMeter);
//}

//// �ⲿ�жϴ�����
//void EXTI0_IRQHandler(void) {
//    HAL_GPIO_EXTI_IRQHandler(FLOWMETER_PIN);
//}


#include "stm32f1xx_hal.h"  // ����ʵ��ʹ�õ�STM32ϵ��ѡ����ʵ�ͷ�ļ�
#include "FlowMeter.h"

// ����ʹ���� GPIOA �� PA0 ������Ϊ�ⲿ�ж�����
#define FLOWMETER_PIN GPIO_PIN_0
#define FLOWMETER_GPIO_PORT GPIOA

class FlowMeter {
public:
    FlowMeter(uint32_t pin, FlowSensorProperties prop, void (*callback)(void), uint8_t interruptMode);
    double getCurrentFlowrate();
    double getCurrentVolume();
    double getTotalFlowrate();
    double getTotalVolume();
    void tick(unsigned long duration);
    void count();
    void reset();
    unsigned int getPin();
    unsigned long getCurrentDuration();
    double getCurrentFrequency();
    double getCurrentError();
    unsigned long getTotalDuration();
    double getTotalError();
    FlowMeter* setTotalDuration(unsigned long totalDuration);
    FlowMeter* setTotalVolume(double totalVolume);
    FlowMeter* setTotalCorrection(double totalCorrection);

private:
    uint32_t _pin;
    FlowSensorProperties _properties;
    void (*_interruptCallback)(void);
    uint8_t _interruptMode;

    // ����˽�г�Ա����...
};

extern "C" void EXTI0_IRQHandler(void) {
    // �����ⲿ�ж�
    HAL_GPIO_EXTI_IRQHandler(FLOWMETER_PIN);
    FlowMeter::getInstance()->count();  // ������һ����̬������ȡʵ��
}

void FlowMeter::count() {
    // ʵ�ּ����߼�
}

// ���캯��ʵ��
FlowMeter::FlowMeter(uint32_t pin, FlowSensorProperties prop, void (*callback)(void), uint8_t interruptMode) : 
    _pin(pin), _properties(prop), _interruptCallback(callback), _interruptMode(interruptMode) {

    // ���� GPIO Ϊ����ģʽ
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();  // ���� GPIOA ʱ��
    GPIO_InitStruct.Pin = FLOWMETER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  // ����ʹ���½��ش���
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(FLOWMETER_GPIO_PORT, &GPIO_InitStruct);

    // �����ⲿ�ж�
    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    HAL_GPIO_EXTI_ConfigPort(FLOWMETER_GPIO_PORT);

    if (_interruptCallback != nullptr) {
        // ������Խ�һ�������ж�
    }

    reset();
}
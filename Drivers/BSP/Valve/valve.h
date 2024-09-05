#ifndef _VALVE_H
#define _VALVE_H
#include "./SYSTEM/sys/sys.h"

// 阀门GPIO定义
#define FV1_GPIO_PORT                  GPIOA
#define FV1_GPIO_PIN                   GPIO_PIN_0
#define FV1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define FV2_GPIO_PORT                  GPIOA
#define FV2_GPIO_PIN                   GPIO_PIN_1
#define FV2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define FV3_GPIO_PORT                  GPIOA
#define FV3_GPIO_PIN                   GPIO_PIN_2
#define FV3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)

#define INV_GPIO_PORT                  GPIOB
#define INV_GPIO_PIN                   GPIO_PIN_1
#define INV_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define MIXV_GPIO_PORT                 GPIOB
#define MIXV_GPIO_PIN                  GPIO_PIN_2
#define MIXV_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

// 阀门控制函数定义
void valve_init(void); // 初始化阀门IO口
void FV1_set(int state);
void FV2_set(int state);
void FV3_set(int state);
void inV_set(int state);
void MixV_set(int state);

// 阀门状态切换（开/关）
#define FV1_TOGGLE()    do{ HAL_GPIO_TogglePin(FV1_GPIO_PORT, FV1_GPIO_PIN); }while(0)
#define FV2_TOGGLE()    do{ HAL_GPIO_TogglePin(FV2_GPIO_PORT, FV2_GPIO_PIN); }while(0)
#define FV3_TOGGLE()    do{ HAL_GPIO_TogglePin(FV3_GPIO_PORT, FV3_GPIO_PIN); }while(0)
#define INV_TOGGLE()    do{ HAL_GPIO_TogglePin(INV_GPIO_PORT, INV_GPIO_PIN); }while(0)
#define MIXV_TOGGLE()   do{ HAL_GPIO_TogglePin(MIXV_GPIO_PORT, MIXV_GPIO_PIN); }while(0)

#endif



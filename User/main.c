/**
 ****************************************************************************************************
 * @file        main.c
 * @author      马绪会
 * @version     V1.0
 * @date        2024-08-23
 * @brief       WRO净水器
 * @license     
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STM32F103开发板
 
 *
 ****************************************************************************************************
 */
 #include <stdbool.h>
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
//#include "./BSP/NORFLASH/norflash.h"

//#include "　./AWS/mqtt_client.h"              //此库待定
#include "BSP/FlowMeter/FlowMeter.h" 
 
/* 定义相关外设引脚*/
//define TDS_SENSOR_UART_PORT &huart1
//define FLOW_SENSOR_PIN GPIO_PIN_0
//define FLOW_SENSOR_GPIO_PORT GPIOA
//define LED_STATUS_PIN GPIO_PIN_1


/* 全局变量 */
uint32_t tankWeight = 0; // 水箱重量
uint32_t totalFlow = 0; // 累计流量
uint16_t tdsValue = 0;  // TDS值




/* 用于跟踪冲洗计划状态*/
bool openF1Enable = false;
bool openF2Enable = false;
bool openF3Enable = false;
bool openF4Enable = false;
bool openF5Enable = false;
bool openF6Enable = false;
bool logic2Enable = false;

/* 函数原型*/
void operateF1(void);
void operateF2(void);
void operateF3(void);
void operateF4(void);
void operateF5(void);
void operateF6(void);
void checkTime(void);

/* 时钟外设等初始化*/
void SystemClock_Config(void);
// 初始化RTC模块
void  MX_RTC_Init();  

void Error_Handler(void);
void led_init(void);
void valve_init(void);
//void Error_Handler(void);
//void MQTT_Init(void);      
//void Sensor_Init(void);//传感器初始化
//void Valve_Init(void);//阀门初始化
//void Pump_Init(void);//泵初始化
//void Schedule_Flush(void);
//void Control_Logics(void);
//void Display_Update(void);




int main(void) {
	
	
	
	
	

                                                       
    SystemClock_Config();
	
//		Hardware_Init();				//初始化外围硬件
//    MX_USART_Init(); //TDS传感器
//    Sensor_Init(); // 初始化传感器
//    MQTT_Init();   //初始化MQTT
//    Display_Update(); // 初始化显示屏
//	
 /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	// 初始化冲洗调度器
    FlushScheduler_Init();
	led_init;//指示灯初始化
	valve_init;//阀门初始化
	
//	user_init_program();

    /* 循环体 */
    while (1) {
		
		
	//	 user_main_program();
	//	flowMeterTick(&flowMeter, 1000);
//        double currentFlowrate = flowMeterGetCurrentFlowrate(&flowMeter);
//        double currentVolume = flowMeterGetCurrentVolume(&flowMeter);
//        printf("Current Flowrate: %.2f l/min, Current Volume: %.2f l\n", currentFlowrate, currentVolume);
		
			// 先从云端更新时间，如果未连云取系统时间
		//	Update_Time_Client();
			 /* 读取传感器数据 */   
//				tankWeight = Sensor_Read_Weight();
//        totalFlow = Sensor_Read_Total_Flow();
//        tdsValue = Sensor_Read_TDS();

//			Control_Logics();
//			//定期检查时间用以执行冲洗计划
//			checkTime();
//			/MQTT尝试重连
//			if (!MQTT_IsConnected()) {
//            MQTT_Reconnect();
//        }
			// 简短延时
        HAL_Delay(1000);
//			
//			
//        if (MQTT_IsConnected()) {
//           
//            /* 更新显示 */
//            Display_Update();

//            /* 发布MQTT信息*/
//            Publish_MQTT_Data("tds/value", &tdsValue, sizeof(tdsValue));
//            Publish_MQTT_Data("flow/total", &totalFlow, sizeof(totalFlow));

//            /* 简短延迟，避免CPU过快*/
//            HAL_Delay(1000);
//        
    }
}

void SystemClock_Config(void)
{
	
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  } // 系统时钟配置代码
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

//************************************************************
//*	函数名称:	Hardware_Init
//*
//*	函数功能:	硬件初始化
//*
//*	入口参数:	?
//*
//*	????:	?
//*
//*	??:		??????????????
//************************************************************
//*/
//void Hardware_Init(void)
//{
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//?????????

//	Delay_Init();									//systick???
//	
//	Usart1_Init(115200);							//??1,?????
//	
//	Usart2_Init(115200);							//??2,??ESP8266?
//	
//  Key_Init();
//	
//	Led_Init();									//??????
//	
//	OLED_Init();			//???OLED  
//	
//	while(DHT11_Init())
//	{
////		UsartPrintf(USART_DEBUG, "DHT11 Error \r\n");
//		OLED_ShowString(0,0,"DHT11 Error",16);
//		DelayMs(1000);
//	}
//	
////	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
//	OLED_Clear(); OLED_ShowString(0,0,"Hardware init OK",16); DelayMs(1000);
//}

//void Error_Handler(void) {
//    //错误处理代码
//    while(1) {
//        LED_Toggle(LED_STATUS_PIN); // 错误指示灯闪烁
//        HAL_Delay(500);
//    }
//}

//void MQTT_Init(void) {
//    // MQTT初始化
//}

//void Sensor_Init(void) {
//    // 传感器初始化
//}

//uint16_t Read_TDS_Sensor(UART_HandleTypeDef *huart) {
//    //从TDS读取数据
//    return 0; 
//}

//uint32_t Read_Flow_Sensor(GPIO_TypeDef *gpio_port, uint16_t gpio_pin) {
//    // 冲流量传感器读取数据
//    return 0; 
//}

//void Publish_MQTT_Data(char *topic, void *data, size_t size) {
//    // 发布MQTT消息
//}

//void Display_Update(void) {
//    // 更新LCD显示
//    lcd_show_string(0, 0, 240, 16, 16, "TDS: ", BLUE);
//    lcd_show_string(40, 0, 240, 16, 16, (char *) &tdsValue, BLUE);
//    lcd_show_string(0, 20, 240, 16, 16, "Total Flow: ", BLUE);
//    lcd_show_string(80, 20, 240, 16, 16, (char *) &totalFlow, BLUE);
//}

//void Control_Logics(void) {
//    // 读取传感器数值
//    tankWeight = Read_Tank_Weight();
//    outFlow = Read_Out_Flow();
//    outTDS = Read_Out_TDS();
//		CheckLogic1();
//    CheckLogic2();
//    CheckLogic3();

//  // 根据传感器执行具体控制逻辑
//}
//void checkTime(void) {
//    time_t now = HAL_RTC_GetTime(&hrtc); // 从RTC获取当前时间
//    struct tm timeinfo;
//    // 将时间从time_t结构转换成tm结构
//    gmtime_s(&now, &timeinfo);

//    int currentHour = timeinfo.tm_hour;
//    int currentMinute = timeinfo.tm_min;
//    int currentSecond = timeinfo.tm_sec;
//    int currentDay = timeinfo.tm_mday;

//    // F1 
//    if (currentHour == 1 && currentMinute == 1 && !openF1Enable) {
//        operateF1();
//        HAL_Delay(61000); 
//        openF1Enable = false;
//    }
//    // F2 
//    if (currentHour == 1 && currentMinute == 2 && !openF2Enable) {
//        operateF2();
//        HAL_Delay(61000);
//        openF2Enable = false;
//    }
//    // F3
//    if (currentHour == 1 && currentMinute == 3 && !openF3Enable) {
//        operateF3();
//        HAL_Delay(61000);
//        openF3Enable = false;
//    }
//    // F4 
//    if (currentHour == 1 && currentMinute == 4 && currentSecond == 30 && !openF4Enable) {
//        operateF4();
//        HAL_Delay(31000); // 
//        openF4Enable = false;
//    }
//    // F5 
//    if (currentHour == 1 && currentMinute == 5 && !openF5Enable) {
//        operateF5();
//        HAL_Delay(31000);
//        openF5Enable = false;
//    }

//    // F6
//    if (ShouldRunMonthlyMaintenance(&timeinfo)) {
//        operateF6();
//    }
//		//时间的复位
//		if (currentHour == 23 && currentMinute == 59) { 
//        openF1Enable = false; openF2Enable = false; openF3Enable = false; 
//        openF4Enable = false; openF5Enable = false; openF6Enable = false;
//        logic2Enable = false;
//		
//}
//		
//void CheckLogic1(void) {
//    // 
//    if (weight < TANK_DEFAULT_WEIGHT * 2 / 3) {
//        Valve_Close(FV1); // ????FV1
//        Valve_Close(FV2); // ????FV2
//        Valve_Close(FV3); // ????FV3

//        UV_Light_Off(LED_UV_DRV); // ??UV?
//    }
//}

//void CheckLogic2(void) {
//    // 
//    if (outFlowRate > 2 && weight < TANK_DEFAULT_WEIGHT * 1 / 4 && !logic2Enable) {
//        operateF5(); // F5
//        startTime = Get_Epoch_Time(); // 
//        logic2Enable = true;
//        openF6Enable = true;
//    } else if (logic2Enable) {
//        unsigned long elapsedTime = Get_Epoch_Time() - startTime;
//        if (elapsedTime < 120) {
//            Pump_Start(MOTOR_DRV); // 
//        } else {
//            Pump_Stop(MOTOR_DRV); // 
//            logic2Enable = false;
//            openF6Enable = false;
//        }
//    }
//}

//void CheckLogic3(void) {
//    // TDS
//    if (tdsValue<45||tdsvalue>75{
//        Pump_Start(MOTOR_DRV); // 启动混合阀门
//    }
//}


















//#include "./SYSTEM/sys/sys.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./USMART/usmart.h"
//#include "./BSP/LED/led.h"
//#include "./BSP/LCD/lcd.h"
//#include "./BSP/KEY/key.h"
//#include "./BSP/NORFLASH/norflash.h"

///* 要写入到FLASH的字符串数组 */
//const uint8_t g_text_buf[] = {"STM32 SPI TEST"};

//#define TEXT_SIZE sizeof(g_text_buf) /* TEXT字符串长度 */

//int main(void)
//{
//    uint8_t key;
//    uint16_t i = 0;
//    uint8_t datatemp[TEXT_SIZE];
//    uint32_t flashsize;
//    uint16_t id = 0;

//    HAL_Init();                         /* 初始化HAL库 */
//    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
//    delay_init(72);                     /* 延时初始化 */
//    usart_init(115200);                 /* 串口初始化为115200 */
//    usmart_dev.init(72);                /* 初始化USMART */
//    led_init();                         /* 初始化LED */
//    lcd_init();                         /* 初始化LCD */
//    key_init();                         /* 初始化按键 */
//    norflash_init();                    /* 初始化NORFLASH */

//    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
//    lcd_show_string(30,  70, 200, 16, 16, "SPI TEST", RED);
//    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
//    lcd_show_string(30, 110, 200, 16, 16, "KEY1:Write  KEY0:Read", RED); /* 显示提示信息 */

//    id = norflash_read_id(); /* 读取FLASH ID */

//    while ((id == 0) || (id == 0XFFFF)) /* 检测不到FLASH芯片 */
//    {
//        lcd_show_string(30, 130, 200, 16, 16, "FLASH Check Failed!", RED);
//        delay_ms(500);
//        lcd_show_string(30, 130, 200, 16, 16, "Please Check!      ", RED);
//        delay_ms(500);
//        LED0_TOGGLE(); /* LED0闪烁 */
//    }

//    lcd_show_string(30, 130, 200, 16, 16, "SPI FLASH Ready!", BLUE);
//    flashsize = 16 * 1024 * 1024; /* FLASH 大小为16M字节 */

//    while (1)
//    {
//        key = key_scan(0);

//        if (key == KEY1_PRES) /* KEY1按下,写入 */
//        {
//            lcd_fill(0, 150, 239, 319, WHITE); /* 清除半屏 */
//            lcd_show_string(30, 150, 200, 16, 16, "Start Write FLASH....", BLUE);
//            sprintf((char *)datatemp, "%s%d", (char *)g_text_buf, i);
//            norflash_write((uint8_t *)datatemp, flashsize - 100, TEXT_SIZE);      /* 从倒数第100个地址处开始,写入SIZE长度的数据 */
//            lcd_show_string(30, 150, 200, 16, 16, "FLASH Write Finished!", BLUE); /* 提示传送完成 */
//        }

//        if (key == KEY0_PRES) /* KEY0按下,读取字符串并显示 */
//        {
//            lcd_show_string(30, 150, 200, 16, 16, "Start Read FLASH... . ", BLUE);
//            norflash_read(datatemp, flashsize - 100, TEXT_SIZE);                   /* 从倒数第100个地址处开始,读出SIZE个字节 */
//            lcd_show_string(30, 150, 200, 16, 16, "The Data Readed Is:   ", BLUE); /* 提示传送完成 */
//            lcd_show_string(30, 170, 200, 16, 16, (char *)datatemp, BLUE);         /* 显示读到的字符串 */
//        }

//        i++;

//        if (i == 20)
//        {
//            LED0_TOGGLE(); /* LED0闪烁 */
//            i = 0;
//        }

//        delay_ms(10);
//    }
//}

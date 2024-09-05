/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ������
 * @version     V1.0
 * @date        2024-08-23
 * @brief       WRO��ˮ��
 * @license     
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:STM32F103������
 
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

//#include "��./AWS/mqtt_client.h"              //�˿����
#include "BSP/FlowMeter/FlowMeter.h" 
 
/* ���������������*/
//define TDS_SENSOR_UART_PORT &huart1
//define FLOW_SENSOR_PIN GPIO_PIN_0
//define FLOW_SENSOR_GPIO_PORT GPIOA
//define LED_STATUS_PIN GPIO_PIN_1


/* ȫ�ֱ��� */
uint32_t tankWeight = 0; // ˮ������
uint32_t totalFlow = 0; // �ۼ�����
uint16_t tdsValue = 0;  // TDSֵ




/* ���ڸ��ٳ�ϴ�ƻ�״̬*/
bool openF1Enable = false;
bool openF2Enable = false;
bool openF3Enable = false;
bool openF4Enable = false;
bool openF5Enable = false;
bool openF6Enable = false;
bool logic2Enable = false;

/* ����ԭ��*/
void operateF1(void);
void operateF2(void);
void operateF3(void);
void operateF4(void);
void operateF5(void);
void operateF6(void);
void checkTime(void);

/* ʱ������ȳ�ʼ��*/
void SystemClock_Config(void);
// ��ʼ��RTCģ��
void  MX_RTC_Init();  

void Error_Handler(void);
void led_init(void);
void valve_init(void);
//void Error_Handler(void);
//void MQTT_Init(void);      
//void Sensor_Init(void);//��������ʼ��
//void Valve_Init(void);//���ų�ʼ��
//void Pump_Init(void);//�ó�ʼ��
//void Schedule_Flush(void);
//void Control_Logics(void);
//void Display_Update(void);




int main(void) {
	
	
	
	
	

                                                       
    SystemClock_Config();
	
//		Hardware_Init();				//��ʼ����ΧӲ��
//    MX_USART_Init(); //TDS������
//    Sensor_Init(); // ��ʼ��������
//    MQTT_Init();   //��ʼ��MQTT
//    Display_Update(); // ��ʼ����ʾ��
//	
 /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	// ��ʼ����ϴ������
    FlushScheduler_Init();
	led_init;//ָʾ�Ƴ�ʼ��
	valve_init;//���ų�ʼ��
	
//	user_init_program();

    /* ѭ���� */
    while (1) {
		
		
	//	 user_main_program();
	//	flowMeterTick(&flowMeter, 1000);
//        double currentFlowrate = flowMeterGetCurrentFlowrate(&flowMeter);
//        double currentVolume = flowMeterGetCurrentVolume(&flowMeter);
//        printf("Current Flowrate: %.2f l/min, Current Volume: %.2f l\n", currentFlowrate, currentVolume);
		
			// �ȴ��ƶ˸���ʱ�䣬���δ����ȡϵͳʱ��
		//	Update_Time_Client();
			 /* ��ȡ���������� */   
//				tankWeight = Sensor_Read_Weight();
//        totalFlow = Sensor_Read_Total_Flow();
//        tdsValue = Sensor_Read_TDS();

//			Control_Logics();
//			//���ڼ��ʱ������ִ�г�ϴ�ƻ�
//			checkTime();
//			/MQTT��������
//			if (!MQTT_IsConnected()) {
//            MQTT_Reconnect();
//        }
			// �����ʱ
        HAL_Delay(1000);
//			
//			
//        if (MQTT_IsConnected()) {
//           
//            /* ������ʾ */
//            Display_Update();

//            /* ����MQTT��Ϣ*/
//            Publish_MQTT_Data("tds/value", &tdsValue, sizeof(tdsValue));
//            Publish_MQTT_Data("flow/total", &totalFlow, sizeof(totalFlow));

//            /* ����ӳ٣�����CPU����*/
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
  } // ϵͳʱ�����ô���
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
//*	��������:	Hardware_Init
//*
//*	��������:	Ӳ����ʼ��
//*
//*	��ڲ���:	?
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
//    //���������
//    while(1) {
//        LED_Toggle(LED_STATUS_PIN); // ����ָʾ����˸
//        HAL_Delay(500);
//    }
//}

//void MQTT_Init(void) {
//    // MQTT��ʼ��
//}

//void Sensor_Init(void) {
//    // ��������ʼ��
//}

//uint16_t Read_TDS_Sensor(UART_HandleTypeDef *huart) {
//    //��TDS��ȡ����
//    return 0; 
//}

//uint32_t Read_Flow_Sensor(GPIO_TypeDef *gpio_port, uint16_t gpio_pin) {
//    // ��������������ȡ����
//    return 0; 
//}

//void Publish_MQTT_Data(char *topic, void *data, size_t size) {
//    // ����MQTT��Ϣ
//}

//void Display_Update(void) {
//    // ����LCD��ʾ
//    lcd_show_string(0, 0, 240, 16, 16, "TDS: ", BLUE);
//    lcd_show_string(40, 0, 240, 16, 16, (char *) &tdsValue, BLUE);
//    lcd_show_string(0, 20, 240, 16, 16, "Total Flow: ", BLUE);
//    lcd_show_string(80, 20, 240, 16, 16, (char *) &totalFlow, BLUE);
//}

//void Control_Logics(void) {
//    // ��ȡ��������ֵ
//    tankWeight = Read_Tank_Weight();
//    outFlow = Read_Out_Flow();
//    outTDS = Read_Out_TDS();
//		CheckLogic1();
//    CheckLogic2();
//    CheckLogic3();

//  // ���ݴ�����ִ�о�������߼�
//}
//void checkTime(void) {
//    time_t now = HAL_RTC_GetTime(&hrtc); // ��RTC��ȡ��ǰʱ��
//    struct tm timeinfo;
//    // ��ʱ���time_t�ṹת����tm�ṹ
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
//		//ʱ��ĸ�λ
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
//        Pump_Start(MOTOR_DRV); // ������Ϸ���
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

///* Ҫд�뵽FLASH���ַ������� */
//const uint8_t g_text_buf[] = {"STM32 SPI TEST"};

//#define TEXT_SIZE sizeof(g_text_buf) /* TEXT�ַ������� */

//int main(void)
//{
//    uint8_t key;
//    uint16_t i = 0;
//    uint8_t datatemp[TEXT_SIZE];
//    uint32_t flashsize;
//    uint16_t id = 0;

//    HAL_Init();                         /* ��ʼ��HAL�� */
//    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
//    delay_init(72);                     /* ��ʱ��ʼ�� */
//    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
//    usmart_dev.init(72);                /* ��ʼ��USMART */
//    led_init();                         /* ��ʼ��LED */
//    lcd_init();                         /* ��ʼ��LCD */
//    key_init();                         /* ��ʼ������ */
//    norflash_init();                    /* ��ʼ��NORFLASH */

//    lcd_show_string(30,  50, 200, 16, 16, "STM32", RED);
//    lcd_show_string(30,  70, 200, 16, 16, "SPI TEST", RED);
//    lcd_show_string(30,  90, 200, 16, 16, "ATOM@ALIENTEK", RED);
//    lcd_show_string(30, 110, 200, 16, 16, "KEY1:Write  KEY0:Read", RED); /* ��ʾ��ʾ��Ϣ */

//    id = norflash_read_id(); /* ��ȡFLASH ID */

//    while ((id == 0) || (id == 0XFFFF)) /* ��ⲻ��FLASHоƬ */
//    {
//        lcd_show_string(30, 130, 200, 16, 16, "FLASH Check Failed!", RED);
//        delay_ms(500);
//        lcd_show_string(30, 130, 200, 16, 16, "Please Check!      ", RED);
//        delay_ms(500);
//        LED0_TOGGLE(); /* LED0��˸ */
//    }

//    lcd_show_string(30, 130, 200, 16, 16, "SPI FLASH Ready!", BLUE);
//    flashsize = 16 * 1024 * 1024; /* FLASH ��СΪ16M�ֽ� */

//    while (1)
//    {
//        key = key_scan(0);

//        if (key == KEY1_PRES) /* KEY1����,д�� */
//        {
//            lcd_fill(0, 150, 239, 319, WHITE); /* ������� */
//            lcd_show_string(30, 150, 200, 16, 16, "Start Write FLASH....", BLUE);
//            sprintf((char *)datatemp, "%s%d", (char *)g_text_buf, i);
//            norflash_write((uint8_t *)datatemp, flashsize - 100, TEXT_SIZE);      /* �ӵ�����100����ַ����ʼ,д��SIZE���ȵ����� */
//            lcd_show_string(30, 150, 200, 16, 16, "FLASH Write Finished!", BLUE); /* ��ʾ������� */
//        }

//        if (key == KEY0_PRES) /* KEY0����,��ȡ�ַ�������ʾ */
//        {
//            lcd_show_string(30, 150, 200, 16, 16, "Start Read FLASH... . ", BLUE);
//            norflash_read(datatemp, flashsize - 100, TEXT_SIZE);                   /* �ӵ�����100����ַ����ʼ,����SIZE���ֽ� */
//            lcd_show_string(30, 150, 200, 16, 16, "The Data Readed Is:   ", BLUE); /* ��ʾ������� */
//            lcd_show_string(30, 170, 200, 16, 16, (char *)datatemp, BLUE);         /* ��ʾ�������ַ��� */
//        }

//        i++;

//        if (i == 20)
//        {
//            LED0_TOGGLE(); /* LED0��˸ */
//            i = 0;
//        }

//        delay_ms(10);
//    }
//}

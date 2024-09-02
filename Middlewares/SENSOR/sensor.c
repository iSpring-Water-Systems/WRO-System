//#include "sensor.h" 


//#include "weigh.h"
//#inlcude "Flowmeter.h"//等传感器的硬件抽象层
//// ……


////
//float Read_Flow_Sensor(void) {
//    float flowRate = 0.0f;
//    flowRate = HAL_Read_Flow_Sensor(FLOW_SENSOR_PIN);
//    return flowRate;
//}

//float Read_Weight_Sensor(void) {
//    float weight = 0.0f;
//    weight = HAL_Read_Weight_Sensor(WEIGHT_SENSOR_PIN);
//    return weight;
//}


//uint16_t Read_TDS_Sensor(void) {
//    uint16_t tdsValue = 0;
//    tdsValue = HAL_Read_TDS_Sensor(TDS_SENSOR_PIN);
//    return tdsValue;
//}

//void Sensor_Init(void) {
//    HAL_Init_Flow_Sensor(FLOW_SENSOR_PIN);
//    HAL_Init_Weight_Sensor(WEIGHT_SENSOR_PIN);
//    HAL_Init_TDS_Sensor(TDS_SENSOR_PIN);
//}

//#define CHECK_SENSOR_ERROR(expression) { \
//    SensorError_t error = (expression); \
//    if (error != SENSOR_ERROR_NONE) { \
//        Handle_Sensor_Error(error); \
//    } \
//}


//void Handle_Sensor_Error(SensorError_t error) {
//    switch (error) {
//        case FLOW_SENSOR_ERROR:
//					//处理错误
//            break;
//        case WEIGHT_SENSOR_ERROR:
//					//处理错误
//            break;
//        case TDS_SENSOR_ERROR:
//            ////处理错误
//            break;
//        // ...其他错误处理
//    }
//}


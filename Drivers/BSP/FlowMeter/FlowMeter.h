///**
// * Flow Meter
// *
// * A C language flow meter library that provides calibrated liquid flow and volume measurement with flow sensors.
// *
// * @author sekdiy (https://github.com/sekdiy/FlowMeter)
// * @date 14.07.2015 Initial release.
// * @version See git comments for changes.
// *
// * @todo Split up flow sensor and flow meter into different modules.
// */

//#ifndef FLOWMETER_H
//#define FLOWMETER_H

//#include "stm32f1xx_hal.h"  // 根据实际使用的STM32系列选择合适的头文件
//#include <stdio.h>  // 包含 printf 函数


//#define EXTI_MODE_RISING 1
//#define EXTI_MODE_FALLING 2
//#define EXTI_MODE_RISING_FALLING 3

///**
// * FlowSensorProperties
// *
// * Structure that holds essential information about a flow sensor.
// * Stores general sensor properties and calibration points.
// *
// * See file G34_Flow_rate_to_frequency.jpg for reference.
// */
//typedef struct {
//  double capacity;      //!< capacity, upper limit of flow rate (in l/min)
//  double kFactor;       //!< "k-factor" (in (pulses/s) / (l/min)), e.g.: 1 pulse/s = kFactor * l/min
//  double mFactor[10];   //!< multiplicative correction factor near unity, "meter factor" (per decile of flow)
//} FlowSensorProperties;

//extern FlowSensorProperties UncalibratedSensor; //!< default sensor
//extern FlowSensorProperties FS300A;             //!< see documentation about FS300A/SEN02141B
//extern FlowSensorProperties FS400A;             //!< see documentation about FS400A/USN-HS10TA

///**
// * FlowMeter
// */
//typedef struct {
//  uint32_t pin;                           //!< connection pin (has to be interrupt capable!)
//  FlowSensorProperties properties;        //!< sensor properties (including calibration data)
//  void (*interruptCallback)(void);        //!< interrupt callback
//  uint8_t interruptMode;                  //!< interrupt mode (LOW, CHANGE, RISING, FALLING, HIGH)

//  unsigned long currentDuration;          //!< current tick duration (convenience, in ms)
//  double currentFrequency;                //!< current pulses per second (convenience, in 1/s)
//  double currentFlowrate;                 //!< current flow rate (in l/tick), e.g.: 1 l / min = 1 pulse / s / (pulses / s / l / min)
//  double currentVolume;                   //!< current volume (in l), e.g.: 1 l = 1 (l / min) / (60 * s)
//  double currentCorrection;               //!< currently applied correction factor

//  unsigned long totalDuration;            //!< total measured duration since begin of measurement (in ms)
//  double totalVolume;                     //!< total volume since begin of measurement (in l)
//  double totalCorrection;                 //!< accumulated correction factors

//  volatile unsigned long currentPulses;   //!< pulses within current sample period
//} FlowMeter;

///**
// * Initializes a new flow meter object.
// *
// * @param flowMeter Pointer to the flow meter structure.
// * @param pin The pin that the flow sensor is connected to (has to be interrupt capable, default: GPIO_PIN_0).
// * @param prop The properties of the actual flow sensor being used (default: UncalibratedSensor).
// * @param callback The interrupt callback function (default: NULL).
// * @param interruptMode The interrupt mode (default: EXTI_MODE_RISING).
// */
//void flowMeterInit(FlowMeter *flowMeter, uint32_t pin, FlowSensorProperties prop, void (*callback)(void), uint8_t interruptMode);

//double flowMeterGetCurrentFlowrate(const FlowMeter *flowMeter); //!< Returns the current flow rate since last tick (in l/min).
//double flowMeterGetCurrentVolume(const FlowMeter *flowMeter);   //!< Returns the current volume since last tick (in l).

//double flowMeterGetTotalFlowrate(const FlowMeter *flowMeter); //!< Returns the (linear) average flow rate in this flow meter instance (in l/min).
//double flowMeterGetTotalVolume(const FlowMeter *flowMeter);   //!< Returns the total volume flown through this flow meter instance (in l).

///**
// * The tick method updates all internal calculations at the end of a measurement period.
// *
// * We're calculating flow and volume data over time.
// * The actual pulses have to be sampled using the count method (i.e. via an interrupt service routine).
// *
// * @param flowMeter Pointer to the flow meter structure.
// * @param duration The tick duration (in ms).
// */
//void flowMeterTick(FlowMeter *flowMeter, unsigned long duration);

//void flowMeterCount(FlowMeter *flowMeter); //!< Increments the internal pulse counter. Serves as an interrupt callback routine.
//void flowMeterReset(FlowMeter *flowMeter); //!< Prepares the flow meter for a fresh measurement. Resets all current values, but not the totals.

///**
// * Setters enabling continued metering across power cycles
// */
//void flowMeterSetTotalDuration(FlowMeter *flowMeter, unsigned long totalDuration); //!< Sets the total (overall) duration (i.e. after power up).
//void flowMeterSetTotalVolume(FlowMeter *flowMeter, double totalVolume);            //!< Sets the total (overall) volume (i.e. after power up).
//void flowMeterSetTotalCorrection(FlowMeter *flowMeter, double totalCorrection);    //!< Sets the total (overall) correction factor (i.e. after power up).

///**
// * Convenience methods and calibration helpers
// */
//uint32_t flowMeterGetPin(const FlowMeter *flowMeter); //!< Returns the STM32 pin number that the flow sensor is connected to.

//unsigned long flowMeterGetCurrentDuration(const FlowMeter *flowMeter); //!< Returns the duration of the current tick (in ms).
//double flowMeterGetCurrentFrequency(const FlowMeter *flowMeter);       //!< Returns the pulse rate in the current tick (in 1/s).
//double flowMeterGetCurrentError(const FlowMeter *flowMeter);           //!< Returns the error resulting from the current measurement (in %).

//unsigned long flowMeterGetTotalDuration(const FlowMeter *flowMeter);   //!< Returns the total run time of this flow meter instance (in ms).
//double flowMeterGetTotalError(const FlowMeter *flowMeter);             //!< Returns the (linear) average error of this flow meter instance (in %).


//void init_flow_meter();
//#endif   // FLOWMETER_H


// This .cpp file contains the functions for Battery level indication
#include <Arduino.h>
#include "0_Config.h"

float getBatteryVoltage() {
  int adcValue = analogRead(13);

  // .print(adcAttachPin);
  float voltage = adcValue * ADC_CALIBRATION_CONSTANT * R2 / (R1 + R2);
  return voltage;
}


int getBatteryPercentage() {
  float batteryVoltage = getBatteryVoltage();
  int percentage = map(batteryVoltage, MIN_BATTERY_VOLTAGE, MAX_BATTERY_VOLTAGE, 0, 100);
  percentage = constrain(percentage, 0, 100);
  return percentage;
}
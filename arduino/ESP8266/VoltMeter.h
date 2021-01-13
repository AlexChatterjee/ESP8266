#ifndef VOLT_METER_H
#define VOLT_METER_H
#include <Arduino.h>

class VoltMeter {
  private: 
    int voltMeterInput;
    int sensorValue;
    bool dividerOn;
    float dividerMultiplier; //(R1+R2)/R2
    
  public:
    VoltMeter();
    VoltMeter(int R1Value, int R2Value);
    
    void init();
    float getVoltage();
    int getSignal();
    float computeRealVoltage(int sensorValue);
  };
  
#endif

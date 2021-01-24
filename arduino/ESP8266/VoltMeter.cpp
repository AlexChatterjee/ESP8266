#include "VoltMeter.h"

VoltMeter::VoltMeter(bool verbose)
{
  this->verbose = verbose;
  this->dividerOn = false;
  this->dividerMultiplier = 0;  
  
  init();
}

VoltMeter::VoltMeter(int R1Value, int R2Value , bool verbose)
{
  this->verbose = verbose;
  this->dividerOn = true;
  this->dividerMultiplier = (R1Value+R2Value)/R2Value;
   
  init();
}

void VoltMeter::init()
{
  this->voltMeterInput = A0; //pin to be read
  this->sensorValue = 0;//0 to 1023, 0 to 3.3V on NodeMCU kit
}

float VoltMeter::getVoltage()
{
  if(this->verbose)
  {
    Serial.println("**********************");
    Serial.println("Divider cuircuit: "+String(this->dividerOn));    
  }

  return computeRealVoltage(getSignal());  
}

int VoltMeter::getSignal()
{
  return this->sensorValue = analogRead(this->voltMeterInput); 
}

float VoltMeter::computeRealVoltage(int sensorValue)
{
  if(this->verbose)
  {
    Serial.println("SensorValue: "+String(sensorValue));
  }
  
  float vinVoltage= 0.0;
  float realVoltage = 0.0;

  if(sensorValue!=0)
  {
    vinVoltage = (3.3*sensorValue)/1023;
  }
  
  if(this->verbose)
  {
    Serial.println("vinVoltage: "+String(vinVoltage));
  }


  if(this->dividerOn)
  {
    //calclate Vout
    realVoltage = vinVoltage*this->dividerMultiplier;
  }
  else
    realVoltage = vinVoltage;

  if(this->verbose)
  {
    Serial.println("realVoltage: "+String(realVoltage));
    Serial.println("**********************");
  }

  return realVoltage;
}

#include "Temp_and_hum_lib.h"
#include "DHT.h"

//define source pin for DHT11 sensor Pin D4 - pin2
#define DHT_SENSOR_TYPE DHT11
DHT dht(2, DHT_SENSOR_TYPE); //constant GPIO pin

TempAndHum::TempAndHum(int GPIONumber)
{
  this->GPIONumber = GPIONumber;
  init();
}

void TempAndHum::init()
{
  //Create DHT object
  dht.begin(); //!important: without it there is no correct communication with the sensor
}

float TempAndHum::getTemp()
{
  return dht.readTemperature();// Read temperature as Celsius (the default)
}

float TempAndHum::getHum()
{
  return dht.readHumidity();
}

String TempAndHum::getTempAndHumidity()
{ 
  float h = this->getHum();
  float t = this->getTemp();

  //if you get nan feedback, it means that your sensor is not correctly wired to the NodeMCU
  String returnString = "\"T\":"+String(t)+",\"H\":"+String(h);
  return returnString;
}

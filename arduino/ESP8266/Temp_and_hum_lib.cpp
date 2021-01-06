#include "Temp_and_hum_lib.h"
#include "DHT.h"

//define source pin for DHT11 sensor Pin D4 - pin2
#define DHT_PIN 2
#define DHT_SENSOR_TYPE DHT11

//Create DHT object
DHT dht(DHT_PIN, DHT_SENSOR_TYPE);

TempAndHum::TempAndHum()
{
  
}

void TempAndHum::init()
{
  
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
  
  while(isnan(h))
  {
      h = this->getHum();
      t = this->getTemp();
  }

  String jsonFormat = "{\"T\":"+String(t)+",\"H\":"+String(h)+"}";
  return jsonFormat;
}

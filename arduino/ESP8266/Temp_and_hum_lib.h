#ifndef TEMP_AND_HUM_LIB_H
#define TEMP_AND_HUM_LIB_H
#include <Arduino.h>

class TempAndHum {
  private:
    float getTemp();
    float getHum();
  public:
    TempAndHum();
    void init();
    String getTempAndHumidity();  
};

#endif

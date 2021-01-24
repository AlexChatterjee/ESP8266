#ifndef TEMP_AND_HUM_LIB_H
#define TEMP_AND_HUM_LIB_H
#include <Arduino.h>

class TempAndHum {
  private:
    int GPIONumber;
    float getTemp();
    float getHum();
    
  public:
    TempAndHum(int GPIONumber);
    void init();
    String getTempAndHumidity();  
};

#endif

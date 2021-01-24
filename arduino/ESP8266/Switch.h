#ifndef SWITCH_H
#define SWITCH_H
#include <Arduino.h>

class Switch {
  private: 
    int GPIONumber;
    bool verbose;
    
  public:
    Switch(int GPIONumber, bool verbose);
    
    void init();
    void setHIGH();
    void setLOW();
  };
  
#endif

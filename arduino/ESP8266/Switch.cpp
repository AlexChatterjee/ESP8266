#include "Switch.h"

Switch::Switch(int GPIONumber, bool verbose)
{
  this->GPIONumber = GPIONumber;
  this->verbose = verbose;
  
  init();
}

void Switch::init()
{
  pinMode(this->GPIONumber, OUTPUT); //pin is initialized as output
}

void Switch::setHIGH()
{
  if(this->verbose)
  {
    Serial.println("**********************");
    Serial.println("Setting HIGH signal");    
  }

  digitalWrite(this->GPIONumber, HIGH);
}

void Switch::setLOW()
{
  if(this->verbose)
  {
    Serial.println("**********************");
    Serial.println("Setting LOW signal");   
  }
  
  digitalWrite(this->GPIONumber, LOW);
}

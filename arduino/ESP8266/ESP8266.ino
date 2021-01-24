#include "WifiConnect.h"
#include "Temp_and_hum_lib.h"
#include "VoltMeter.h"
#include "Switch.h"

/*Wifi router information*/
char* ssid = "ALEXANDER";
char* password = "CHATTERJEE";
char* serverPath = "YOU WEBSITE PATH";

/*Divider circuit parameters*/
int R1Value = 10*1000; //10k
int R2Value = 1*1000; //1k

/*GPIO for controlling the DHT temperature module*/
int DHTPinNumber = 2; //TBD not taking the pin number for the moment

/*GPIO for controlling the relay module*/
int RelayPinNumber = 5;

/*debug parameters*/
const int serialBaudSpeed = 115200;

//Create WifiConnect object
WifiConnect wifiConnect(ssid,password,serverPath);

//Create TempAndHum object
TempAndHum tempAndHum(DHTPinNumber);

//Create voltMeter object without a divider connect to the nodeMCU kit
VoltMeter voltMeter(R1Value,R2Value,false); //no need of verbose

//Create voltMeter object without a divider connect to the nodeMCU kit
Switch switch1(RelayPinNumber,false);

/*
 * main functions being called - setup and loop
 */

void setup()
{
  Serial.print("function setup() ");
  /*
   * Serial connection config
   */
  Serial.print("Serial configuration ");
  Serial.begin(serialBaudSpeed);
  Serial.println();
  
  /*
   * ScanWifis until there is a proper connection
   */
  wifiConnect.scanWifi();
  wifiConnect.connectToWifi();
}

void loop()
{
  Serial.print("function loop() ");

  //measure voltage with open circuit
  float openCircuitVoltage = voltMeter.getVoltage();
  Serial.println("Open Circuit value:"+String(openCircuitVoltage));
  
  //close the NO/COM circuit
  switch1.setLOW();
  
  String payloadTemperature = tempAndHum.getTempAndHumidity(); 
  Serial.println("temperature and humidity value:"+payloadTemperature);

  float solarCellVoltage = voltMeter.getVoltage();
  Serial.println("Solar Cell Voltage value:"+String(solarCellVoltage));

  delay(1*1000); //1s pause
  
  //open the NO/COM circuit
  switch1.setHIGH();
  
  String payload = "{"+payloadTemperature+",\"VC\":"+String(solarCellVoltage)+",\"OC\":"+String(openCircuitVoltage)+"}";

  String api = "solar_cell_info.php";
  wifiConnect.sendHTTPRequest(api,payload);

  //delay(5*1000);
  delay(5*60*1000); //loop every 5 minutes
}

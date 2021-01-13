#include "WifiConnect.h"
#include "Temp_and_hum_lib.h"
#include "VoltMeter.h"

/*Wifi router information*/
char* ssid = "ALEXANDER";
char* password = "CHATTERJEE";
char* serverPath = "YOU WEBSITE PATH";

/*Divider circuit parameters*/
int R1Value = 10*1000; //10k
int R2Value = 1*1000; //1k

/*debug parameters*/
const int serialBaudSpeed = 115200;

//Create WifiConnect object
WifiConnect wifiConnect(ssid,password,serverPath);

//Create TempAndHum object
TempAndHum tempAndHum;

//Create voltMeter object without a divider connect to the nodeMCU kit
VoltMeter voltMeter(R1Value,R2Value);

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
  //get IO information
  String payload = tempAndHum.getTempAndHumidity(); //json payload has been changed

  //send information to the server
  String api = "tempAndHum.php";
  wifiConnect.sendHTTPRequest(api,payload);

  //you can build another api where you can send the voltage you just got
  voltMeter.getVoltage();
  
  //delay the loop for 30 seconds
  delay(1*1000); //1sec
}

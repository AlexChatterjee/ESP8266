#include "WifiConnect.h"
#include "Temp_and_hum_lib.h"

/*Wifi router information*/
char* ssid = "CHATTERJEE";
char* password = "ALEXANDER";
char* serverPath = "YOUR SERVER PATH";

/*debug parameters*/
const int serialBaudSpeed = 115200;

//Create WifiConnect object
WifiConnect wifiConnect(ssid,password,serverPath);
TempAndHum tempAndHum;

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

  wifiConnect.scanWifi();
  wifiConnect.connectToWifi();
}

void loop()
{
  Serial.print("function loop() ");
  String payload = tempAndHum.getTempAndHumidity(); //json payload has been changed
  String api = "tempAndHum.php";//replace with the api you want to consume
  wifiConnect.sendHTTPRequest(api,payload);
  delay(30000); //send a request every 30 seconds
}

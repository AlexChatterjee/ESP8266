#include "WifiConnect.h"

#include <ESP8266HTTPClient.h>
#include "ESP8266WiFi.h" //https://github.com/esp8266/Arduino

/*Wifi router information*/
WifiConnect::WifiConnect(char* ssid,char* password,char* serverPath)
{
    this->ssid = ssid;
    this->password = password;
    this->serverPath = serverPath; 
       
    init();
}
  
void WifiConnect::init()
{
  //vars config
  this->scanWifiBool = true;
  this->connectedToWifi = false;
  this->secureConnect = false;
  this->httpsPort = 443;
  
  /*
   * Wifi config
   */
  Serial.print("Wifi mode config ");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);  
}

void WifiConnect::scanWifi()
{
    Serial.print("function scanWifi() ");
    while(scanWifiBool!=false)
    {
      Serial.print("Scan start ... ");
      int n = WiFi.scanNetworks();
      Serial.print(n);
      Serial.println(" network(s) found");
      
      for (int i = 0; i < n; i++)
      {
        Serial.println(WiFi.SSID(i));
        if(WiFi.SSID(i).compareTo(ssid) == 0)
          scanWifiBool=false;
      }
      
      Serial.println();
      delay(5000); //redo the loop every 5 seconds   
    }
}

void WifiConnect::connectToWifi()
{
  Serial.print("function connectToWifi() ");
  // Connect to WiFi
  WiFi.begin(this->ssid, this->password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print(".");
  }
  
    connectedToWifi=true;
    Serial.print("Connected to ");  
    Serial.print(ssid);
}

void WifiConnect::sendHTTPRequest(String api, String payload)
{
  if(WiFi.status()== WL_CONNECTED)//connectedToWifi)
  {
     HTTPClient http;
     WiFiClientSecure client;
     
     String apiPath = String(serverPath)+api;//"tempAndHum.php";
     Serial.println("Debug apiPath: "+apiPath);

     //type of connection TLS or no security
     if(!secureConnect)//if https, do a unsecure connection
     {
        Serial.println("Debug: unsecure connection");
        client.setInsecure(); //the magic line, use with caution
        client.connect(apiPath, httpsPort);
     }
     else
     {
        //secure connection
       Serial.println("Debug: secure connection"); 
       //TBD create a secure connection      
     }
     
     if(http.begin(client,apiPath))
     {
        Serial.println("Debug: sucessful connection"); 
        //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        //sending json information to server
        http.addHeader("Content-Type", "application/json");

        //get payload from the board
        //String payload = getTempAndHumidity(); //json payload has been changed
        
        //get local ip and send some data
         Serial.println("Debug Payload to be sent:"+payload);
         
         int httpCode = http.POST(payload); //send it as a POST payload
         String response = http.getString();
         
         Serial.println("HTTP return code->"+httpCode);   //Print HTTP return code
         Serial.println("\nResponse from website->"+response);    //Print request response payload
    
         http.end();
     }
     else
     {
        Serial.println("Error: wrong HTTP connection connection");     
     }
  }
  else
    Serial.print("Can not send data as the device is not connected to the Internet");     
}

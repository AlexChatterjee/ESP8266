#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H
#include <Arduino.h>

class WifiConnect {
  private: 
    char* ssid;
    char* password;
    char* serverPath;
    
  public:
    bool scanWifiBool;
    bool connectedToWifi;
    bool secureConnect;
    uint16_t httpsPort;
    
    WifiConnect(char* ssid, char* password, char* serverPath);
    void init();
    void scanWifi();
    void connectToWifi();
    void sendHTTPRequest(String api, String payload);
  };
#endif


#ifndef ConnectWiFi_H
#define ConnectWiFi_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// #include "src/parsebytes.h"

class ConnectWiFi {
private:
  // IP address, Netmask and Gateway, populated when connected
  server.ip _ip;
  server.net _net;
  server.gw _gw;
  // Start with accesspoint mode disabled, wifi setup will activate it if no known networks are found, and WIFI_AP_ENABLE has been defined
  bool _accesspoint;
  // Number of known networks in stationList[]
  int _stationCount;
public:
  ConnectWiFi() {}  // Default Construction; DO NOT USE
  /** Constructor, that initialize timer
    * @param 
    */
  ConnectWiFi(server.ip ip, server.net net, server.gw gw, bool accesspoint, int stationCount);

  /** WiFi Init 
  * Initialize the WiFi
  */
  void init();

  /** WiFi Init 
  * Initialize the WiFi
  */
  void setupWifi();

  /** WiFi Init 
  * Initialize the WiFi
  */
  void loopWiFi();
};

#endif
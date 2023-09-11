
// Primary config, or defaults.
#if __has_include("myconfig.h")
    struct station { const char ssid[65]; const char password[65]; const bool dhcp;};  // do no edit
    #include "myconfig.h"
#else
    #warning "Using Defaults: Copy myconfig.sample.h to myconfig.h and edit that to use your own settings"
    #define WIFI_AP_ENABLE
    #define CAMERA_MODEL_AI_THINKER
    struct station { const char ssid[65]; const char password[65]; const bool dhcp;}
    stationList[] = {{"ESP32-CAM-CONNECT","InsecurePassword", true}};
#endif


#include "debug.h"
#include "wiFi.h"
#include "OTA.h"
#include "server.h"
#include "app_httpd.cpp"
#include "camera.h"
#include "light.h"

extern void setupDebug();
extern void setupWifi();
extern void setupOTA();
extern void setupServer();
extern void setupCamera();
extern void setupLight();

void setup () {
  setupDebug();
  setupWifi();
  setupOTA();
  setupServer();
  setupLight();
  setupCamera();
}

extern void loopWiFi();
void loop () {
  loopWiFi();
}
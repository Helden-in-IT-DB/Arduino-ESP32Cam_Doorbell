
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


void setup () {

}


#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

extern void serialDump();

class Debug {
  private:
    // Counters for info screens and debug
    int8_t streamCount = 0;          // Number of currently active streams
    unsigned long streamsServed = 0; // Total completed streams
    unsigned long imagesServed = 0;  // Total image requests
    // This will be displayed to identify the firmware
    char myVer[] PROGMEM = __DATE__ " @ " __TIME__;
    // Critical error string; if set during init (camera hardware failure) it will be returned for all http requests
    String critERR = "";
    // Debug flag for stream and capture data
    bool debugData;

  public:
    void init();
    void debugOn();
    void debugOff();
    void handleSerial();
    void printLocalTime(bool extraData=false);
    void setupDebug();

};
#endif
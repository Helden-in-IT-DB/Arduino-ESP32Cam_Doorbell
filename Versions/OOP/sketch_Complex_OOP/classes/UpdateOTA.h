// OTA Interface
#ifndef UpdateOTA_H
#define UpdateOTA_H

#include <Arduino.h>
#include <ArduinoOTA.h>

class UpdateOTA {
private:
  // Sketch Info
  int _sketchSize;
  int _sketchSpace;
  String _sketchMD5;
public:
  UpdateOTA(){}  // Default Construction; DO NOT USE

    /** Constructor, 
    * @param sketchSize {int} Size of the Sketch
    * @param sketchSpace {int} Free Sketch Space
    * @param sketchMD5 {String} Sketch MD5
    */
  UpdateOTA(int sketchSize, int sketchSpace, String sketchMD5);

  /** init
  * Initialize the OTA
  */
  void init();
};
#endif
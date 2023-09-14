// Light Interface
#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

class Light {
private:
  bool _autoLamp;
  int _lampChannel;
  int _pwmFreq;
  int _pwmResolution;
  int _lampVal;
public:
  Light() {}  // Default Construction; DO NOT USE
  /** Constructor, that initialize timer
  * @param autoLamp {bool} Automatic lamp (auto on while camera running)
  * @param lampChannel {int} a free PWM channel (some channels used by camera)
  * @param pwmFreq {int} 50K pwm frequency
  * @param pwmResolution {int} duty cycle bit range
  */
  Light(bool autoLamp, int lampChannel, int pwmFreq, int pwmResolution);
  
  /** Notification LED 
  * @param flashTime {int} notifcation LED Flash time
  */
  void flashLED(int flashtime);
  
  /** Lamp Control 
  * @param newVal {int} new Lamp Value
  */
  void setLamp(int newVal);
  
  /** Setup Light 
  * Illumination LAMP and status LED 
  * @param lampVal {int} initial Lamp Value
  */
  void setupLight(int lampVal);
};

#endif
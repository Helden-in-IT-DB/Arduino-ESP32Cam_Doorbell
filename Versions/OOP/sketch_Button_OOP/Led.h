// LED Interface
#ifndef LED_H
#define LED_H

#include <Arduino.h>

/** LED Class */
class Led {
private:
  byte _pin;
public:
  Led() {}                        // Default Construction; DO NOT USE
  Led(byte pin);
  
  void init();                    /** LED Init*/
  void init(byte defaultState);   /** LED Init w. DefaultState*/
  void on();                      /** LED ON*/
  void off();                     /** LED OFF*/
};

#endif
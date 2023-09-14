// LED Interface
#ifndef LED_H
#define LED_H

#include <Arduino.h>

/** LED Class */
class Led {
private:
  byte _pin;
public:
  Led() {}  // Default Construction; DO NOT USE

  /** Constructor, that initialize timer
    * @param pin the output pin
    */
  explicit Led(byte pin);

  /** LED Init 
  * Initialize the LED
  */
  void init();

  /** LED Init w. DefaultState 
  * @param defaultState set defaultstate on Init
  */
  void init(byte defaultState);

  /** LED ON 
  * Toggle LED ON
  */
  void on();

  /** LED OFF 
  * Toggle LED Off
  */
  void off();
};

#endif
// Button Interface
#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

/** Button Class */
class Button {
private:
  byte _pin;
  byte _state;
  byte _lastReading;
  unsigned long _lastDebounceTime = 0;
  unsigned long _debounceDelay = 50;
public:
  Button() {}  // Default Construction; DO NOT USE

  /** Constructor, that initialize Button
    * @param pin the input pin
    */
  Button(byte pin);

  /** Buzzer Init 
  * Initialize the Buzzer
  */
  void init();

  /** Button Update
  * Update the Button
  */
  void update();

  /** Button Update
  * @return state Returns button State
  */
  byte getState();

  /** Button Update
  * @return bool Returns Button is Pressed Bool
  */
  bool isPressed();
};

#endif
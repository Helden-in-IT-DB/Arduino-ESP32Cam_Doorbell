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
  Button() {}                        // Default Construction; DO NOT USE
  Button(byte pin);

  void init();
  void update();
  byte getState();
  bool isPressed();
};

#endif
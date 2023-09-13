// Buzzer Interface
#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

/** Buzzer Class */
class Buzzer {
private:
  byte _pin;
  int _pitch;

public:
  Buzzer() {}  // Default Construction; DO NOT USE
  Buzzer(byte pin, int pitch);

  void init();                  /** Buzzer Init*/
  void init(byte defaultState); /** Buzzer Init w. DefaultState*/
  void on();                    /** Buzzer ON*/
  void off();                   /** Buzzer OFF*/
};

#endif

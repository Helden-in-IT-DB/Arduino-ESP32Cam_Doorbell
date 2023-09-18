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

  /** Constructor, that initialize Buzzer
    * @param pin the output pin
    * @param pitch the pitch of the Buzzer
    */
  Buzzer(byte pin, int pitch);

  /** Buzzer Init 
  * Initialize the Buzzer
  */
  void init();

  /** Buzzer Init w. DefaultState 
  * @param defaultState set defaultstate on Init
  */
  void init(byte defaultState);

  /** Buzzer ON 
  * Toggle Buzzer ON
  */
  void on();

  /** Buzzer OFF 
  * Toggle Buzzer Off
  */
  void off();
};

#endif

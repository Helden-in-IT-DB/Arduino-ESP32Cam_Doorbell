// Buzzer Implementation
#include "Buzzer.h"

Buzzer::Buzzer(byte pin, int pitch) {
  _pin = pin;
  _pitch = pitch;
  init();
}

/** Buzzer Init
* Initialize the Buzzer
*/
void Buzzer::init() {
  pinMode(_pin, OUTPUT);
  off();
}

/** Buzzer Init w. DefaultState
*
*/
void Buzzer::init(byte defaultState) {
  init();
  if (defaultState == HIGH) {
    on();
  } else {
    off();
  }
}

/** Buzzer ON
* Toggle Buzzer ON
*/
void Buzzer::on() {
  tone(_pin, _pitch);
}

/** Buzzer OFF
* Toggle Buzzer Off
*/
void Buzzer::off() {
  noTone(_pin);
}
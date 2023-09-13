// LED Implementation
#include "Led.h"

Led::Led(byte pin) {
  _pin = pin;
  init();
}

/** LED Init
* Initialize the LED
*/
void Led::init() {
  pinMode(_pin, OUTPUT);
  off();
}

/** LED Init w. DefaultState
*
*/
void Led::init(byte defaultState) {
  init();
  if (defaultState == HIGH) {
    on();
  } else {
    off();
  }
}

/** LED ON
* Toggle LED ON
*/
void Led::on() {
  digitalWrite(_pin, HIGH);
}

/** LED OFF
* Toggle LED Off
*/
void Led::off() {
  digitalWrite(_pin, LOW);
}
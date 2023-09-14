// LED Implementation
#include "Led.h"

Led::Led(byte pin) {
  _pin = pin;
  init();
}

// LED Init
void Led::init() {
  pinMode(_pin, OUTPUT);
  off();
}

// LED Init w. DefaultState
void Led::init(byte defaultState) {
  init();
  if (defaultState == HIGH) {
    on();
  } else {
    off();
  }
}

// LED ON
void Led::on() {
  digitalWrite(_pin, HIGH);
}

// LED OFF
void Led::off() {
  digitalWrite(_pin, LOW);
}
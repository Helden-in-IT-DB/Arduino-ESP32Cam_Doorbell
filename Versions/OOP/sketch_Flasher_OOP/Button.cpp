// Button Implementation
#include "Button.h"

Button::Button(byte pin) {
  _pin = pin;
  _lastReading = LOW;
  init();
}

void Button::init() {
  pinMode(_pin, INPUT);
  update();
}

void Button::update() {
  byte _newReading = digitalRead(_pin);

  if (_newReading != _lastReading) {
    _lastDebounceTime = millis();
  }
  if (millis() - _lastDebounceTime > _debounceDelay) {
    // Update the 'state' attribute only if debounce is checked
    _state = _newReading;
  }
  _lastReading = _newReading;
}

byte Button::getState() {
  update();
  return _state;
}

bool Button::isPressed() {
  return (getState() == HIGH);
}

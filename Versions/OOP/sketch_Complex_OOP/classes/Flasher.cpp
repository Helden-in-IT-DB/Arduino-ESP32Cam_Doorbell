// Flasher Implementation
#include "Flasher.h"

Flasher::Flasher(long on, long off) {
  _onTime = on;
  _offTime = off;
  init();
}

void Flasher::init() {
  state = LOW;
  previousMillis = 0;
  //update();
}

bool Flasher::update() {
  unsigned long currentMillis = millis();
  if ((state == HIGH) && (currentMillis - previousMillis >= _onTime)) {
    state = LOW;
    previousMillis = currentMillis;
    return true;
  } else if ((state == LOW) && (currentMillis - previousMillis >= _offTime)) {
    state = HIGH;
    previousMillis = currentMillis;
    return false;
  }
}
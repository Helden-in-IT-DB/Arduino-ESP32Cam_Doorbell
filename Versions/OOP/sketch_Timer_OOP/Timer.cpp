// Timer Implementation
#include "Timer.h"

Timer::Timer(long duration) {
  _duration = duration;
  init();
}

void Timer::init() {
  previousMillis = 0;
  //update();
}

bool Timer::update() {
  unsigned long currentMillis = millis();
  Serial.println("Timer: ");
  Serial.println(currentMillis - previousMillis);
  Serial.print(" _duration:");
  Serial.println(_duration);

  if ((currentMillis - previousMillis >= _duration)) {
    previousMillis = currentMillis;
    Serial.println("Timer Update TRUE");
    return true;
  }
  return false;
}
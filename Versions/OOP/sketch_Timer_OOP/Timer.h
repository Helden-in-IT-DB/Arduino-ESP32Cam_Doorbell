// Timer Interface
#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

//** Timer Class */
class Timer {
private:
  long _duration;
  unsigned long previousMillis;
public:
  Timer() {}  // Default Construction; DO NOT USE
  Timer(long duration);

  void init();
  bool update();
};
#endif
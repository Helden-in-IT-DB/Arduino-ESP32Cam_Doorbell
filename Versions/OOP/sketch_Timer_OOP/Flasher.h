// Flasher Interface
#ifndef FLASHER_H
#define FLASHER_H

#include <Arduino.h>

//** Flasher Class */
class Flasher {
private:
  long _onTime;
  long _offTime;
  int state;
  unsigned long previousMillis;
public:
  Flasher() {}  // Default Construction; DO NOT USE
  Flasher(long on, long off);

  void init();
  bool update();
};
#endif
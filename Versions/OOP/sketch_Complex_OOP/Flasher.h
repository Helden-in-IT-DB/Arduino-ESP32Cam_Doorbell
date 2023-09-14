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

  /** Constructor, that initialize Flasher
    * @param on On Time in msec
    * @param off Off Time in msec
    */
  Flasher(long on, long off);

  /** Flasher Init 
  * Initialize the Flasher
  */
  void init();

  /** Flasher Update
  * @return bool Returns True if ON, False if OFF
  */
  bool update();
};
#endif
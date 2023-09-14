/** Simple Timer
* Created by kiryanenko on 05.10.19.
* version 1.0.0
*/

#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

#include <Arduino.h>

class SimpleTimer {
private:
  uint64_t _start;
  uint64_t _interval;

public:
  /** Constructor, that initialize timer
    * @param interval An interval in msec 
    */
  explicit SimpleTimer(uint64_t interval = 0);

  /** Check is timer is ready
    * @return True if is timer is ready 
    */
  bool isReady();

  /** Set the time interval
    * @param interval An interval in msec
    */
  void setInterval(uint64_t interval);

  /** Reset a timer 
    */
  void reset();
};

#endif

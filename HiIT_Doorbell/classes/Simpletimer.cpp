/** Simple Timer Interface
* Created by kiryanenko on 05.10.19.
* Edited by IMunster on 14/9/23
* version 1.0.0
*/

#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(uint64_t interval) : _interval(interval) {
  _start = millis();
}

bool SimpleTimer::isReady() {
  return _start + _interval <= millis();
}

void SimpleTimer::setInterval(uint64_t interval) {
  _interval = interval;
}

void SimpleTimer::reset() {
  _start = millis();
}

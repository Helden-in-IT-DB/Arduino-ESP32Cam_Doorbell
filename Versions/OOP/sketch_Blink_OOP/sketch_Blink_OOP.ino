/* Blink OOP 
* https://www.tinkercad.com/things/6452yvYXG5U
*/

#define LED_PIN 13

#include "Led.h"

// Create LED Object
Led led(LED_PIN);


void setup() {
  // initialize LED
  led.init();
}

void loop() {
  led.on();
  delay(500);
  led.off();
  delay(500);
}

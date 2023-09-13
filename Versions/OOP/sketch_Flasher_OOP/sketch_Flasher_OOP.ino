/* Flasher OOP 
*/

#define LED_PIN 13
#define BUTTON_PIN 5

//#include "Led.h"
#include "Flasher.h"
#include "Button.h"

// Create LED Object
//Led led(LED_PIN);
Flasher ledFlash(LED_PIN, 500, 250);
Button button(BUTTON_PIN);


void setup() {
}

void loop() {
  if (button.isPressed()) {
    ledFlash.update();
  } else {
  }
}

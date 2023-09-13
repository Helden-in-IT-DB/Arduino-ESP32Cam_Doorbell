/* LEDButton OOP 
*/

#define LED_PIN 13
#define BUTTON_PIN 5

#include "Led.h"
#include "Button.h"

// Create LED Object
Led led(LED_PIN);
Button button(BUTTON_PIN);


void setup() {
}

void loop() {
  if (button.isPressed()) {
    led.on();
  } else {
    led.off();
  }
}

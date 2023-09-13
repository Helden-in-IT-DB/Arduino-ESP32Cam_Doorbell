/* Buzzer OOP 
*/
#define BUTTON_PIN 5
#define BUZZER_PIN 8
#define LED_PIN 13

#include "Led.h"
#include "Button.h"
#include "Buzzer.h"

// Create LED Object
Led led(LED_PIN);
Button button(BUTTON_PIN);
Buzzer buzzer(BUZZER_PIN, 100);


void setup() {
}


void loop() {
  if (button.isPressed()) {
    led.on();
    buzzer.on();
  } else {
  }
}

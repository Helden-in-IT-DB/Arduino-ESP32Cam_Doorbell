/* Buzzer OOP 
*/
#define BUTTON_PIN 2
#define BUZZER_PIN 8
#define LED_PIN 5

#include "Led.h"
#include "Button.h"
#include "Buzzer.h"
#include "Flasher.h"
#include "Timer.h"

// Create LED Object
Led led(LED_PIN);
Button button(BUTTON_PIN);
Buzzer buzzer(BUZZER_PIN, 500);
Flasher flasher(25, 50);
Timer timer(50);

void setup() {
  Serial.begin(9600);  // Serial Port to Debug
}


void loop() {
  if (button.isPressed()) {
    while (timer.update()) {
      if (flasher.update()) {
        led.on();
        buzzer.on();
      } else {
        led.off();
        buzzer.off();
      }
    }

  } else {
    //
  }
}

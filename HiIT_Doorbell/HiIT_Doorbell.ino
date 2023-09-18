/* Multitask OOP 
*/
#define BUTTON_PIN 2
#define BUZZER_PIN 8
#define LED_PIN 5

#include "Classes/Led.h"
#include "Classes/Light.h"
#include "Classes/Button.h"
#include "Classes/Buzzer.h"
#include "Classes/Flasher.h"
#include "Classes/SimpleTimer.h"

// Create Objects
// Led led(LED_PIN);
// Light light(false, 7, 50000, 9);
// Button button(BUTTON_PIN);
// Buzzer buzzer(BUZZER_PIN, 500);
// Flasher flasher(25, 50);
// SimpleTimer timer(50);

void setup() {
  Serial.begin(9600);  // Serial Port to Debug
}


void loop() {
  
}

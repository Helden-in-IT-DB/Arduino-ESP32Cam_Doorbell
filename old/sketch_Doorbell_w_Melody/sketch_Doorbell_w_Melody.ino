// Doorbell HiIT
/* 
version 1.
    Doorbell press:
      -v1.1 Led Light Blink
      - Buzzer Singular
      - Timer to OFF (20sec)

!Delay does not work -> Milisec does work (How long are you "alive")

Refrence Material
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

version 2.
  - Camera Startup

version 3.
  - Servo to Open Lock
*/
#include "pitches.h"

// Constants
const int inputButtonPin = 2; // Button Input Pin
const int outputLedPin = 5; // Led Output Pin
const int outputBuzzerPin = 6; 
const int serialPort = 9600;

// Global
int stateButton = 0; // state of the Button Push
int stateButtonPinLevelLast = LOW;
int stateDoorbell = 0;
int stateLEDPinLevel = LOW;

// Miliseconds Bounce
unsigned long bounceTimeLast = 0;
unsigned long bounceTime = 50;

// Blink Delays
const long blinkInterval = 1000;
unsigned long blinkPreviousMillis = 0;

// Buzzer Melody
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
// Only play Buzzer Song Once
int doOnce = 0;

/** Setup code, to run once
*/
void setup() {

  // Serial Port to Debug
  Serial.begin(serialPort);

  // Initialize LED as Output
  pinMode(outputLedPin, OUTPUT);
  // Initialize Buzzer as Output
  pinMode(outputBuzzerPin, OUTPUT);
  // Initialize Button as Input
  pinMode(inputButtonPin, INPUT);

  // Set initial LED State
  digitalWrite (outputLedPin, stateLEDPinLevel);
}


/** Main code, to run repeatedly
*/
void loop() {

  // Save Input State of Button
  int readIn = readInput(inputButtonPin);

  // If the Switch Changed
  if (readIn != stateButtonPinLevelLast) {
    bounceTimeLast = millis();
  }

  // Check if waited for BounceTime
  if ((millis() - bounceTimeLast) > bounceTime) {
    // If State Changed
    if (readIn != stateButton) {
      // Chang the State
      stateButton = readIn;
      // If State is HIGH
      if (stateButton == HIGH) {
        // LED State is Not HIGH
        stateDoorbell = !stateDoorbell;
      }
    }
  }
  // LED Loop
  ledLoop (stateDoorbell);
  //
  buzzerLoop (stateDoorbell);
  // Set Last State
  stateButtonPinLevelLast = readIn;
}


/** Read Input Function
* @Arg INT inputPin - Input Pin to Read
* @Return - returns Input PIN State INT
*/
int readInput (int inputPin) {
    // Read Button State
   return digitalRead(inputPin);
}

/** Millis Delay Function
* @Arg Long INT 
*/
void millisDelay (long int delayTime) {
  long int startTime = millis ();
  while (millis() - startTime < delayTime);
}


/** LED Loop
*/
void ledLoop (int state) {
  if (state) {
    // Current Millis Time for Blink blinkInterval
    unsigned long currentMillis = millis();

    // Current and last Time bigger than blinkInterval Blink
    if (currentMillis - blinkPreviousMillis >= blinkInterval) {
      //
      blinkPreviousMillis = currentMillis;
      //
      if (stateLEDPinLevel == LOW) {
        //
        stateLEDPinLevel = HIGH;
      } else {
        //
        stateLEDPinLevel = LOW;
      }
    }
  } else {
    //
    stateLEDPinLevel = LOW;
  }
  //
  digitalWrite(outputLedPin, stateLEDPinLevel);
}

/**
*/
void buzzerLoop (int state) {
  if (state && doOnce == 0) {
    // Current Millis Time for Pause Interval
    unsigned long currentMillis = millis();
    //
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone (outputBuzzerPin, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      millisDelay(pauseBetweenNotes);
      //delay(pauseBetweenNotes);
      noTone(outputBuzzerPin);
    } 
      doOnce = 1;
    } else if (!state) {
      doOnce = 0;
  }
}
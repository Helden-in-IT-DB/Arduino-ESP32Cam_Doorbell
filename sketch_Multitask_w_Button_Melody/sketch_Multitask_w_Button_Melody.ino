/** Multitasking with Button
* Source:            https://roboticsbackend.com/how-to-do-multitasking-with-arduino/
* TinkerCAD Sander:  https://www.tinkercad.com/things/kiU7lTCESUR-arduinomultitasktest/editel?sharecode=kpKXm7o7TIOAI0hBZ0wSIcZlQ6VbWi5uqsCQl2yARYw 
* TinkerCAD Ian:     https://www.tinkercad.com/things/2vBIwQ55g4U-hiit-multitask-w-button/
*/

#include "pitches.h"  // Include Pitch Library
/*#define NOTE_C4 262
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262*/

// PIN Definitions
#define BTN_1_PIN 2  // Button 1 PIN
#define LED_1_PIN 5  // LED 1 PIN    (Process_1)
#define LED_2_PIN 6  // LED 2 PIN    (Process_2)
#define BUZ_1_PIN 8  // Buzzer 1 PIN (Process_3)

/** GLOBAL */
// Button1
int BTN1_State = LOW;      // the current reading from the Button input pin
int BTN1_PrevState = LOW;  // the previous reading from the Button input pin
  // Input Debounce
unsigned long debounce_TimeLast = 0;  // the last time the input pin was toggled
unsigned long debounce_Delay = 5;     // the debounce time; increase if the output flickers
  // Repeat Timer
unsigned long repeat_Time = 5000;   // Timer to Repeat the Processes until Time runs Out
unsigned long repeat_PrevTime = 0;  // Previous Time Ran Out
  // LED1
unsigned long LED1Blink_PrevTime = 0;              // Previous Blink time of LED1 in millis();
unsigned long LED1Blink_Delay = repeat_Time / 10;  //1000;  // Time Delay LED1
int LED1Blink_State = LOW;                         // State of LED1
  // LED2
unsigned long LED2Blink_PrevTime = 0;              // Previous Blink time of LED2 in millis();
unsigned long LED2Blink_Delay = repeat_Time / 40;  //250;   // Time Delay LED2
int LED2Blink_State = LOW;                         // State of LED2
  // Buzzer1
const int BUZZ1_Melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };  // Buzzer Melody
const int BUZZ1_NoteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };                                     // note durations: 4 = quarter note, 8 = eighth note, etc.:

int BUZZ1_NoteIndex = 0;     //
int BUZZ1_NoteDuration = 0;  //

unsigned long BUZZ1Blink_PrevTime = 0;                                       // Previous Blink time of Buzzer1 in millis();
unsigned long BUZZ1Blink_Delay = repeat_Time / sizeof(BUZZ1_Melody) * 1.30;  //repeat_Time / 4;  //2500;  // Time Delay Buzzer1
int BUZZ1Blink_State = LOW;                                                  // State of Buzzer1

//const int BUZZ1_Pitch = 100;                                                                      // Buzzer Sound Pitch
//const int BUZZ1_Duration = 3;                                                                     // Buzzer Sound Duraction !! UNUSED !!


/** Setup, Run once */
void setup() {
  pinMode(BTN_1_PIN, INPUT);   // Set INPUT PinMode for Button 1
  pinMode(LED_1_PIN, OUTPUT);  // Set OUTPUT PinMode for LED1
  pinMode(LED_2_PIN, OUTPUT);  // Set OUTPUT PinMode for LED2
  pinMode(BUZ_1_PIN, OUTPUT);  // Set OUTPUT PinMode for Buzzer1
  Serial.begin(9600);          // Serial Port to Debug
}


/** Main run repeatedly
* Wait for Input from Button1 and Debounce Noise
*/
void loop() {
  debounceButtonInput();  // Debounce the Button Input
}


/** Debounce Input Noise
*/
void debounceButtonInput() {
  int btnReading = digitalRead(BTN_1_PIN);                // read the state of the switch into a local variable
  if (btnReading != BTN1_PrevState) {                     // If the switch changed, due to noise or pressing
    debounce_TimeLast = millis();                         // reset the debouncing timer
  }                                                       //
  if ((millis() - debounce_TimeLast) > debounce_Delay) {  // When longer than the debounce delay
    if (btnReading != BTN1_State) {                       // if the button state has changed
      BTN1_State = btnReading;                            // Save the new Input State
      if (BTN1_State == HIGH) {                           // if the new button state is HIGH (i.e ON)
        Serial.println("Button Press");                   // DEBUG
        startProcessesTimer();                            // Start the Processes Timer
      }                                                   //
    }                                                     //
  }                                                       //
  BTN1_PrevState = btnReading;                            // save the btnReading. Next time through the loop
}


/**
* Runs # of Processes while a Timer has not ran out of Time
* Otherwise Ends Processes
*/
void startProcessesTimer() {
  repeat_PrevTime = millis();                          // Save Previous Repeat Time
  while (millis() - repeat_PrevTime <= repeat_Time) {  // Do while the end Timer has not been passes
    runProcesses();                                    // Run The Processes
  }                                                    // After Timer runs out
  Serial.println("END PROCESS");                       // DEBUG
  endProcesses();                                      // End the Processes
}

/** Run Processes
* Saves Current Time and Gives Current Time to Processes to Run
*/
void runProcesses() {
  unsigned long currentTime = millis();  // Save Current Time
  processLEDOne(currentTime);            // START_PROCESS_1
  processLEDTwo(currentTime);            // START_PROCESS_2
  processBuzzOne(currentTime);           // START_PROCESS_3
}


/** END Processes
* Runs after Timer ran out of Time
* Check if LEDs or Buzzer are ON after Timer Ran Out, if ON, manually turn OFF.
*/
void endProcesses() {

  LED1Blink_PrevTime = 0;          // Reset previous Time
  LED2Blink_PrevTime = 0;          // Reset previous Time
  BUZZ1Blink_PrevTime = 0;         // Reset previous Time
  BUZZ1_NoteIndex = 0;             //
  BUZZ1_NoteDuration = 0;          //
  if (LED1Blink_State == HIGH) {   // Check if LED1 is Still ON when Process Ended
    digitalWrite(LED_1_PIN, LOW);  // Manually Turn LED1 OFF
  }                                //
  if (LED2Blink_State == HIGH) {   // Check if LED2 is Still ON when Process Ended
    digitalWrite(LED_2_PIN, LOW);  // Manually Turn LED2 OFF
  }                                //
  if (BUZZ1Blink_State == HIGH) {  // Check if Buzzer1 is Still ON when Process Ended
    noTone(BUZ_1_PIN);             // Manually Stop Buzzer1 Sound
  }
}


/** Process One - LED One
* @param {unsigned long} _currentTime - Current Time the Process was called. Used for Blink Timer
*/
void processLEDOne(unsigned long _currentTime) {
  if (_currentTime - LED1Blink_PrevTime >= LED1Blink_Delay) {  // Toggle LED1 if Delay has passed
    LED1Blink_PrevTime += LED1Blink_Delay;                     // Update previous Time, with Delay Time
    if (LED1Blink_State == HIGH) {                             // Check LED1 State is HIGH (i.e. ON)
      LED1Blink_State = LOW;                                   // Switch from HIGH to LOW
    } else {                                                   // Otherwise if NOT HIGH
      LED1Blink_State = HIGH;                                  // Otherwise switch from LOW to HIGH
    }                                                          //
    digitalWrite(LED_1_PIN, LED1Blink_State);                  // Toggle LED1, with LED1 Blink State
  }
}


/** Process Two - LED Two
* @param {unsigned long} _currentTime - Current Time the Process was called. Used for Blink Timer
*/
void processLEDTwo(unsigned long _currentTime) {
  if (_currentTime - LED2Blink_PrevTime >= LED2Blink_Delay) {  // Toggle LED2 if Delay has passed
    LED2Blink_PrevTime += LED2Blink_Delay;                     // Update previous Time, with Delay Time
    if (LED2Blink_State == HIGH) {                             // Check LED2 State
      LED2Blink_State = LOW;                                   // Switch from HIGH to LOW
    } else {                                                   // Otherwise if NOT HIGH
      LED2Blink_State = HIGH;                                  // Otherwise switch from LOW to HIGH
    }                                                          //
    digitalWrite(LED_2_PIN, LED2Blink_State);                  // Toggle LED2, with LED2 Blink State
  }
}


/** Process Three - Buzzer ONE
* @param {unsigned long} _currentTime - Current Time the Process was called. Used for Blink Timer
*/
void processBuzzOne(unsigned long _currentTime) {
  int BUZZ1_PauseBetweenNotes;
  if (_currentTime - BUZZ1Blink_PrevTime >= BUZZ1Blink_Delay /*+ BUZZ1_PauseBetweenNotes*/) {  // Toggle BUZZ1 if Delay has passed
    BUZZ1Blink_PrevTime += BUZZ1Blink_Delay + BUZZ1_PauseBetweenNotes;                         // Update previous Time, with Delay Time
    BUZZ1_NoteDuration = BUZZ1_NoteDurations[BUZZ1_NoteIndex] / 1000;                          //
    BUZZ1_PauseBetweenNotes = BUZZ1_NoteDuration * 1.30;                                       //
    if (BUZZ1Blink_State == HIGH) {                                                            // Check BUZZ1 State
      noTone(BUZ_1_PIN);                                                                       // Stop BUZZ1 Sound
      BUZZ1Blink_State = LOW;                                                                  // Switch from HIGH to LOW
    } else {                                                                                   // Otherwise
      Serial.print(BUZZ1_NoteIndex);                                           // DEBUG
      Serial.println(BUZZ1_Melody[BUZZ1_NoteIndex]);                                           // DEBUG
      tone(BUZ_1_PIN, BUZZ1_Melody[BUZZ1_NoteIndex] /*, BUZZ1_NoteDuration*/);                 // Play BUZZ1 Sound
      BUZZ1Blink_State = HIGH;                                                                 // Otherwise switch from LOW to HIGH
      BUZZ1_NoteIndex += 1;                                                                      //
    }
  }
}

/*
BUZZ MELODY w DELAY()
for (int thisNote = 0; thisNote < 8; thisNote++) {                // iterate over the notes of the melody:
  BUZZ1_NoteDuration = 1000 / BUZZ1_NoteDurations[thisNote];  // to calculate the note duration, take one second divided by the note type. e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  tone(BUZ_1_PIN, BUZZ1_Melody[thisNote], BUZZ1_NoteDuration);    // Play Note
  int BUZZ1_PauseBetweenNotes = BUZZ1_NoteDuration * 1.30;        // to distinguish the notes, set a minimum time between them. the note's duration + 30% seems to work well:
  delay(BUZZ1_NauseBetweenNotes);                                 // Pause Between
  noTone(BUZ_1_PIN);                                              // stop the tone playing:
}

BUZZ NOISE SINGLE PITCH
if (_currentTime - BUZZ1Blink_PrevTime >= BUZZ1Blink_Delay) {  // Toggle BUZZ1 if Delay has passed
  BUZZ1Blink_PrevTime += BUZZ1Blink_Delay;                     // Update previous Time, with Delay Time
  if (BUZZ1Blink_State == HIGH) {                              // Check BUZZ1 State
    BUZZ1Blink_State = LOW;                                    // Switch from HIGH to LOW
    noTone(BUZ_1_PIN);                                         // Stop BUZZ1 Sound
  } else {                                                     // Otherwise
    BUZZ1Blink_State = HIGH;                                   // Otherwise switch from LOW to HIGH
    tone(BUZ_1_PIN, BUZZ1_Pitch);                              // Play BUZZ1 Sound
  }
}*/
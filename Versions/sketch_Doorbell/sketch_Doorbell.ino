/* Product Description
Version 1.
Press Doorbell:
  Debounce Input Noise
  Light Blink
  Buzzer Blink

  Refrence Material
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
*/
// Pin numbers
#define pinButton 2  // the number of the pushbutton pin
#define pinLED 5     // the number of the LED pin
#define pinBuzzer 6  // the number of the Buzzer pin

// States
int stateDoorbell = 0;      // The current state of the Doorbell (Where 0: Not Ringing, 1: Ringing, 3: Opening,)
int stateLED = LOW;         // the current state of the LED output pin
int stateBuzzer = LOW;      // the current state of the Buzzer output pin
int stateButton = 0;        // the current reading from the Button input pin
int stateButtonLast = LOW;  // the previous reading from the Button input pin

// Debounce Timer milliseconds
unsigned long debounceTimeLast = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Blink Timers
unsigned long blinkMillisLast = 0;  // will store last time LED was updated
const long blinkInterval = 1000;    // blinkInterval at which to blink (milliseconds)

// Ring Time
unsigned long ringTimeLast = 0;  // Store last Ring Time
const long ringTime = 5000;      //20000;        // Ring Time (20sec)

// Buzzer Sound
const int buzzerPitch = 100;   // Store Buzzer Sound Pitch
const int buzzerDuration = 3;  // Store Buzzer Sound Duration

// Debug Console
const int serialPort = 9600;

void setup() {
  pinMode(pinButton, INPUT);       // Set the Button Input Pin
  pinMode(pinLED, OUTPUT);         // Set the LED Output Pin
  digitalWrite(pinLED, stateLED);  // set initial LED state
  // Serial Port to Debug
  Serial.begin(serialPort);
}

void loop() {
  // Get and Debounce Button Input
  debounceInput();
}

/** Debounce Input Noise
*
*/
void debounceInput() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(pinButton);
  // check to see if you just pressed the button (i.e. the input went from LOW to HIGH), and you've waited long enough since the last press to ignore any noise:
  // If the switch changed, due to noise or pressing:
  if (reading != stateButtonLast) {
    // reset the debouncing timer
    debounceTimeLast = millis();
  }
  // whatever the reading is at, it's been there for longer than the debounce delay, so take it as the actual current state:
  if ((millis() - debounceTimeLast) > debounceDelay) {
    // if the button state has changed:
    if (reading != stateButton) {
      stateButton = reading;
      // only toggle the LED if the new button state is HIGH
      if (stateButton == HIGH) {
        // If Already Ringing
        if (stateDoorbell == 1) {
          // Doorbell not ringing
          stateDoorbell = 0;
        } else {
          
          // Start WiFi Camera Temp Function
          startCamera();

          // Doorbell State 1 (i.e. Ringing)
          stateDoorbell = 1;
          // Reset Last Ring Time
          ringTimeLast = millis();
          // Start Ringing Function
          startRinging();
          // Debug, Doorbell Press Ended
          Serial.println("End Doorbell Press...");
        }
        // Debug State Doorbell
        Serial.print("State Doorbell:");
        Serial.println(stateDoorbell);
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the stateButtonLast:
  stateButtonLast = reading;
}

/** Start the Camera Function
*
*/
void startCamera() {
  // Temp Function
  Serial.println("Start Camera...");
}


/** Start Ringing the Doorbell
* 
*/
void startRinging() {
  Serial.println("Start Ringing..");
  // Increment RingTime
  //
  // check to see if RingTime has Passed
  while (millis() - ringTimeLast <= ringTime) {
    // check to see if it's time to blink; that is, if the difference between the current time and last time you blinked is bigger than the blinkInterval at which you want to blink.
    unsigned long blinkMillisCurrent = millis();
    if (blinkMillisCurrent - blinkMillisLast >= blinkInterval) {
      // save the last time you blinked
      blinkMillisLast = blinkMillisCurrent;

      // if the LED is off turn it on and vice-versa:
      if (stateLED == LOW) {
        Serial.println("No Buzz, LED On");
        stateLED = HIGH;
      } else {
        Serial.println("Buzz On, LED Off");
        stateLED = LOW;
        tone(pinBuzzer, buzzerPitch, buzzerDuration);
      }
      // Set state of Buzzer
      stateBuzzer = digitalRead(pinBuzzer);
      // set the LED with the state of the variable:
      digitalWrite(pinLED, stateLED);

      // Debug Current Ring Time
      Serial.println(millis() - ringTimeLast);
    }
    // buzzInterval
    //if (blinkMillisCurrent - blinkMillisLast >= buzzerInterval) {
      //
    //}
  }
  // Stop Ringing after RingTime
  stopRinging();
}


void stopRinging() {
  // Debugg Stopped Ringing
  Serial.println("Stopped Ringing..");
  // Doorbell State 0
  stateDoorbell = 0;
  // Check to make sure LED and Buzzer are off
  if (stateLED == HIGH) {
    digitalWrite(pinLED, LOW);
    Serial.println("LED OFF..");
  }
  if (stateBuzzer) {
    noTone(pinBuzzer);
    Serial.println("BUZZER OFF..");
  }
  // Debug State Doorbell
  Serial.print("State Doorbell End Ring:");
  Serial.println(stateDoorbell);
}
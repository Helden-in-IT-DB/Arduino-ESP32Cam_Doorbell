/* Doorbell HiIT
Product Description
  Version 1.
    Press Doorbell:
      Light Blink
      Buzzer Blink
      Off After 20sec

  Refrence Material
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay

  Version 2.
    Camera Startup

  Version 3.
    Servo to Open Lock
*/

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
bool stateBuzzer = false;
const int pitch = 1000;

// Miliseconds Bounce
unsigned long bounceTimeLast = 0;
unsigned long bounceTime = 50;

// Blink Delays
const long blinkInterval = 1000;
unsigned long blinkPreviousMillis = 0;


int switcher = 1;

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
  int readIn = digitalRead(inputButtonPin);

  debounce(readIn);

  if (switcher == 1) {
    //
    ledLoop (stateDoorbell);
  } else if (switcher == 2) {
    //
    buzzerLoop (stateDoorbell);
  }

  // Set Last State
  stateButtonPinLevelLast = readIn;
}

/**
*
*/
void debounce (int read) {
  // If the Switch Changed
  if (read != stateButtonPinLevelLast) {
    bounceTimeLast = millis();
  }

  // Check if waited for BounceTime
  if ((millis() - bounceTimeLast) > bounceTime) {
    // If State Changed
    if (read != stateButton) {
      // Chang the State
      stateButton = read;
      // If State is HIGH
      if (stateButton == HIGH) {
        // LED State is Not HIGH
        stateDoorbell = !stateDoorbell;
      }
    }
  }
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
  // switcher = 2;
}

/**
*/
void buzzerLoop (int state) {
  if (state) {
    // Current Millis Time for Blink blinkInterval
    unsigned long currentMillis = millis();

    // Current and last Time bigger than blinkInterval Blink
    if (currentMillis - blinkPreviousMillis >= blinkInterval) {
      //
      blinkPreviousMillis = currentMillis;
      //
      if (stateBuzzer) {
        //
        tone(outputBuzzerPin, pitch, 100);
        stateBuzzer = false;
      } else {
        //
        noTone(outputBuzzerPin);
        stateBuzzer = true;
      }
    } 
    // switcher = 1;
  }
}
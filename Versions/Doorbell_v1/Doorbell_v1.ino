/* Product Description
Version 1.
Press Doorbell:
  Light Blink
  Buzzer Blink

  Refrence Material
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
*/


// Constants PIN
const int pinButton = 2;
const int pinLED = 5;
const int pinBuzzer = 6;
const int serialPort = 9600;

//
int stateLED = LOW;
bool stateBuzzer = false;

// Bounce Input Var
int stateDoorbell = LOW;
int stateButton = 0;
int stateButtonLast = LOW;
unsigned long bounceTimeLast = 0;
unsigned long bounceTime = 50;

// Blink Interval
const long blinkInterval = 1000;
const long buzzerInterval = 10000;
unsigned long blinkPreviousMillis = 0;

// Buzzer Pitch
const int pitch = 31;

void setup() {
  // put your setup code here, to run once:
  // Serial Port to Debug
  Serial.begin(serialPort);
  // Inialize PIN Modes
  pinMode(pinButton, INPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Debounce Input Function
  debounceInput ();
  // Serial.println(stateDoorbell);
 if (stateDoorbell) {
    // while (current Millis < doorbellTimeOut) {}
    digitalWrite(pinLED, stateSwitch (blinkInterval));
    buzzerLoop (buzzerInterval);
 }
}

/** Debounce Input
*
*/
void debounceInput () {
  // inputButtonRead
  int readButton = digitalRead(pinButton);
  // If Button State has Changed
  if (readButton != stateButtonLast) {
    // Set new BounceTime Millis
    bounceTimeLast = millis();
  }
  // Wait untill BounceTime has Passed
  if ((millis() - bounceTimeLast) > bounceTime) {
    // If Button State Changed
    if (readButton != stateButton) {
      // Change the Current State
      stateButton = readButton;
      // if State is ON
      if (stateButton = HIGH) {
        // State Doorbell to NOT Doorbell State
        stateDoorbell = !stateDoorbell;
      }
    }
  }

  stateButtonLast = readButton;
}


/**
* 
*/
int stateSwitch (int interval) {
  // Current Millis Time for Blink blinkInterval
  unsigned long currentMillis = millis();

  // Current minus last Time bigger than blinkInterval Blink
  if (currentMillis - blinkPreviousMillis >= interval) {
    //
    blinkPreviousMillis = currentMillis;
    //
    if (stateLED == LOW) {
    //
      return stateLED = HIGH;
    } else {
    //
      return stateLED = LOW;
    }
  }
}

/**
*
*/
void buzzerLoop (int interval) {
    // Current Millis Time for Blink blinkInterval
  unsigned long currentMillis = millis();

  // Current and last Time bigger than blinkInterval Blink
  if (currentMillis - blinkPreviousMillis >= interval) {
    //
    blinkPreviousMillis = currentMillis;
    //
    if (stateBuzzer) {
      //
      tone(pinBuzzer, pitch, 10);
      stateBuzzer = false;
    } else {
      //
      noTone(pinBuzzer);
      stateBuzzer = true;
    }
  }
}
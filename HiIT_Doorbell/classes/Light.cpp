//Light Implementation
#include "Light.h"

Light::Light(bool autoLamp, int lampChannel, int pwmFreq, int pwmResolution) {
  _autoLamp = autoLamp;
  _lampChannel = lampChannel;
  _pwmFreq = pwmFreq;
  _pwmResolution = pwmResolution;
}

// Notification LED
void Light::flashLED(int flashtime) {
  #if defined(LED_PIN)
    digitalWrite(LED_PIN, LED_ON);   // On at full power.
    delay(flashtime);                // delay
    digitalWrite(LED_PIN, LED_OFF);  // turn Off
  #else
    return; // No notifcation LED, do nothing, no delay
  #endif
}

// Lamp Control
void Light::setLamp(int newVal) {
  #if defined(LAMP_PIN)
    if (newVal != -1) {
      int pwmMax = pow(2, _pwmResolution) - 1;  // Apply a logarithmic function to the scale.
      int brightness = round((pow(2, (1 + (newVal * 0.02))) - 2) / 6 * pwmMax);
      ledcWrite(_lampChannel, brightness);

      //Debug Log
      //Serial.print("Lamp: ");
      //Serial.print(newVal);
      //Serial.print("%, pwm = ");
      //Serial.println(brightness);
    }
  #endif
}

// Illumination LAMP and status LED
void Light::setupLight(int lampVal) {
  _lampVal = lampVal;

  #if defined(LED_PIN)  // If we have a notification LED, set it to output
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LED_ON);
  #endif

  // Initialise and set the lamp
  if (_lampVal != -1) {
    #if defined(LAMP_PIN)
        ledcSetup(_lampChannel, _pwmFreq, _pwmresolution);  // configure LED PWM channel
        ledcAttachPin(LAMP_PIN, _lampChannel);              // attach the GPIO pin to the channel
        if (_autoLamp) setLamp(0);                          // set default value
        else setLamp(_lampVal);
    #endif
  } else {
    // Debug Log
    //Serial.println("No lamp, or lamp disabled in config");
  }

  #if defined(LAMP_DISABLE)
    _lampVal = -1;  // lamp is disabled in config
  #elif defined(LAMP_PIN)
    #if defined(LAMP_DEFAULT)
      _lampVal = constrain(LAMP_DEFAULT, 0, 100);  // initial lamp value, range 0-100
    #else
      _lampVal = 0;  //default to off
    #endif
  #else
    _lampVal = -1;  // no lamp pin assigned
  #endif

  #if defined(LED_DISABLE)
    #undef LED_PIN  // undefining this disables the notification LED
  #endif
}
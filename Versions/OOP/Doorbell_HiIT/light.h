
// Illumination LAMP and status LED
#if defined(LAMP_DISABLE)
    int lampVal = -1; // lamp is disabled in config
#elif defined(LAMP_PIN)
    #if defined(LAMP_DEFAULT)
        int lampVal = constrain(LAMP_DEFAULT,0,100); // initial lamp value, range 0-100
    #else
        int lampVal = 0; //default to off
    #endif
#else
    int lampVal = -1; // no lamp pin assigned
#endif

#if defined(LED_DISABLE)
    #undef LED_PIN    // undefining this disables the notification LED
#endif

bool autoLamp = false;         // Automatic lamp (auto on while camera running)

int lampChannel = 7;           // a free PWM channel (some channels used by camera)
const int pwmfreq = 50000;     // 50K pwm frequency
const int pwmresolution = 9;   // duty cycle bit range
const int pwmMax = pow(2,pwmresolution)-1;


// Notification LED
void flashLED(int flashtime) {
#if defined(LED_PIN)                // If we have it; flash it.
    digitalWrite(LED_PIN, LED_ON);  // On at full power.
    delay(flashtime);               // delay
    digitalWrite(LED_PIN, LED_OFF); // turn Off
#else
    return;                         // No notifcation LED, do nothing, no delay
#endif
}

// Lamp Control
void setLamp(int newVal) {
#if defined(LAMP_PIN)
    if (newVal != -1) {
        // Apply a logarithmic function to the scale.
        int brightness = round((pow(2,(1+(newVal*0.02)))-2)/6*pwmMax);
        ledcWrite(lampChannel, brightness);
        Serial.print("Lamp: ");
        Serial.print(newVal);
        Serial.print("%, pwm = ");
        Serial.println(brightness);
    }
#endif
}

void setupLight() {
    #if defined(LED_PIN)  // If we have a notification LED, set it to output
        pinMode(LED_PIN, OUTPUT);
        digitalWrite(LED_PIN, LED_ON);
    #endif
	
	  // Initialise and set the lamp
    if (lampVal != -1) {
        #if defined(LAMP_PIN)
            ledcSetup(lampChannel, pwmfreq, pwmresolution);  // configure LED PWM channel
            ledcAttachPin(LAMP_PIN, lampChannel);            // attach the GPIO pin to the channel
            if (autoLamp) setLamp(0);                        // set default value
            else setLamp(lampVal);
         #endif
    } else {
        Serial.println("No lamp, or lamp disabled in config");
    }


}
/* Blink OOP */

#define LED_PIN 13

/** LED Class
pin
init()
on()
off()
*/
class Led {
  private:
    byte _pin;
  public:
    Led(){} // Default Construction; DO NOT USE
    Led(byte pin) {
      _pin = pin;
      //init();
    }

/** LED Init
* Initialize the LED
*/
    void init() {
      pinMode(_pin, OUTPUT);
    }

/** LED Init w. DefaultState
*
*/
    void init(byte defaultState){
      init();
      if (defaultState == HIGH) {
        on();
      } else {
        off();
      }
    }

/** LED ON
* Toggle LED ON
*/
    void on() {
      digitalWrite(_pin, HIGH);
    }

/** LED OFF
* Toggle LED Off
*/
    void off() {
      digitalWrite(_pin, LOW);
    }
};

// Create LED Object
Led led(LED_PIN);


void setup() {
  // initialize LED
  led.init();
}

void loop() {
  led.on();
  delay(500);
  led.off();
  delay(500);
}

# HiIT-Arduino
 Arduino Project

## Product Description
Digital doorbell for HiIT.
On Press:
- Blinks a LED for 20sec
- Plays a short Buzzer Sound
- Starts a WiFi Connected Camera
- Waits for Confirmation

On Confirmation:
- Rotates a Servo to disengage Lock
- Waits for approx. 30sec to ShutDoor

On ShutDoor:
- Rotates a Serco to engage Lock
- Shuts down WiFi Connected Camera
- Waits for Input Press.

Every 24hrs:
- Restarts Self, to Reset the internal Clock (i.e. MicroController's Timer)

## Virtual Sketch
[Tinker CAD](https://www.tinkercad.com/things/1TXkCIflTyw-brilliant-bojo-amur/editel?sharecode=3b64AbjSNC-aFxWy6FOw-oxU1wfmHp1eEG2GOLfIka4)


## Reference Material
	[Arduino Object Oriented Programming (OOP)](https://roboticsbackend.com/arduino-object-oriented-programming-oop/)
	[Multi-tasking the Arduino](https://cdn-learn.adafruit.com/downloads/pdf/multi-tasking-the-arduino-part-1.pdf)
	[Creating Classes and Libraries with Arduino](https://www.halvorsen.blog/documents/technology/resources/resources/Arduino/Arduino%20Library/Arduino%20Classes%20and%20Libraries.pdf)
	[Arduino the Object Oriented way] https://paulmurraycbr.github.io/ArduinoTheOOWay.html
	
# Slimme Arduino Deurbel
Helden in IT

## Korte product beschrijving.
Een deurbel gemaakt met Arduino. Naast een knop met LED-licht en Zoemer, heeft de deurbel ook een Camera en WiFi connectie. Wanneer de deurbel wordt gebruikt, gaat de camera aan en stuurt het beeld naar een interne website.  

## Lange product beschrijving.
 Als de deurbel wordt ingedrukt moeten er meerdere dingen gebeuren:  
  1. De deurbel-knop heeft en LED lampje dat gaat knipperen.  
  2. De deurbel speelt een Zoem geluid of melodie over de Zoemer.  
  3. De Camera gaat aan en verstuurt beeld naar interne website.  

### Webhost
 Om direct beeld te kunnen versturen en ontvangen zal de website continue gehost worden. Dit om te voorkomen dat het minuten duurt voordat de deurbel volledig functioneel is.  

### OTA
 Om de deurbel niet continue te hoeven demonteren, zal de deurbel gebruik maken van OTA (Over the Air Updates.) Dit houdt in dat de Arduino programeerbaar en up-to-date kan blijven, door de software via de WiFi connectie te versturen.  

### Automatische herstart
 De Arduino maakt gebruik van de Millis() functie om meerdere taken "tegerlijkertijd" uit te voeren. Deze functie "retourneert het aantal milliseconden dat is verstreken sinds het Arduino-bord het huidige programma begon uit te voeren.  
 Dit aantal zal na ongeveer 50 dagen overlopen (teruggaan naar nul)."  
 Om de interne werking goed te houden zal het board automatisch elke week moeten herstarten. Reset de interne klok (i.e. MicroController's Timer)  

### Toekomst plannen
 De mogelijkheid om een Arduino-Servo aan het Slot te bevestigen, dat het slot op afstand te ontgrendelen is.  

## Ontwikkeling
 De ontwikkeling van de software is in etappes.  
 De eerste etappe was het maken van een Drukknop met Buzzer.  
 [Zie versies](https://github.com/IanMunster/HiIT-Arduino/tree/main/Versions/Doorbell)  
  
 De tweede etappe was het maken van een Multitask programma, waarbij er twee of meer processen (semi)-parallel lopen. (Semi omdat de Arduino maar 1 process tegerlijkertijd kan verwerken)  
 [Zie versies](https://github.com/IanMunster/HiIT-Arduino/tree/main/Versions/Multitask)  
  
 De derde etappe was het implementeren van de Camera Server functies.  
 Hierbij maken we gebruik van de ["ESP32-CAM example revisited"](https://github.com/easytarget/esp32-cam-webserver) code  
 [Zie examples](https://github.com/IanMunster/HiIT-Arduino/tree/main/Examples)  
 Zie de revisited ReadMe voor informatie over het instellen van de ESP32 Camera  
  
 De huidige etappe, het maken van een Object Oriented Program.  
 Het idee is om alle functionaliteiten van de deurbel als losse logica-Objecten te maken. De deurbel heeft onderandere de volgende functies:  
  - De Drukknop,  
  - De Buzzer,  
  - Het LED lampje,  
  - De Camera,  
  - De WiFi Connector,  
  - De Website,  
  - De Server,  
  - OTA  
 Al deze functies moeten worden geïmplementeerd in het complete programma.  
 We gebruiken OOB de code leesbaar, herbruikbaar en flexibel te krijgen.  
 [Zie versies](C:\Users\IanMunster\Documents\GitHub\HiIT-Arduino\Versions\OOP)  

### Notities
 De meeste classes hebben een eigen interface, deze moeten alleen nog afgemaakt worden en worden gecontroleerd op functionaliteit.  
 Vervolgens moeten alle interfaces met elkaar kunnen communiceren om de complexe logica te maken.  


## Virtual Sketch
[Tinker CAD](https://www.tinkercad.com/things/1TXkCIflTyw-brilliant-bojo-amur/editel?sharecode=3b64AbjSNC-aFxWy6FOw-oxU1wfmHp1eEG2GOLfIka4)  


## Reference Material
 [Arduino Object Oriented Programming (OOP)](https://roboticsbackend.com/arduino-object-oriented-programming-oop/)  
 [Multi-tasking the Arduino](https://cdn-learn.adafruit.com/downloads/pdf/multi-tasking-the-arduino-part-1.pdf)  
 [Creating Classes and Libraries with Arduino](https://www.halvorsen.blog/documents/technology/resources/resources/Arduino/Arduino%20Library/Arduino%20Classes%20and%20Libraries.pdf)  
 [Arduino the Object Oriented way] https://paulmurraycbr.github.io/ArduinoTheOOWay.html
 

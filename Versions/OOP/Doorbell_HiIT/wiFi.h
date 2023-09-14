
#include <WiFi.h>
#include <WiFiUdp.h>
#include "src/parsebytes.h"


// Start with accesspoint mode disabled, wifi setup will activate it if
// no known networks are found, and WIFI_AP_ENABLE has been defined
bool accesspoint = false;

// IP address, Netmask and Gateway, populated when connected
server.ip ip;
server.net net;
server.gw gw;

#if !defined(WIFI_WATCHDOG)
    #define WIFI_WATCHDOG 15000
#endif

// Number of known networks in stationList[]
int stationCount = sizeof(stationList)/sizeof(stationList[0]);

// If we have AP mode enabled, ignore first entry in the stationList[]
#if defined(WIFI_AP_ENABLE)
    int firstStation = 1;
#else
    int firstStation = 0;
#endif

void InitWiFi() {
    // Feedback that we are now attempting to connect
    flashLED(300);
    delay(100);
    flashLED(300);
    Serial.println("Starting WiFi");

    // Disable power saving on WiFi to improve responsiveness
    // (https://github.com/espressif/arduino-esp32/issues/1484)
    WiFi.setSleep(false);

    Serial.print("Known external SSIDs: ");
    if (stationCount > firstStation) {
        for (int i=firstStation; i < stationCount; i++) Serial.printf(" '%s'", stationList[i].ssid);
    } else {
        Serial.print("None");
    }
    Serial.println();
    byte mac[6] = {0,0,0,0,0,0};
    WiFi.macAddress(mac);
    Serial.printf("MAC address: %02X:%02X:%02X:%02X:%02X:%02X\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    int bestStation = -1;
    long bestRSSI = -1024;
    char bestSSID[65] = "";
    uint8_t bestBSSID[6];
    if (stationCount > firstStation) {
        // We have a list to scan
        Serial.printf("Scanning local Wifi Networks\r\n");
        int stationsFound = WiFi.scanNetworks();
        Serial.printf("%i networks found\r\n", stationsFound);
        if (stationsFound > 0) {
            for (int i = 0; i < stationsFound; ++i) {
                // Print SSID and RSSI for each network found
                String thisSSID = WiFi.SSID(i);
                int thisRSSI = WiFi.RSSI(i);
                String thisBSSID = WiFi.BSSIDstr(i);
                Serial.printf("%3i : [%s] %s (%i)", i + 1, thisBSSID.c_str(), thisSSID.c_str(), thisRSSI);
                // Scan our list of known external stations
                for (int sta = firstStation; sta < stationCount; sta++) {
                    if ((strcmp(stationList[sta].ssid, thisSSID.c_str()) == 0) ||
                    (strcmp(stationList[sta].ssid, thisBSSID.c_str()) == 0)) {
                        Serial.print("  -  Known!");
                        // Chose the strongest RSSI seen
                        if (thisRSSI > bestRSSI) {
                            bestStation = sta;
                            strncpy(bestSSID, thisSSID.c_str(), 64);
                            // Convert char bssid[] to a byte array
                            parseBytes(thisBSSID.c_str(), ':', bestBSSID, 6, 16);
                            bestRSSI = thisRSSI;
                        }
                    }
                }
                Serial.println();
            }
        }
    } else {
        // No list to scan, therefore we are an accesspoint
        accesspoint = true;
    }

    if (bestStation == -1) {
        if (!accesspoint) {
            #if defined(WIFI_AP_ENABLE)
                Serial.println("No known networks found, entering AccessPoint fallback mode");
                accesspoint = true;
            #else
                Serial.println("No known networks found");
            #endif
        } else {
            Serial.println("AccessPoint mode selected in config");
        }
    } else {
        Serial.printf("Connecting to Wifi Network %d: [%02X:%02X:%02X:%02X:%02X:%02X] %s \r\n",
                       bestStation, bestBSSID[0], bestBSSID[1], bestBSSID[2], bestBSSID[3],
                       bestBSSID[4], bestBSSID[5], bestSSID);
        // Apply static settings if necesscary
        if (stationList[bestStation].dhcp == false) {
            #if defined(ST_IP)
                Serial.println("Applying static IP settings");
                #if !defined (ST_GATEWAY)  || !defined (ST_NETMASK)
                    #error "You must supply both Gateway and NetMask when specifying a static IP address"
                #endif
                IPAddress staticIP(ST_IP);
                IPAddress gateway(ST_GATEWAY);
                IPAddress subnet(ST_NETMASK);
                #if !defined(ST_DNS1)
                    WiFi.config(staticIP, gateway, subnet);
                #else
                    IPAddress dns1(ST_DNS1);
                #if !defined(ST_DNS2)
                    WiFi.config(staticIP, gateway, subnet, dns1);
                #else
                    IPAddress dns2(ST_DNS2);
                    WiFi.config(staticIP, gateway, subnet, dns1, dns2);
                #endif
                #endif
            #else
                Serial.println("Static IP settings requested but not defined in config, falling back to dhcp");
            #endif
        }

        WiFi.setHostname(mdnsName);

        // Initiate network connection request (3rd argument, channel = 0 is 'auto')
        WiFi.begin(bestSSID, stationList[bestStation].password, 0, bestBSSID);

        // Wait to connect, or timeout
        unsigned long start = millis();
        while ((millis() - start <= WIFI_WATCHDOG) && (WiFi.status() != WL_CONNECTED)) {
            delay(500);
            Serial.print('.');
        }
        // If we have connected, inform user
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Client connection succeeded");
            accesspoint = false;
            // Note IP details
            ip = WiFi.localIP();
            net = WiFi.subnetMask();
            gw = WiFi.gatewayIP();
            Serial.printf("IP address: %d.%d.%d.%d\r\n",ip[0],ip[1],ip[2],ip[3]);
            Serial.printf("Netmask   : %d.%d.%d.%d\r\n",net[0],net[1],net[2],net[3]);
            Serial.printf("Gateway   : %d.%d.%d.%d\r\n",gw[0],gw[1],gw[2],gw[3]);
            calcURLs();
            // Flash the LED to show we are connected
            for (int i = 0; i < 5; i++) {
                flashLED(50);
                delay(150);
            }
        } else {
            Serial.println("Client connection Failed");
            WiFi.disconnect();   // (resets the WiFi scan)
        }
    }

    if (accesspoint && (WiFi.status() != WL_CONNECTED)) {
        // The accesspoint has been enabled, and we have not connected to any existing networks
        #if defined(AP_CHAN)
            Serial.println("Setting up Fixed Channel AccessPoint");
            Serial.print("  SSID     : ");
            Serial.println(stationList[0].ssid);
            Serial.print("  Password : ");
            Serial.println(stationList[0].password);
            Serial.print("  Channel  : ");
            Serial.println(AP_CHAN);
            WiFi.softAP(stationList[0].ssid, stationList[0].password, AP_CHAN);
        # else
            Serial.println("Setting up AccessPoint");
            Serial.print("  SSID     : ");
            Serial.println(stationList[0].ssid);
            Serial.print("  Password : ");
            Serial.println(stationList[0].password);
            WiFi.softAP(stationList[0].ssid, stationList[0].password);
        #endif
        #if defined(AP_ADDRESS)
            // User has specified the AP details; apply them after a short delay
            // (https://github.com/espressif/arduino-esp32/issues/985#issuecomment-359157428)
            delay(100);
            IPAddress local_IP(AP_ADDRESS);
            IPAddress gateway(AP_ADDRESS);
            IPAddress subnet(255,255,255,0);
            WiFi.softAPConfig(local_IP, gateway, subnet);
        #endif
        // Note AP details
        ip = WiFi.softAPIP();
        net = WiFi.subnetMask();
        gw = WiFi.gatewayIP();
        strcpy(apName, stationList[0].ssid);
        Serial.printf("IP address: %d.%d.%d.%d\r\n",ip[0],ip[1],ip[2],ip[3]);
        calcURLs();
        // Flash the LED to show we are connected
        for (int i = 0; i < 5; i++) {
            flashLED(150);
            delay(50);
        }
        // Start the DNS captive portal if requested
        if (stationList[0].dhcp == true) {
            Serial.println("Starting Captive Portal");
            dnsServer.start(DNS_PORT, "*", ip);
            captivePortal = true;
        }
    }
}

void setupWifi() {
    if (stationCount == 0) {
        Serial.println("\r\nFatal Error; Halting");
        while (true) {
            Serial.println("No wifi details have been configured; we cannot connect to existing WiFi or start our own AccessPoint, there is no point in proceeding.");
            delay(5000);
        }
    }
	
	 // Start Wifi and loop until we are connected or have started an AccessPoint
    while ((WiFi.status() != WL_CONNECTED) && !accesspoint)  {
        InitWiFi();
        delay(1000);
    }
	
	
}

void loopWiFi() {
    /*
     *  Just loop forever, reconnecting Wifi As necesscary in client mode
     * The stream and URI handler processes initiated by the startCameraServer() call at the
     * end of setup() will handle the camera and UI processing from now on.
    */
    if (accesspoint) {
        // Accespoint is permanently up, so just loop, servicing the captive portal as needed
        // Rather than loop forever, follow the watchdog, in case we later add auto re-scan.
        unsigned long start = millis();
        while (millis() - start < WIFI_WATCHDOG ) {
            delay(100);
            if (otaEnabled) ArduinoOTA.handle();
            handleSerial();
            if (captivePortal) dnsServer.processNextRequest();
        }
    } else {
        // client mode can fail; so reconnect as appropriate
        static bool warned = false;
        if (WiFi.status() == WL_CONNECTED) {
            // We are connected, wait a bit and re-check
            if (warned) {
                // Tell the user if we have just reconnected
                Serial.println("WiFi reconnected");
                warned = false;
            }
            // loop here for WIFI_WATCHDOG, turning debugData true/false depending on serial input..
            unsigned long start = millis();
            while (millis() - start < WIFI_WATCHDOG ) {
                delay(100);
                if (otaEnabled) ArduinoOTA.handle();
                handleSerial();
            }
        } else {
            // disconnected; attempt to reconnect
            if (!warned) {
                // Tell the user if we just disconnected
                WiFi.disconnect();  // ensures disconnect is complete, wifi scan cleared
                Serial.println("WiFi disconnected, retrying");
                warned = true;
            }
            InitWiFi();
        }
    }
}


#include <DNSServer.h>
#include <ESPmDNS.h>

//
#if defined(NO_OTA)
    bool otaEnabled = false;
#else
    bool otaEnabled = true;
#endif

// IP address, Netmask and Gateway, populated when connected
IPAddress ip;
IPAddress net;
IPAddress gw;

// Declare external function from app_httpd.cpp
extern void startCameraServer(int hPort, int sPort);

#if defined(MDNS_NAME)
    char mdnsName[] = MDNS_NAME;
#else
    char mdnsName[] = "esp32-cam";
#endif

// Ports for http and stream (override in myconfig.h)
#if defined(HTTP_PORT)
    int httpPort = HTTP_PORT;
#else
    int httpPort = 80;
#endif

#if defined(STREAM_PORT)
    int streamPort = STREAM_PORT;
#else
    int streamPort = 81;
#endif

// DNS server
const byte DNS_PORT = 53;
DNSServer dnsServer;
bool captivePortal = false;
char apName[64] = "Undefined";

// The app and stream URLs
char httpURL[64] = {"Undefined"};
char streamURL[64] = {"Undefined"};


#if defined(NTPSERVER)
    bool haveTime = true;
    const char* ntpServer = NTPSERVER;
    const long  gmtOffset_sec = NTP_GMT_OFFSET;
    const int   daylightOffset_sec = NTP_DST_OFFSET;
#else
    bool haveTime = false;
    const char* ntpServer = "";
    const long  gmtOffset_sec = 0;
    const int   daylightOffset_sec = 0;
#endif


// Select between full and simple index as the default.
#if defined(DEFAULT_INDEX_FULL)
    char default_index[] = "full";
#else
    char default_index[] = "simple";
#endif


void calcURLs() {
    // Set the URL's
    #if defined(URL_HOSTNAME)
        if (httpPort != 80) {
            sprintf(httpURL, "http://%s:%d/", URL_HOSTNAME, httpPort);
        } else {
            sprintf(httpURL, "http://%s/", URL_HOSTNAME);
        }
        sprintf(streamURL, "http://%s:%d/", URL_HOSTNAME, streamPort);
    #else
        Serial.println("Setting httpURL");
        if (httpPort != 80) {
            sprintf(httpURL, "http://%d.%d.%d.%d:%d/", ip[0], ip[1], ip[2], ip[3], httpPort);
        } else {
            sprintf(httpURL, "http://%d.%d.%d.%d/", ip[0], ip[1], ip[2], ip[3]);
        }
        sprintf(streamURL, "http://%d.%d.%d.%d:%d/", ip[0], ip[1], ip[2], ip[3], streamPort);
    #endif
}

void setupServer() {

    // NO OTA
    if (!otaEnabled) {
        Serial.println("OTA is disabled");

        if (!MDNS.begin(mdnsName)) {
          Serial.println("Error setting up MDNS responder!");
        }
        Serial.println("mDNS responder started");
    }

    //MDNS Config -- note that if OTA is NOT enabled this needs prior steps!
    MDNS.addService("http", "tcp", 80);
    Serial.println("Added HTTP service to MDNS server");

    // Set time via NTP server when enabled
    if (haveTime) {
        Serial.print("Time: ");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        printLocalTime(true);
    } else {
        Serial.println("Time functions disabled");
    }



    // Start the camera server
    startCameraServer(httpPort, streamPort);
}

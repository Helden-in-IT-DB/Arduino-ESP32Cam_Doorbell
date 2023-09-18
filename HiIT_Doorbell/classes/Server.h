
#ifndef SERVER_H
#define SERVER_H

#include <DNSServer.h>
#include <ESPmDNS.h>

class Server {
  private:
  public:
    Server(){}
    Server();
    // Declare external function from app_httpd.cpp
    extern void startCameraServer(int hPort, int sPort);
    void init();
    void calcURLs();
    void setupServer();
};

#endif
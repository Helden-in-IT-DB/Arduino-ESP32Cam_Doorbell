// Original Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef APP_HTTPD_H
#define APP_HTTPD_H

#include <esp_http_server.h>
#include <esp_timer.h>
#include <esp_camera.h>
#include <esp_int_wdt.h>
#include <esp_task_wdt.h>
#include <Arduino.h>
#include <WiFi.h>

#include "index/ov2640.h"
#include "index/ov3660.h"
#include "index/other.h"
#include "index/css.h"
#include "src/favicons.h"
#include "src/logo.h"

// Functions from the main .ino
extern void flashLED(int flashtime);
extern void setLamp(int newVal);
extern void printLocalTime(bool extraData);

// External variables declared in the main .ino
extern char myName[];
extern char myVer[];
extern char baseVersion[];
extern IPAddress ip;
extern IPAddress net;
extern IPAddress gw;
extern bool accesspoint;
extern char apName[];
extern bool captivePortal;
extern int httpPort;
extern int streamPort;
extern char httpURL[];
extern char streamURL[];
extern char default_index[];
extern int8_t streamCount;
extern unsigned long streamsServed;
extern unsigned long imagesServed;
extern int myRotation;
extern int minFrameTime;
extern int lampVal;
extern bool autoLamp;
extern String critERR;
extern bool debugData;
extern bool haveTime;
extern int sketchSize;
extern int sketchSpace;
extern String sketchMD5;
extern bool otaEnabled;
extern char otaPassword[];
extern unsigned long xclk;
extern int sensorPID;

class App {
  private:
    
  public:
    App(){}
    App();
    void init();
    void serialDump();
    static esp_err_t capture_handler(httpd_req_t *req);
    static esp_err_t stream_handler(httpd_req_t *req);
    static esp_err_t cmd_handler(httpd_req_t *req);
    static esp_err_t status_handler(httpd_req_t *req);
    static esp_err_t info_handler(httpd_req_t *req);
    static esp_err_t favicon_16x16_handler(httpd_req_t *req);
    static esp_err_t favicon_32x32_handler(httpd_req_t *req);
    static esp_err_t favicon_ico_handler(httpd_req_t *req);
    static esp_err_t logo_svg_handler(httpd_req_t *req);
    static esp_err_t dump_handler(httpd_req_t *req);
    static esp_err_t stop_handler(httpd_req_t *req);
    static esp_err_t style_handler(httpd_req_t *req);
    static esp_err_t streamviewer_handler(httpd_req_t *req);
    static esp_err_t error_handler(httpd_req_t *req);
    static esp_err_t index_handler(httpd_req_t *req);
    void startCameraServer(int hPort, int sPort);
};

#endif
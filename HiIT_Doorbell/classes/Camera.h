
#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include <esp_camera.h>

class Camera {
  private:
    camera_config_t _config;
    int _sensorPID;
    int _myRotation = CAM_ROTATION;
    int _minFrameTime = MIN_FRAME_TIME;
  public:
    Camera() {}
    Camera();
    void StartCamera();
    void setupCamera();
};

#endif

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "raylib.h"
#include "rcamera.h"

// holds camera obj
class CameraController {
public:
    // constructors/destructor

    CameraController(Camera3D &camera);

    ~CameraController();

    void moveUp(float amount);
    //public methods
    void setCameraMode(int cameraMode);

    // public variables
   
    int cameraMode = CAMERA_FIRST_PERSON;
    
    Camera3D& camera;
private:
};

#endif

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "../Headers/CameraController.h"
#include "raylib.h"

class PlayerController : public CameraController {
public:
    PlayerController(Camera3D& inputCamera);
    ~PlayerController();

private:
};

#endif
//
// Created by Kyle Sullivan on 11/26/24.
//

#include "raylib.h"
#include "rcamera.h"
#include "Headers/CameraController.h"

CameraController::CameraController(Camera3D &camera) : camera(camera) {
    setCameraMode(CAMERA_FIRST_PERSON);
}

CameraController::~CameraController(){ }

void CameraController::setCameraMode(int cameraMode) {
    this->cameraMode = cameraMode;
}


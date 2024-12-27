#ifndef PLAYER_H
#define PLAYER_H 

#include "../unused /PlayerController.h"
#include "raylib.h"
#include "rcamera.h"

class Player {
public:
    Player(CameraController& cameraController);
    ~Player();

    Vector3 position;
    Vector3 target;
    Vector3  up;
    float speed;
    bool canJump; 
    bool isPlayerColliding{};
    BoundingBox boundingBox;
    
    CameraController& cameraContoller;

    void moveUp(float amount);

    void updateBoundingBox();

    void Update();

    bool isOnGround();

    void Jump();

    Vector3 getPosition();
};


#endif
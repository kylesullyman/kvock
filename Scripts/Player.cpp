//
// Created by Kyle Sullivan on 11/27/24.
//

#include "Headers/Player.h"
#include <iostream>

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

Player::Player(CameraController &cameraController)
        : position(cameraController.camera.position),
          target(cameraController.camera.target),
          up(cameraController.camera.up),
          speed(0.0f),
          canJump(true),
          cameraContoller(cameraController) {
}

Player::~Player() {}


void Player::updateBoundingBox() {
    float boxWidth = 1.0f; // Example width of the bounding box
    float boxHeight = 1.5f; // Example height of the bounding box
    float boxDepth = 1.0f; // Example depth of the bounding box

    Vector3 playerPos = this->position; // Player's current position

    // Set the bounding box coordinates
    boundingBox.min = Vector3{playerPos.x - boxWidth / 2,
                              playerPos.y - boxHeight / 2 - 0.5f,
                              playerPos.z - boxDepth / 2};

    boundingBox.max = Vector3{playerPos.x + boxWidth / 2,
                              playerPos.y + boxHeight / 2,
                              playerPos.z + boxDepth / 2};
}

void Player::Update() {
    updateBoundingBox();

    if (IsKeyDown(KEY_W)) position.z -= PLAYER_HOR_SPD * GetFrameTime();
    if (IsKeyDown(KEY_S)) position.z += PLAYER_HOR_SPD * GetFrameTime();
    if (IsKeyDown(KEY_A)) position.x -= PLAYER_HOR_SPD * GetFrameTime();
    if (IsKeyDown(KEY_D)) position.x += PLAYER_HOR_SPD * GetFrameTime();

    // Ensure gravity affects the player
    if (!isOnGround()) {
        position.y -= G * GetFrameTime();  // Apply gravity
    }

    // Update bounding box after moving
    updateBoundingBox();

    // Check if player is on the ground
    canJump = isOnGround();
}


bool Player::isOnGround() {
    // Define the starting point of the ray (bottom center of the player's bounding box)
    Vector3 rayStart = {position.x, boundingBox.min.y, position.z};
    // Define the direction of the ray (straight down)
    Vector3 rayDirection = {0.0f, -1.0f, 0.0f};
    // Define the length of the ray (short distance)
    float rayLength = 0.1f;

    Ray ray = {rayStart, rayDirection};
    RayCollision collision = GetRayCollisionBox(ray, (BoundingBox) {{-16.0f, -0.1f, -16.0f},
                                                                    {16.0f,  0.1f,  16.0f}}); // Ground bounding box example

    return collision.hit;
}

void Player::Jump() {
    if (isOnGround()) {
        position.y += PLAYER_JUMP_SPD * GetFrameTime();
        canJump = false;  // Player is in the air after jumping
    }
    std::cout << "isOnGround: " << isOnGround() << std::endl;
}

Vector3 Player::getPosition() { return position; }
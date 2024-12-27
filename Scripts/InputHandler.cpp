//
// Created by Kyle Sullivan on 11/26/24.
//
#include "Headers/InputHandler.h"
#include "raylib.h"
#include "Headers/CameraController.h"
#include <iostream>

InputHandler::InputHandler(Player& player) : player(player) {
}

InputHandler::~InputHandler() {}

void InputHandler::Update() {
    if(IsKeyDown(KEY_SPACE) && player.isOnGround()){
        player.Jump();
    }
}

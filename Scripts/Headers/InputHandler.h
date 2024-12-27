#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Player.h"
#include "CameraController.h"

class InputHandler {
public:
    InputHandler(Player& player);

    ~InputHandler();

    void Update();
private:
   Player& player;
};

#endif
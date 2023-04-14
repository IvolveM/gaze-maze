#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Camera.h"

class Player: public Camera{
    private:
        float gravityAcceleration = 20.0f;
        float speed = 3.0f;
        float jumpSpeed = 2.0f;

        glm::vec2 movingDirection;
        float verticalSpeed = 0.0f;
        float verticalAcceleration = 0.0f;
        
        bool isMoving = false;
        bool isOnGround = false;
        void handleVerticalMovement(float dt);
    public:
        enum class InputEvent
        {
            FORWARDS, BACKWARDS, LEFT, RIGHT, JUMP
        };
        Player();
        void handleKeyInput(InputEvent event);

        void update(float dt);
};
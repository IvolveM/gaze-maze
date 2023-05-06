#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "../objects/Collisioner.h"
#include "../objects/Mesh.h"
#include "../entities/ParticleGenerator.h"

class Player: public Camera{
    private:
        Collisioner collisioner;
        ParticleGenerator particleGenerator;

        float gravityAcceleration = 20.0f;
        float speed = 3.0f;
        float jumpSpeed = 1.8f;

        glm::vec2 movingDirection;
        float verticalSpeed = 0.0f;
        float verticalAcceleration = 0.0f;
        
        bool isMoving = false;
        bool isOnGround = false;
        void handleVerticalMovement(float dt);

        glm::vec3 resolveCollision(Collisioner c);
    public:
        enum class InputEvent
        {
            FORWARDS, BACKWARDS, LEFT, RIGHT, JUMP
        };
        Player();
        void handleKeyInput(InputEvent event);
        
        void update(float dt);
        void doCollisions(Mesh m);
        void draw();
};
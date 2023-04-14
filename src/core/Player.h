#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "../objects/Collisioner.h"
#include "../objects/Mesh.h"

class Player: public Camera{
    private:
        glm::vec3 acceleration;
        glm::vec3 velocity;
        bool isMoving;
        void accelerate(glm::vec3 direction);

        Collisioner collisioner;

    public:
        enum class InputEvent
        {
            FORWARDS, BACKWARDS, LEFT, RIGHT, JUMP
        };
        Player();
        void handleKeyInput(InputEvent event);

        void update();
        void doCollisions(Mesh m);
};
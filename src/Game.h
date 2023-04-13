#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <exception>
#include <functional> // for std::bind

#include "stb_image.h"

#include "resources/shaders/Shader.h"
#include "resources/ResourceManager.h"
#include "objects/based/Cube.h"
#include "objects/based/Plane.h"
#include "core/Player.h"
#include "utils/MazeLoader.h"

class Game{
    private:
        GLFWwindow* window;

        glm::mat4 proj;
        glm::mat4 view;

        Player player;
        std::vector<Cube*> mazeCubes;
        Plane* ground;

        void initGlfw();
        void initShaders();
        void initTextures();

        void render();
        void processInput();
        void processEvents();

        void handleMouse();
    public:
        Game(int width, int height);
        ~Game();

        void mainloop();
};

struct FailedGLADInit : public std::exception {
    const char * what () const throw () {
        return "Failed to initialize GLAD";
    }
};

struct FailedGLFWInit : public std::exception {
    const char * what () const throw () {
        return "Failed to initialize GLFW";
    }
};

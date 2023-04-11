#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <exception>

#include "stb_image.h"

#include "resources/shaders/Shader.h"

class Game{
    private:
        GLFWwindow* window;

        Shader shader;

        void initGlfw();
        void initShaders();

        void render();
        void processInput();
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

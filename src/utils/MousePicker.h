#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

class MousePicker {
    public:
        MousePicker();
        ~MousePicker();

        static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
    
    private:
    
};
#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../objects/model/Model.h"

#include <iostream>
#include <unordered_map>

class ColorPicker {
    public:
        ColorPicker();
        ~ColorPicker();

        static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
        int addModel(Model* m);
        Model* getModelByColor(unsigned char color[4]);
        void removeModelByColor(unsigned char color[4]);
        void drawModels();

    private:
        int currId = 30;
        std::unordered_map<int, Model*> modelMap;
};
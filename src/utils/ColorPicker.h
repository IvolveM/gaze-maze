#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../objects/model/Model.h"

#include <iostream>
#include <unordered_map>

/***
 * This class is not responsible for managing the lifetime of its objects
*/

class ColorPicker {
    public:
        ColorPicker();
        ~ColorPicker();

        int addModel(Model* m);
        Model* getModelByColor(unsigned char color[4]);
        void removeModelByColor(unsigned char color[4]);
        void drawModels();

    private:
        int currId = 1;
        std::unordered_map<int, Model*> modelMap;
};
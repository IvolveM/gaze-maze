#include "ColorPicker.h"

extern bool clicked;

ColorPicker::ColorPicker() {
    
}

ColorPicker::~ColorPicker() {
    
}

void ColorPicker::mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        clicked = true;    
    }
}

int ColorPicker::addModel(Model* m) {
    this->modelMap[currId] = m;
    currId++;
    return currId - 1;
}

Model* ColorPicker::getModelByColor(unsigned char color[4]) {
    return this->modelMap[static_cast<int>(color[0])];
}

void ColorPicker::removeModelByColor(unsigned char color[4]) {
    this->modelMap.erase(static_cast<int>(color[0]));
}

void ColorPicker::drawModels() {
    for (const auto& modelPair : this->modelMap) {
        modelPair.second->drawPicker(modelPair.first);
    }
}


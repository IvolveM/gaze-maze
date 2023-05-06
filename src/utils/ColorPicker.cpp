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
    currId += 10;
    return currId - 10;
}

Model* ColorPicker::getModelByColor(unsigned char color[4]) {
    return this->modelMap[static_cast<int>(color[0])];
}

void ColorPicker::removeModelByColor(unsigned char color[4]) {
    this->modelMap.erase(static_cast<int>(color[0]));
}

std::vector<std::pair<Model*, int>> ColorPicker::getAllModels() {
    std::vector<std::pair<Model*, int>> ret;
    for (const auto& kvp : this->modelMap) {
        ret.push_back(std::pair(kvp.second, kvp.first));
    }
    return ret;
}


#include "MousePicker.h"

MousePicker::MousePicker() {
    
}

MousePicker::~MousePicker() {
    
}

void MousePicker::mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        double xpos, ypos;
        xpos = width / 2;
        ypos = height / 2;

        std::cout << "xpos: " << xpos << " ypos: " << ypos << std::endl;

        // Read the pixel color at the cursor position
        unsigned char data[4];
        glReadPixels(xpos, height - ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // Convert the color to an integer value
        std::cout << "R: " << static_cast<int>(data[0]) << " G: " << static_cast<int>(data[1]) << " B: " << static_cast<int>(data[2]) << std::endl;    }
}
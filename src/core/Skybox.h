#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../resources/shaders/Shader.h"
#include "../resources/ResourceManager.h"
#include <string>
#include <vector>


class Skybox {
    public:
        Skybox();
        ~Skybox();

        void draw(glm::mat4 view, glm::mat4 proj);
  
    private:
        std::vector<float> skyboxVertices;
        std::vector<unsigned int> skyboxIndices;
        unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
        unsigned int cubemapTexture;

        Shader shader;
        std::string parentDir = "/home/ivan/Documents/School/bach2/Computer\ Graphics/gaze-maze/assets/skybox/";
        std::string cubemap[6] = {
            parentDir + "right.jpg",
            parentDir + "left.png",
            parentDir + "top.png",
            parentDir + "bottom.png",
            parentDir + "front.png",
            parentDir + "back.png"
        };
};
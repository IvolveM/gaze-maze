#pragma once
#include <vector>

#include "../Mesh.h"
#include "../../resources/ResourceManager.h"

class Cube : public Mesh {
    private:
        unsigned int VAO;
        std::vector<float> vertices;

        Shader shader;
        Texture texture;
    public:
        Cube(glm::vec3 position);

        void draw() override;
};
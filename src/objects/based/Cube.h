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

        void initVertices();
        void initDefaultVaoVbo();

    public:
        Cube(glm::vec3 position);
        Cube(std::vector<glm::vec3> instancePositions, glm::vec3 size = glm::vec3(1.0f));

        void draw() override;
};
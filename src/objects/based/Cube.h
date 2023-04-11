#pragma once
#include <vector>

#include "../Mesh.h"
#include "../../resources/ResourceManager.h"

class Cube : public Mesh {
    private:
        unsigned int VAO;
        std::vector<float> vertices;
    public:
        Cube();

        void draw() override;
};
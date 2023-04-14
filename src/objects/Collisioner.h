#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

// Collisioner is always a box shape
class Collisioner {
    public:
        Collisioner() = default;
        Collisioner(glm::vec3 size, glm::vec3 center);
        ~Collisioner();

        void setCenter(glm::vec3 center);
        glm::vec3 getMinVec();
        glm::vec3 getMaxVec();

        bool isColliding(Collisioner col);
        static bool isColliding(Collisioner col1, Collisioner col2);

        glm::vec3 minVec;
        glm::vec3 maxVec;
    private:
        glm::vec3 center;
        glm::vec3 size;
};
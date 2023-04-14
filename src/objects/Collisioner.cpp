#include "Collisioner.h"

Collisioner::Collisioner(glm::vec3 size, glm::vec3 center) :
    center{center},
    size{size}    
{
    this->minVec = center - (size * 0.5f);
    this->maxVec = center + (size * 0.5f);
}

Collisioner::~Collisioner() {

}

void Collisioner::setCenter(glm::vec3 center) {
    this->center = center;
    this->minVec = center - (size * 0.5f);
    this->maxVec = center + (size * 0.5f);
}

glm::vec3 Collisioner::getMinVec() {
    return this->minVec;
}

glm::vec3 Collisioner::getMaxVec() {
    return this->maxVec;
}

bool Collisioner::isColliding(Collisioner col) {
    // std::cout << "box: " << glm::to_string(col.minVec) << " " << glm::to_string(col.maxVec) << std::endl;
    return this->maxVec.x > col.minVec.x &&
            this->minVec.x < col.maxVec.x &&
            this->maxVec.y > col.minVec.y &&
            this->minVec.y < col.maxVec.y &&
            this->maxVec.z > col.minVec.z &&
            this->minVec.z < col.maxVec.z;
}

static bool isColliding(Collisioner col1, Collisioner col2) {
    return col1.maxVec.x > col2.minVec.x &&
            col1.minVec.x < col2.maxVec.x &&
            col1.maxVec.y > col2.minVec.y &&
            col1.minVec.y < col2.maxVec.y &&
            col1.maxVec.z > col2.minVec.z &&
            col1.minVec.z < col2.maxVec.z;
}
#include "Mesh.h"

Mesh::~Mesh(){

}

Mesh::Mesh(glm::vec3 position, glm::vec3 size)
:   position{position},
    size{size},
    instancing{false},
    collisioner{size, position}
{

}

Mesh::Mesh(std::vector<glm::vec3> instancePositions, glm::vec3 size)
:   instancing{true},
    size{size}
{
    for (auto pos : instancePositions) {
        this->instanceCollisioners.push_back(Collisioner(this->size, pos));
    }
}

void Mesh::draw(){
    
}

bool Mesh::isColliding(Collisioner c) {
    if (this->instancing) {
        for (auto box : this->instanceCollisioners) {
            if (box.isColliding(c)) {
                return true;
            }
        }
        return false;
    }
    return this->collisioner.isColliding(c);
}

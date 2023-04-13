#include "Mesh.h"

Mesh::~Mesh(){

}

Mesh::Mesh(glm::vec3 position)
:   position{position},
    instancing{false} {

}

Mesh::Mesh(std::vector<glm::vec3> instancePositions)
:   position{position},
    instancing{true} {

}

void Mesh::draw(){
    
}
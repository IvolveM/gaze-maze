#include "Mesh.h"

Mesh::~Mesh(){

}

Mesh::Mesh(glm::vec3 position, glm::vec3 size)
:   position{position},
    size{size},
    instancing{false}
{

}

Mesh::Mesh(std::vector<glm::vec3> instancePositions)
:   instancing{true} {
    
}

void Mesh::draw(){
    
}
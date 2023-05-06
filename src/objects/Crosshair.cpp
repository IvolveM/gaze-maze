#include "Crosshair.h"

Crosshair::Crosshair(float width, float height) 
: shader{ResourceManager::getShader("default2D")}
{
    vertices = {
        -width/2, 0,
        width/2, 0,
        0, -height/2,
        0, height/2
    };


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &(vertices.front()), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}

Crosshair::~Crosshair() {

}

void Crosshair::draw() {
    shader.use();
    glLineWidth(2.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
}
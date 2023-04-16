
#include "Cube.h"

Cube::Cube(glm::vec3 position) : 
	Mesh{position, glm::vec3(1.0f), Collisioner::BoundingBoxType::CUBE},
    shader{ResourceManager::getShader("defaultShader")},
    texture{ResourceManager::getTexture("defaultTexture")}
{
	initVertices();
	initDefaultVaoVbo();
}

Cube::Cube(std::vector<glm::vec3> instancePositions, glm::vec3 size) :
	Mesh{instancePositions, size, Collisioner::BoundingBoxType::CUBE},
    shader{ResourceManager::getShader("instanceShader")},
    texture{ResourceManager::getTexture("defaultTexture")}
{
	initVertices();

	for (auto pos : instancePositions) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		this->instanceModelMatrices.push_back(model);
	}

	initDefaultVaoVbo();

	unsigned int instancingVBO;
    glGenBuffers(1, &instancingVBO);

    glBindBuffer(GL_ARRAY_BUFFER, instancingVBO);
    glBufferData(GL_ARRAY_BUFFER, this->instanceModelMatrices.size() * sizeof(glm::mat4), &this->instanceModelMatrices[0], GL_STATIC_DRAW);
	size_t vec4Size = sizeof(glm::vec4);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)(vec4Size));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
}

void Cube::initVertices() {
    this->vertices = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };
}

void Cube::initDefaultVaoVbo() {
	glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &(vertices.front()), GL_STATIC_DRAW); // OR GL_DYNAMIC_DRAW

    // pointer for vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // pointer for texture uv's
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Cube::draw()
{
    shader.use();

	if (!this->instancing) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->position);
		// model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		shader.setMatrixFloat4("model", model);

		glBindVertexArray(VAO);
		texture.bindTexture();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	else {
		glBindVertexArray(VAO);
		texture.bindTexture();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, instanceModelMatrices.size());
		glBindVertexArray(0);
	}
}
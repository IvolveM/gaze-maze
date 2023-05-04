
#include "Cube.h"

Cube::Cube(glm::vec3 position) : 
	Mesh{position, glm::vec3(1.0f), Collisioner::BoundingBoxType::CUBE},
    shader{ResourceManager::getShader("default")},
    diffuse{ResourceManager::getTexture("wallDiffuse")},
	specular{ResourceManager::getTexture("wallDiffuse")}
{
	initVertices();
	initDefaultVaoVbo();
}

Cube::Cube(std::vector<glm::vec3> instancePositions, glm::vec3 size) :
	Mesh{instancePositions, size, Collisioner::BoundingBoxType::CUBE},
    shader{ResourceManager::getShader("defaultInstancing")},
    diffuse{ResourceManager::getTexture("wallDiffuse")},
	specular{ResourceManager::getTexture("wallDiffuse")}
{
	initVertices();

	for (auto pos : instancePositions) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		// model = glm::translate(model, glm::vec3{0.0f, -0.5f, 0.0f});
		// model = glm::scale(model, glm::vec3{1.0f, 0.2f, 1.0f});
		this->instanceModelMatrices.push_back(model);
	}

	initDefaultVaoVbo();

	unsigned int instancingVBO;
    glGenBuffers(1, &instancingVBO);

    glBindBuffer(GL_ARRAY_BUFFER, instancingVBO);
    glBufferData(GL_ARRAY_BUFFER, this->instanceModelMatrices.size() * sizeof(glm::mat4), &this->instanceModelMatrices[0], GL_STATIC_DRAW);
	size_t vec4Size = sizeof(glm::vec4);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)(vec4Size));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4*vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
}

void Cube::initVertices() {
    this->vertices = {
		// positions  		 // normals         // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,0.5f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f,0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f,0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f,0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f,0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f,0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	// pointer for normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // pointer for texture uv's
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Cube::draw()
{
    shader.use();
	glBindVertexArray(VAO);
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	diffuse.bindTexture(GL_TEXTURE0);
	specular.bindTexture(GL_TEXTURE1);

	if (!this->instancing) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->position);
		// model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		shader.setMatrixFloat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	else {
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, instanceModelMatrices.size());
		glBindVertexArray(0);
	}
}
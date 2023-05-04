#pragma once

#include <vector>
#include "../../resources/ResourceManager.h"
#include "../../stb_image.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // glm::vec3 Tangent;
    // glm::vec3 Bitangent;
	// int m_BoneIDs[MAX_BONE_INFLUENCE];
	// float m_Weights[MAX_BONE_INFLUENCE];
};

struct MeshTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class ModelMesh{
    private:
        // mesh Data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshTexture>      textures;
        unsigned int VAO;
        unsigned int VBO, EBO;

        void setupMesh();
    public:
        ModelMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
        void draw(Shader &shader);
};
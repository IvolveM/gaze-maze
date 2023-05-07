#pragma once
#include <string>
#include <vector>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "./ModelMesh.h"
#include "./AssimpGLMHelpers.h"
#include "./BoneInfo.h"

#define MAX_BONE_WEIGHTS 4

class Model{
    public:
        Model(
            char *path,  
            glm::vec3 position = glm::vec3{0.0f}, 
            glm::vec3 size = glm::vec3{1.0f},
            Shader shader = {ResourceManager::getShader("mesh")},
            bool flipUvs = true
        );
        void draw();
        void drawPicker(int id);
        void move(glm::vec3 direction);

        auto& getBoneInfoMap() { return boneInfoMap; }
        int& getBoneCount() { return boneCounter; }
    private:
        Shader shader;
        Shader pickerShader;
        glm::vec3 position, size;

        std::vector<ModelMesh> meshes;
        std::string directory;
        void loadModel(std::string path, bool flipUvs);
        void processNode(aiNode *node, const aiScene *scene);
        ModelMesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

        // bones
        std::map<std::string, BoneInfo> boneInfoMap; //
        int boneCounter = 0;

        void setVertexBoneDataToDefault(Vertex& vertex);
        // Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        void setVertexBoneData(Vertex& vertex, int boneID, float weight);
        void extractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
};
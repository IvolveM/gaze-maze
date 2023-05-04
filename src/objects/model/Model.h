#pragma once
#include <string>
#include <vector>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "./ModelMesh.h"

class Model{
    public:
        Model(char *path);
        void draw();
    private:
        Shader shader;

        std::vector<ModelMesh> meshes;
        std::string directory;
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        ModelMesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
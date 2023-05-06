#include "Model.h"

Model::Model(
    char *path,  
    glm::vec3 position,
    glm::vec3 size
)
    : shader{ResourceManager::getShader("mesh")},
    pickerShader{ResourceManager::getShader("picker")},
    position{position},
    size{size}
{
    loadModel(path);
}

void Model::draw()
{
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
    model = glm::scale(model, this->size);
    shader.setMatrixFloat4("model", model);
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].draw(shader);
    }
}

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    // postprocessing options:
    // * aiProcess_GenNormals: generates normals for all vectors
    // * aiProcess_OptimizeMeshes: joins several meshes to reduce draw calls
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process meshes
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // process children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

ModelMesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshTexture> textures;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else{
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<MeshTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<MeshTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return ModelMesh(vertices, indices, textures);
}

std::vector<MeshTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<MeshTexture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        MeshTexture texture;

        std::string filename = std::string(str.C_Str());
        std::string path = directory + '/' + filename;
        texture.id = ResourceManager::setTexture(filename, path.c_str()).getId();
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}

void Model::drawPicker() {
    this->pickerShader.use();
    this->pickerShader.setVec3("idCol", glm::vec3(255.0f, 0.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
    model = glm::scale(model, this->size);
    pickerShader.setMatrixFloat4("model", model);
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].draw(pickerShader);
    }
}
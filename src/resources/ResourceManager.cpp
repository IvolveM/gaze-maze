#include "ResourceManager.h"

// initialize members
std::map<std::string, Shader> ResourceManager::shaders{};
std::map<std::string, Texture> ResourceManager::textures{};

Texture ResourceManager::setTexture(std::string textureName, const char *texturePath)
{
    if (textures.count(textureName) != 0){
        return getTexture(textureName);
    }
    Texture texture = Texture(texturePath);
    textures.emplace(textureName, texture);
    return texture;
}

Shader ResourceManager::addShader(std::string shaderName, std::string vertexPath, std::string fragmentPath)
{
    if (shaders.count(shaderName) != 0){
        throw DuplicateResourceException("Shader -> " + shaderName);
    }
    Shader shader = Shader(vertexPath.c_str(), fragmentPath.c_str());
    shaders.emplace(shaderName, shader);
    return shader;
}

Texture ResourceManager::getTexture(std::string textureName) {
    if (textures.count(textureName) == 0){
        throw NoResourceFoundException("Texture -> " + textureName);
    }
    return textures.at(textureName);
}

Shader ResourceManager::getShader(std::string shaderName) {
    if (shaders.count(shaderName) == 0){
        throw NoResourceFoundException("Shader -> " + shaderName);
    }
    return shaders.at(shaderName);
}

void ResourceManager::initShaders()
{
    std::string shaderDirectory = "../assets/shaders/";

    std::string defaultPath = shaderDirectory + "defaultShader/default";
    std::string meshPath    = shaderDirectory + "meshShader/mesh";
    addShader("default", appendVert(defaultPath), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    // some materials: http://devernay.free.fr/cours/opengl/materials.html
    Shader cubeShader = getShader("default");
    cubeShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    cubeShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    cubeShader.setFloat("material.shininess", 0.25f);
    cubeShader.setFloat3("light.position", 0.2f, 0.2f, 0.2f);
    cubeShader.setFloat3("light.ambient", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat3("light.diffuse", 0.5f, 0.5f, 0.5f); // darkened
    cubeShader.setFloat3("light.specular", 1.0f, 1.0f, 1.0f);

    addShader("defaultInstancing", appendVert(defaultPath, true), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    Shader insanceShader = getShader("defaultInstancing");
    insanceShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    insanceShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    insanceShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    insanceShader.setFloat("material.shininess", 0.25f);
    insanceShader.setFloat3("light.position", 0.2f, 2.0f, 0.2f);
    insanceShader.setFloat3("light.ambient", 1.0f, 1.0f, 1.0f);
    insanceShader.setFloat3("light.diffuse", 1.0f, 1.0f, 1.0f); // darkened
    insanceShader.setFloat3("light.specular", 0.5f, 0.5f, 0.5f);

    addShader("mesh", appendVert(defaultPath), appendFrag(meshPath)).use().setBlockBinding("Matrices", 0);
}

void ResourceManager::initTextures(){
    setTexture("defaultTexture", "../assets/textures/wall2.jpg");
    setTexture("groundTexture", "../assets/textures/ground2.jpg");
}

std::string ResourceManager::appendVert(const std::string& path, bool instancing){
    if (instancing){
        return path + "Instancing.vert";
    }
    return path + ".vert";
}

std::string ResourceManager::appendFrag(const std::string& path, bool instancing){
    if (instancing){
        return path + "Instancing.frag";
    }
    return path + ".frag";
}
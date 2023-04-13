#include "ResourceManager.h"


// initialize members
std::map<std::string, Shader> ResourceManager::shaders{};
std::map<std::string, Texture> ResourceManager::textures{};

void ResourceManager::setTexture(std::string textureName, const char *texturePath)
{
    if (shaders.count(textureName) != 0){
        throw DuplicateResourceException("Texture -> " + textureName);
    }
    Texture texture = Texture(texturePath);
    textures.emplace(textureName, texture);
}

void ResourceManager::addShader(std::string shaderName, const char *vertexCode, const char *fragmentCode)
{
    if (shaders.count(shaderName) != 0){
        throw DuplicateResourceException("Shader -> " + shaderName);
    }
    Shader shader = Shader(vertexCode, fragmentCode);
    shaders.emplace(shaderName, shader);
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
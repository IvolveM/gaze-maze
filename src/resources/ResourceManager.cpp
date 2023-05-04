#include "ResourceManager.h"

// initialize members
std::map<std::string, Shader> ResourceManager::shaders{};
std::map<std::string, Texture> ResourceManager::textures{};

Texture ResourceManager::setTexture(std::string textureName, std::string texturePath)
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
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.0f,  0.0f, 0.0f),
        glm::vec3( 0.0f, 0.0f, 30.0f)
    };

    std::string shaderDirectory = "../assets/shaders/";

    std::string defaultPath = shaderDirectory + "defaultShader/default";
    std::string meshPath    = shaderDirectory + "meshShader/mesh";
    addShader("default", appendVert(defaultPath), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    addShader("defaultInstancing", appendVert(defaultPath, true), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    addShader("mesh", appendVert(defaultPath), appendFrag(meshPath)).use().setBlockBinding("Matrices", 0);

    // some materials: http://devernay.free.fr/cours/opengl/materials.html
    Shader cubeShader = getShader("default");
    cubeShader.use();
    cubeShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    cubeShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    cubeShader.setFloat("material.shininess", 0.25f);
    // directional light
    cubeShader.setFloat3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    cubeShader.setFloat3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    cubeShader.setFloat3("dirLight.diffuse", 0.5f, 0.5f, 0.5f); // darkened
    cubeShader.setFloat3("dirLight.specular", 0.1f, 0.1f, 0.1f);
    // point light 1
    cubeShader.setFloat3("pointLights[0].position", pointLightPositions[0]);
    cubeShader.setFloat3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setFloat3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setFloat3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[0].constant", 1.0f);
    cubeShader.setFloat("pointLights[0].linear", 0.09f);
    cubeShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    cubeShader.setFloat3("pointLights[1].position", pointLightPositions[1]);
    cubeShader.setFloat3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    cubeShader.setFloat3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    cubeShader.setFloat3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[1].constant", 1.0f);
    cubeShader.setFloat("pointLights[1].linear", 0.09f);
    cubeShader.setFloat("pointLights[1].quadratic", 0.032f);

    Shader insanceShader = getShader("defaultInstancing");
    insanceShader.use();
    insanceShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    insanceShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    insanceShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    insanceShader.setFloat("material.shininess", 0.25f);
    // directional light
    insanceShader.setFloat3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    insanceShader.setFloat3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    insanceShader.setFloat3("dirLight.diffuse", 0.5f, 0.5f, 0.5f); // darkened
    insanceShader.setFloat3("dirLight.specular", 0.1f, 0.1f, 0.1f);

    // point light 1
    insanceShader.setFloat3("pointLights[0].position", pointLightPositions[0]);
    insanceShader.setFloat3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    insanceShader.setFloat3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    insanceShader.setFloat3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    insanceShader.setFloat("pointLights[0].constant", 1.0f);
    insanceShader.setFloat("pointLights[0].linear", 0.09f);
    insanceShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    insanceShader.setFloat3("pointLights[1].position", pointLightPositions[1]);
    insanceShader.setFloat3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    insanceShader.setFloat3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    insanceShader.setFloat3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    insanceShader.setFloat("pointLights[1].constant", 1.0f);
    insanceShader.setFloat("pointLights[1].linear", 0.09f);
    insanceShader.setFloat("pointLights[1].quadratic", 0.032f);

    Shader meshShader = getShader("mesh");
    meshShader.use();
    meshShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    meshShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    meshShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    meshShader.setFloat("material.shininess", 0.25f);
    // directional light
    meshShader.setFloat3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    meshShader.setFloat3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    meshShader.setFloat3("dirLight.diffuse", 0.5f, 0.5f, 0.5f); // darkened
    meshShader.setFloat3("dirLight.specular", 0.1f, 0.1f, 0.1f);

    // point light 1
    meshShader.setFloat3("pointLights[0].position", pointLightPositions[0]);
    meshShader.setFloat3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    meshShader.setFloat3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    meshShader.setFloat3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    meshShader.setFloat("pointLights[0].constant", 1.0f);
    meshShader.setFloat("pointLights[0].linear", 0.09f);
    meshShader.setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    meshShader.setFloat3("pointLights[1].position", pointLightPositions[1]);
    meshShader.setFloat3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    meshShader.setFloat3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    meshShader.setFloat3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    meshShader.setFloat("pointLights[1].constant", 1.0f);
    meshShader.setFloat("pointLights[1].linear", 0.09f);
    meshShader.setFloat("pointLights[1].quadratic", 0.032f);
}

void ResourceManager::initTextures(){
    std::string texturesPath = "../assets/textures/";
    setTexture("wallDiffuse", texturesPath + "wall/diffuse.jpg");

    setTexture("groundDiffuse", texturesPath + "ground/diffuse.jpg");
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
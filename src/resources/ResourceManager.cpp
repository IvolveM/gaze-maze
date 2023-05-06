#include "ResourceManager.h"

// initialize members
std::map<std::string, Shader> ResourceManager::shaders{};
std::map<std::string, Texture> ResourceManager::textures{};

Texture ResourceManager::setTexture(std::string textureName, std::string texturePath, bool pixelated)
{
    if (textures.count(textureName) != 0){
        return getTexture(textureName);
    }
    Texture texture = Texture(texturePath, pixelated);
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
        std::cout << "Texture -> " + textureName << std::endl;
        throw NoResourceFoundException("Texture -> " + textureName);
    }
    return textures.at(textureName);
}

Shader ResourceManager::getShader(std::string shaderName) {
    if (shaders.count(shaderName) == 0){
        std::cout << "Shader -> " + shaderName << std::endl;
        throw NoResourceFoundException("Shader -> " + shaderName);
    }
    return shaders.at(shaderName);
}

void ResourceManager::initShaders(glm::vec3 pointLightPositions[])
{
    std::string shaderDirectory = "../assets/shaders/";

    std::string defaultPath = shaderDirectory + "defaultShader/default";
    std::string meshPath    = shaderDirectory + "meshShader/mesh";
    std::string skyboxPath  = shaderDirectory + "skyboxShader/skybox";
    std::string particlePath  = shaderDirectory + "particleShader/particle";
    std::string pickerPath  = shaderDirectory + "pickerShader/picker";

    addShader("default", appendVert(defaultPath), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    addShader("defaultInstancing", appendVert(defaultPath, true), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    addShader("mesh", appendVert(defaultPath), appendFrag(defaultPath)).use().setBlockBinding("Matrices", 0);
    addShader("skybox", appendVert(skyboxPath), appendFrag(skyboxPath)).use().setBlockBinding("Matrices", 0);
    addShader("particle", appendVert(particlePath), appendFrag(particlePath)).use().setBlockBinding("Matrices", 0);
    addShader("picker", appendVert(defaultPath), appendFrag(pickerPath)).use().setBlockBinding("Matrices", 0);

    // some materials: http://devernay.free.fr/cours/opengl/materials.html
    Shader defaultShader = getShader("default");
    defaultShader.use();
    setLightSources(defaultShader, pointLightPositions);
    defaultShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    defaultShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    defaultShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    defaultShader.setFloat("material.shininess", 0.05f);

    Shader instanceShader = getShader("defaultInstancing");
    instanceShader.use();
    setLightSources(instanceShader, pointLightPositions);
    instanceShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    instanceShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    instanceShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    instanceShader.setFloat("material.shininess", 0.25f);

    Shader meshShader = getShader("mesh");
    meshShader.use();
    setLightSources(meshShader, pointLightPositions);
    meshShader.setFloat3("material.ambient", 1.0f, 1.0f, 1.0f);
    meshShader.setFloat3("material.diffuse", 0.55f, 0.55f, 0.55f);
    meshShader.setFloat3("material.specular", 0.7f, 0.7f, 0.7f);
    meshShader.setFloat("material.shininess", 0.25f);
}

void ResourceManager::initTextures(){
    std::string texturesPath = "../assets/textures/";
    setTexture("wallDiffuse", texturesPath + "wall/diffuse.jpg");
    setTexture("groundDiffuse", texturesPath + "ground/diffuse.jpg");
    setTexture("smoke", texturesPath + "smoke/smoke.png", true);
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

void ResourceManager::setLightSources(Shader shader, glm::vec3 pointLightPositions[])
{
    // directional light
    shader.setFloat3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    shader.setFloat3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
    shader.setFloat3("dirLight.diffuse", 0.0f, 0.0f, 0.0f); // darkened
    shader.setFloat3("dirLight.specular", 0.1f, 0.1f, 0.1f);
    for (int i = 0; i < pointLightPositions->length(); i++){
        shader.setFloat3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
        shader.setFloat3("pointLights[" + std::to_string(i) + "].ambient", 255.0f/255.0f, 224.0f/255.0f, 166.0f/255.0f);
        shader.setFloat3("pointLights[" + std::to_string(i) + "].diffuse", 0.5f, 0.5f, 0.5f);
        shader.setFloat3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat( "pointLights[" + std::to_string(i) + "].constant", 1.0f);
        shader.setFloat( "pointLights[" + std::to_string(i) + "].linear", 0.09f);
        shader.setFloat( "pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
    }
}
// shader.setFloat3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
// shader.setFloat3("pointLights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
// shader.setFloat3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
// shader.setFloat3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
// shader.setFloat( "pointLights[" + std::to_string(i) + "].constant", 1.0f);
// shader.setFloat( "pointLights[" + std::to_string(i) + "].linear", 0.09f);
// shader.setFloat( "pointLights[" + std::to_string(i) + "].quadratic", 0.032f);

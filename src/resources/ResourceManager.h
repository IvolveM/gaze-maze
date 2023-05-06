#pragma once
#include <map>
#include <string>

#include "textures/Texture.h"
#include "shaders/Shader.h"

class ResourceManager{
    private:
        ResourceManager() = default;

        static std::map<std::string, Shader> shaders;
        static std::map<std::string, Texture> textures;

        static std::string appendVert(const std::string& path, bool instancing = false);
        static std::string appendFrag(const std::string& path, bool instancing = false);
        static void setLightSources(Shader shader, glm::vec3 pointLightPositions[]); 
    public:
        ResourceManager(ResourceManager &other) = delete;
        void operator=(const ResourceManager &) = delete;
        
        static Texture setTexture(std::string textureName, std::string texturePath, bool pixelated = false);
        static Shader addShader(std::string shaderName, std::string vertexPath, std::string fragmentPath);

        static Texture getTexture(std::string);
        static Shader getShader(std::string);
        static void initShaders(glm::vec3 pointLightPositions[]);
        static void initTextures();
};

class DuplicateResourceException : public std::exception {
    private:
        std::string name;
        
    public:
        DuplicateResourceException(std::string name){
            this->name = name;
        };

        virtual const char * what () const throw () {
            return strcat("There was already a resource with the name: ", name.c_str());
        }
};

class NoResourceFoundException : public std::exception {
    private:
        std::string name;
        
    public:
        NoResourceFoundException(std::string name){
            this->name = name;
        };

        virtual const char * what () const throw () {
            return strcat("There was already a shader with this name", name.c_str());
        }
};
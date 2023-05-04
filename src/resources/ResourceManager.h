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

    public:
        ResourceManager(ResourceManager &other) = delete;
        void operator=(const ResourceManager &) = delete;
        
        static Texture setTexture(std::string textureName, const char* texturePath);
        static Shader addShader(std::string shaderName, const char* vertexCode, const char* fragmentCode);

        static Texture getTexture(std::string);
        static Shader getShader(std::string);
};

class DuplicateResourceException : public std::exception {
    private:
        std::string name;
        
    public:
        DuplicateResourceException(std::string name){
            this->name = name;
        };

        const char * what () const throw () {
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

        const char * what () const throw () {
            return strcat("There was already a shader with this name", name.c_str());
        }
};
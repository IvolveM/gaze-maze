#pragma once
#include <glad/glad.h> 
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);

        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setFloat3(const std::string &name, float value1, float value2, float value3) const;
        void setFloat4(const std::string &name, float value1, float value2, float value3, float value4) const;
        void setMatrixFloat4(const std::string &name, glm::mat4 matrix) const;
};
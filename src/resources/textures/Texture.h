#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include "../../stb_image.h"

class Texture{
    private:
        unsigned int textureId;
    public:
        Texture(const char* texturePath);
        Texture(const Texture& texture){
            this->textureId = texture.textureId;
        }
        void bindTexture() const;
        unsigned int getId();
};
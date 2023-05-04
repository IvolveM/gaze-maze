#include "Texture.h"

Texture::Texture(std::string texturePath)
{
    int width, height, nrChannels;
    unsigned char *data;

    glGenTextures(1, &this->textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping/filtering options
    // GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }

    stbi_image_free(data); // free image
}

void Texture::bindTexture(int textureUnit) const
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

unsigned int Texture::getId()
{
    return textureId;
}

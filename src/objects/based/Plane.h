#pragma once

class Plane: public Mesh {
    private:
        unsigned int VAO;
        std::vector<float> vertices;
        std::vector<float> indices;
        
        Shader shader;
        Texture texture;
    public:
        Plane();
        void draw() override;
}
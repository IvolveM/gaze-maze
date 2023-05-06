#pragma once
#include <vector>
#include "Particle.h"

class ParticleGenerator{
    private:
        std::vector<Particle> particles{};
        int amount = 1;
        int lastUsedParticleIndex = 0;

        unsigned int VAO;
        unsigned int EBO;

        Shader shader;
        Texture texture;

        int getFirstDeadParticleIndex();
    public:
        ParticleGenerator(
            int amount,
            Texture texture
        );

        void update(float dt);
        void addParticles(glm::vec3 position);
        void draw();
};
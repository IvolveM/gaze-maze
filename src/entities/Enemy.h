#pragma once

#include <vector>
#include <utility>

#include "Entity.h"
#include "../core/Maze.h"
#include "./ParticleGenerator.h"

#include "../objects/model/Model.h"

#include "../objects/model/Animation.h"
#include "../objects/model/Animator.h"

class Enemy : public Entity {
    public:
        Enemy(
            float health, 
            std::pair<int,int> initialPos, 
            std::vector<std::vector<Maze::Object>> grid,
            glm::vec3 gridBlockSize
        );
        ~Enemy() = default;
        void update(float dt) override;
        void draw() override;

    private:
        glm::vec3 calculateNewTargetPos();
        void updateNewPosition(float dt);
        bool inBounds(std::pair<int,int> pos);

        float health;
        float speed = 2.0f;

        glm::vec3 movingDir;
        glm::vec3 targetPos;
        float distanceToTravel = 0.0f;

        std::vector<std::vector<Maze::Object>> grid;
        glm::vec3 gridBlockSize;
        std::pair<int,int> gridPosition;

        Model* model;
        Animation* animation;
        Animator* animator;
        ParticleGenerator particleGenerator;
};
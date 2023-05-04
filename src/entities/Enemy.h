#pragma once

#include <vector>
#include <utility>

#include "Entity.h"
#include "../core/Maze.h"

#include "../objects/based/Cube.h" //testing

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
        void move();
        glm::vec3 calculateNewTargetPos();
        void updateNewPosition(float dt);
        void updateNewDirection();
        bool inBounds(std::pair<int,int> pos);

        float health;
        
        float speed = 2.0f;
        glm::vec3 movingDir;
        glm::vec3 targetPos;

        std::vector<std::vector<Maze::Object>> grid;
        glm::vec3 gridBlockSize;
        std::pair<int,int> gridPosition;

        Cube* cube;
};
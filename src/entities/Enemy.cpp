#include "Enemy.h"

Enemy::Enemy(
    float health, 
    std::pair<int,int> initialPos, 
    std::vector<std::vector<Maze::Object>> grid,
    glm::vec3 gridBlockSize
) : 
    Entity{glm::vec3(initialPos.first, 0.0f, initialPos.second) * gridBlockSize},
    health{health},
    grid{grid},
    gridBlockSize{gridBlockSize},
    gridPosition{initialPos},
    movingDir{0.0f, 0.0f, 0.0f},
    particleGenerator{100, ResourceManager::getTexture("smoke")},
    targetPos{0.0f, 0.0f, 0.0f}
{
    this->cube = new Cube(this->position);
}

void Enemy::update(float dt) {
    // std::cout << "target: " << glm::to_string(targetPos) << std::endl;
    std::cout << "movingDir: " << glm::to_string(this->movingDir) << std::endl;
    // std::cout << "currpos: " << glm::to_string(this->position) << std::endl;

    // update particles
    glm::vec3 particlePosition = {this->position.x, this->position.y-0.45f, this->position.z};
    particleGenerator.addParticles(particlePosition);
    particleGenerator.update(dt);
    
    // target reached
    if (std::abs(glm::distance(this->targetPos, this->position)) <= gridBlockSize.x * 0.01) {
        // lock to target        
        this->gridPosition = std::pair<int,int>(targetPos.x, targetPos.z);
        this->cube->move(targetPos - position);
        this->position = targetPos;

        // find new target and set new moving direction
        this->targetPos = calculateNewTargetPos();
        updateNewDirection();
    }
    updateNewPosition(dt);
}

void Enemy::draw() {
    this->particleGenerator.draw();
    this->cube->draw();
}

glm::vec3 Enemy::calculateNewTargetPos() {
    std::vector<std::pair<int, int>> possibleDirs = {
        /*{0,0},*/ {1,0}, {0,1},
        {-1,0}, {0,-1}
    };

    std::vector<std::pair<int, int>> possiblePos = {};
    for (auto dir : possibleDirs) {
        std::pair<int,int> newPos = { this->gridPosition.second + dir.second, this->gridPosition.first + dir.first };
        if (inBounds(newPos) && grid[newPos.first][newPos.second] == Maze::Object::EMPTY) {
            possiblePos.push_back(newPos);
        }
    }
    std::cout << "possibles-----------" << std::endl;
    for (auto pos: possiblePos)
        std::cout << pos.first << " " << pos.second << std::endl;

    std::srand(time(NULL));
    std::pair<int,int> newGridPos = possiblePos[rand() % possiblePos.size()];
    return glm::vec3(newGridPos.second, 0.0f, newGridPos.first);
}

void Enemy::updateNewDirection() {
    this->movingDir = this->targetPos - this->position;
}

void Enemy::updateNewPosition(float dt) {
    glm::vec3 toIncrement = glm::vec3{movingDir.x, 0.0f, movingDir.z} * speed * dt;
    // make sure the max step size per move is one block length
    for (int i = 0; i < 3; i++) {
        if (toIncrement[i] > gridBlockSize[i])
            toIncrement[i] = gridBlockSize[i];
    }
    this->cube->move(toIncrement);
    this->position += toIncrement;
}

bool Enemy::inBounds(std::pair<int,int> pos) {
    return pos.first >= 0 && pos.first <= this->grid.size() 
        && pos.second >= 0 && pos.second <= this->grid[0].size();
}
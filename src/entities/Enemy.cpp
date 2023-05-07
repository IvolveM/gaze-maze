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
    model = new Model(
        "../assets/meshes/Amongus/scene.gltf", 
        glm::vec3{0.0f, -0.5f, 0.0f}, 
        glm::vec3{0.005f},
        ResourceManager::getShader("meshAnimated"),
        false
    );
    animation = new Animation("../assets/meshes/Amongus/scene.gltf", model);
    animator = new Animator(animation);
}

void Enemy::update(float dt) {
    // target reached
    if (this->distanceToTravel <= 0.0f) {
        // lock to target        
        this->gridPosition = std::pair<int,int>(targetPos.x, targetPos.z);
        this->model->move(targetPos - position);
        this->position = targetPos;

        // find new target and set new moving direction
        this->targetPos = calculateNewTargetPos();
        this->distanceToTravel = glm::distance(this->targetPos, this->position);
        this->movingDir = glm::normalize(this->targetPos - this->position);
    }
    updateNewPosition(dt);

    // update animation
    animator->UpdateAnimation(dt);
    // update particles
    glm::vec3 particlePosition = {this->position.x, this->position.y-0.45f, this->position.z};
    particleGenerator.addParticles(dt, particlePosition);
    particleGenerator.update(dt);
    
}

void Enemy::draw() {
    this->particleGenerator.draw();
    this->model->draw();

    Shader shader = ResourceManager::getShader("meshAnimated");
    shader.use();
    auto transforms = animator->GetFinalBoneMatrices();
    for (int i = 0; i < transforms.size(); ++i)
        shader.setMatrixFloat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
    model->draw();
}

glm::vec3 Enemy::calculateNewTargetPos() {
    std::vector<std::pair<int, int>> possibleDirs = {
        {1,0}, {0,1},
        {-1,0}, {0,-1}
    };
    std::vector<std::pair<int, int>> possiblePos = {};
    for (auto dir : possibleDirs) {
        std::pair<int,int> newPos = { this->gridPosition.second + dir.second, this->gridPosition.first + dir.first };
        if (inBounds(newPos) && grid[newPos.first][newPos.second] == Maze::Object::EMPTY) {
            possiblePos.push_back(newPos);
        }
    }
    std::srand(time(NULL));
    std::pair<int,int> newGridPos = possiblePos[rand() % possiblePos.size()];
    return glm::vec3(newGridPos.second, 0.0f, newGridPos.first);
}

void Enemy::updateNewPosition(float dt) {
    glm::vec3 toIncrement = glm::vec3{movingDir.x, 0.0f, movingDir.z} * speed * dt;
    // make sure the max step size per move is one block length
    for (int i = 0; i < 3; i++) {
        if (toIncrement[i] > gridBlockSize[i])
            toIncrement[i] = gridBlockSize[i];
    }
    this->model->move(toIncrement);
    this->position += toIncrement;
    this->distanceToTravel -= glm::length(toIncrement);
}

bool Enemy::inBounds(std::pair<int,int> pos) {
    return pos.first >= 0 && pos.first <= this->grid.size() 
        && pos.second >= 0 && pos.second <= this->grid[0].size();
}
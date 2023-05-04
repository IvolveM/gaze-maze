#include "Player.h"

#include <iostream>

// TODO: PLAYER SIZE VARIABLE

Player::Player() : Camera{glm::vec3{0.0f, 0.0f, 0.0f}},
                   movingDirection{glm::vec2{0.0f, 0.0f}},
                   isMoving{false},
                   collisioner{glm::vec3(0.3f, 0.3f, 0.3f), this->getPosition(), Collisioner::BoundingBoxType::SPHERE}
{
}

void Player::handleKeyInput(InputEvent event)
{
    float x = this->direction.x;
    float z = this->direction.z;
    glm::vec3 left = glm::cross(this->up, this->direction);
    switch (event)
    {
    case InputEvent::FORWARDS:
        movingDirection += glm::vec2{x, z};
        break;
    case InputEvent::BACKWARDS:
        movingDirection -= glm::vec2{x, z};
        break;
    case InputEvent::LEFT:
        movingDirection += glm::vec2{left.x, left.z};
        break;
    case InputEvent::RIGHT:
        movingDirection -= glm::vec2{left.x, left.z};
        break;
    case InputEvent::JUMP:
        if (isOnGround)
        {
            isOnGround = false;
            this->verticalSpeed += jumpSpeed;
        }
        break;
    }
}

void Player::update(float dt)
{
    if (movingDirection.x != 0.0f && movingDirection.y != 0.0f)
    {
        glm::vec2 directionNormalized = glm::normalize(movingDirection);
        incrementPosition(glm::vec3{directionNormalized.x, 0.0f, directionNormalized.y} * speed * dt);
        movingDirection = glm::vec2{0.0f, 0.0f};
    }
    handleVerticalMovement(dt);
    this->collisioner.setCenter(this->getPosition());
}

void Player::handleVerticalMovement(float dt)
{
    if (!isOnGround)
    {
        this->verticalAcceleration -= gravityAcceleration * dt;
        this->verticalSpeed += verticalAcceleration * dt;
    }

    glm::vec3 pos = getPosition();
    pos.y += verticalSpeed * dt;
    setPosition(pos);
    if (pos.y < 0)
    {
        pos.y = 0;
        setPosition(pos);

        verticalAcceleration = 0.0f;
        verticalSpeed = 0.0f;
        isOnGround = true;
    }
}

void Player::doCollisions(Mesh m)
{
    std::vector<Collisioner> collisions = m.isColliding(this->collisioner);
    glm::vec3 totalTranslationVector = glm::vec3(0.0f);
    int c = 1;
    for (auto col: collisions) {
        totalTranslationVector += resolveCollision(col);
        std::cout << "counter: " <<c++<<std::endl;
    }
    if (collisions.size() > 0)
        incrementPosition(totalTranslationVector);
}

glm::vec3 Player::resolveCollision(Collisioner c) {
    // glm::vec2 directionNormalized = glm::normalize(movingDirection);
    // std::cout << glm::to_string(this->collisioner.getVectorToTranslate(c, glm::vec3{directionNormalized.x, 0.0f, directionNormalized.y} * speed * dt, dt).second) << std::endl;
    // std::pair<glm::vec3, glm::vec3> ret = this->collisioner.getVectorToTranslate(c, glm::vec3{directionNormalized.x, 0.0f, directionNormalized.y} * speed * dt, dt);
    //     this->movingDirection = ret.second;

    //     this->setPosition(ret.first);
    auto vec = this->collisioner.getVectorToTranslate(c);
    std::cout << glm::to_string(vec)<<std::endl;
    this->movingDirection = glm::vec2{0.0f, 0.0f};
    return vec;
}

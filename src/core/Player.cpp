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

void Player::doCollisions(Mesh m, float dt)
{
    std::vector<Collisioner> collisions = m.isColliding(this->collisioner);
    this->movingDirection = glm::vec3(0.0f, 0.0f, 0.0f);
    if (collisions.size() == 1)
    {
        resolveCollision(collisions[0], dt);
    }
    else if (collisions.size() > 1)
    {
        resolveCollision(collisions[0], dt);
        resolveCollision(collisions[1], dt);
    }
    incrementPosition(glm::vec3{movingDirection.x, 0.0f, movingDirection.y});
}

void Player::resolveCollision(Collisioner c, float dt)
{
    glm::vec3 distanceNormal = this->collisioner.getDistanceNormal(c);
    // this->setPosition(distanceNormal);
    this->movingDirection += glm::normalize(glm::vec2(distanceNormal.x, distanceNormal.z)) * speed * dt;

    std::cout << "normal: " << glm::to_string(distanceNormal) << std::endl;
}

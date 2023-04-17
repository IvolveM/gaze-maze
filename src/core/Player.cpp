#include "Player.h"

#include <iostream>

// TODO: PLAYER SIZE VARIABLE

Player::Player(): 
    Camera{glm::vec3{0.0f, 0.0f, 0.0f}},
    movingDirection{glm::vec2{0.0f, 0.0f}},
    isMoving{false},
    collisioner{glm::vec3(0.2f, 0.2f, 0.2f), this->getPosition(), Collisioner::BoundingBoxType::SPHERE}
{
    
}

void Player::handleKeyInput(InputEvent event)
{
    float x = this->direction.x;
    float z = this->direction.z;
    glm::vec3 left = glm::cross(this->up, this->direction);
    switch (event){
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
            if (isOnGround){
                isOnGround = false;
                this->verticalSpeed += jumpSpeed;
            }
            break;
    }
}

void Player::update(float dt)
{
    if (movingDirection.x != 0.0f && movingDirection.y != 0.0f){
        glm::vec2 directionNormalized = glm::normalize(movingDirection);
        std::cout << "dir: " << glm::to_string(directionNormalized) << std::endl;
        incrementPosition(glm::vec3{directionNormalized.x, 0.0f, directionNormalized.y}*speed*dt);
        movingDirection = glm::vec2{0.0f, 0.0f};
    }
    handleVerticalMovement(dt);
    this->collisioner.setCenter(this->getPosition());
}

void Player::handleVerticalMovement(float dt){
    if (!isOnGround){
        this->verticalAcceleration -= gravityAcceleration*dt;
        this->verticalSpeed += verticalAcceleration*dt;
    }

    glm::vec3 pos = getPosition();
    pos.y += verticalSpeed*dt;
    setPosition(pos);
    if (pos.y < 0){
        pos.y = 0;
        setPosition(pos);
        
        verticalAcceleration = 0.0f;
        verticalSpeed = 0.0f;
        isOnGround = true;
    }
}

void Player::doCollisions(Mesh m) {
    Collisioner colliding = m.isColliding(this->collisioner);
    if (colliding.getType() != Collisioner::BoundingBoxType::NONE) {
        resolveCollision(colliding);
    }
}

void Player::resolveCollision(Collisioner c) {
    glm::vec3 collisionNormal = this->collisioner.getCollisionNormal(c);
    this->movingDirection += glm::vec2(collisionNormal.x, collisionNormal.z) * speed;
}

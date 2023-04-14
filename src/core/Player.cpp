#include "Player.h"

#include <iostream>

// TODO: PLAYER SIZE VARIABLE

Player::Player(): 
    Camera{glm::vec3{0.0f, 0.0f, 0.0f}},
    velocity{glm::vec3{0.0f, 0.0f, 0.0f}},
    acceleration{glm::vec3{0.0f, 0.0f, 0.0f}},
    isMoving{false},
    collisioner{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f)}
{
    
}

void Player::handleKeyInput(InputEvent event)
{
    float speed = 0.5f;
    switch (event){
        case InputEvent::FORWARDS:
            accelerate(this->direction * speed);
            break;
        case InputEvent::BACKWARDS:
            accelerate(this->direction * -speed);
            break;
        case InputEvent::LEFT:
            accelerate(glm::cross(this->up, this->direction) * speed);
            break;
        case InputEvent::RIGHT:
            accelerate(glm::cross(this->direction, this->up) * speed);
            break;
        case InputEvent::JUMP:
            accelerate(glm::vec3{0, speed, 0});
            break;
    }
}

void Player::accelerate(glm::vec3 direction)
{
    this->acceleration += glm::normalize(direction);
}

void Player::update()
{
    float decelerationSpeed = 20.0f;
    this->velocity += acceleration;
    this->acceleration /= (2.0f*decelerationSpeed);
    this->velocity /= (2.0f*decelerationSpeed);
    this->incrementPosition(this->velocity);

    this->collisioner.setCenter(this->getPosition());
}

void Player::doCollisions(Mesh m) {
    if (m.isColliding(this->collisioner)) {
        std::cout << "COLLISION BABY WHOOOHOOO" << std::endl;
    }
    else {
        std::cout << "NO FUCKING COLLISION" << std::endl;
    }
}
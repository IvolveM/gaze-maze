#include "Player.h"

Player::Player(): 
    Camera{glm::vec3{0.0f, 0.0f, 0.0f}},
    velocity{glm::vec3{0.0f, 0.0f, 0.0f}},
    acceleration{glm::vec3{0.0f, 0.0f, 0.0f}},
    isMoving{false}
{
    
}

void Player::handleKeyInput(InputEvent event)
{
    float speed = 0.5f;
    switch (event){
        case InputEvent::FORWARDS:
            accelerate(glm::vec3{0.0f, 0.0f, -speed});
            break;
        case InputEvent::BACKWARDS:
            accelerate(glm::vec3{0.0f, 0.0f, speed});
            break;
        case InputEvent::LEFT:
            accelerate(glm::vec3{-speed, 0.0f, 0.0f});
            break;
        case InputEvent::RIGHT:
            accelerate(glm::vec3{speed, 0.0f, 0.0f});
            break;
        case InputEvent::JUMP:
            accelerate(glm::vec3{0.0f, speed, 0.0f});
            break;
    }
}

void Player::accelerate(glm::vec3 direction)
{
    this->acceleration += direction;
}

void Player::update()
{
    float decelerationSpeed = 1.0f;
    this->velocity += acceleration;
    this->acceleration /= (2.0f*decelerationSpeed);
    this->velocity /= (2.0f*decelerationSpeed);
    this->incrementPosition(this->velocity);
}

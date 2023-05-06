#include "Collisioner.h"

Collisioner::Collisioner(glm::vec3 size, glm::vec3 center, BoundingBoxType boxType) :
    center{center},
    // for a sphere the size == diameter
    size{size},
    boxType{boxType}
{
    if (boxType == BoundingBoxType::CUBE) {
        this->minVec = center - (size * 0.5f);
        this->maxVec = center + (size * 0.5f);
    }
}

Collisioner::~Collisioner() {

}

void Collisioner::setCenter(glm::vec3 center) {
    this->center = center;

    // update minVec and maxVec for cube bounding box
    if (this->boxType == BoundingBoxType::CUBE) {
        this->minVec = center - (size * 0.5f);
        this->maxVec = center + (size * 0.5f);
    }
}

glm::vec3 Collisioner::getMinVec() {
    return this->minVec;
}

glm::vec3 Collisioner::getMaxVec() {
    return this->maxVec;
}

glm::vec3 Collisioner::getCenter() {
    return this->center;
}

bool Collisioner::isColliding(Collisioner col) {
    if (this->boxType == BoundingBoxType::CUBE && col.boxType == BoundingBoxType::CUBE) {
        return this->maxVec.x > col.minVec.x &&
                this->minVec.x < col.maxVec.x &&
                this->maxVec.y > col.minVec.y &&
                this->minVec.y < col.maxVec.y &&
                this->maxVec.z > col.minVec.z &&
                this->minVec.z < col.maxVec.z;
    }
    else if (this->boxType == BoundingBoxType::SPHERE && col.boxType == BoundingBoxType::SPHERE) {
        // TODO: SPHERE TO SPHERE COLLISION
        // const distance = Math.sqrt(
        //     (sphere.x - other.x) * (sphere.x - other.x) +
        //     (sphere.y - other.y) * (sphere.y - other.y) +
        //     (sphere.z - other.z) * (sphere.z - other.z)
        // );
        // return distance < sphere.radius + other.radius;
    }
    else {
        Collisioner cube, sphere;
        if (this->boxType == BoundingBoxType::SPHERE) {
            sphere = *this;
            cube = col;
        }
        else {
            sphere = col;
            cube = *this;
        }
        float sphereR = sphere.size.x * 0.5f;
        glm::vec3 closestPointClamped = glm::clamp(sphere.getCenter(), cube.getMinVec(), cube.getMaxVec());

        glm::vec3 dstVecSqrd = (closestPointClamped - sphere.getCenter()) * (closestPointClamped - sphere.getCenter());
        float dstSqrd = dstVecSqrd.x + dstVecSqrd.y + dstVecSqrd.z;

        return dstSqrd < sphereR * sphereR;
    }
}

glm::vec3 Collisioner::getVectorToTranslate(Collisioner col) {
    glm::vec3 closestPointClamped = glm::clamp(this->center, col.getMinVec(), col.getMaxVec());
    float closestDistance = glm::distance(this->center, closestPointClamped);
    glm::vec3 direction = closestPointClamped - this->center;
    // can't normalize 0-vector
    if (direction == glm::vec3(0.0f)){
        return glm::vec3(1.0f);
    }
    glm::vec3 directionNormalized = glm::normalize(closestPointClamped - this->center);
    float translationDistance = closestDistance - (this->size.x * 0.5f);

    glm::vec3 translationVector = directionNormalized * translationDistance;
    return translationVector;
}

Collisioner::BoundingBoxType Collisioner::getType() {
    return this->boxType;
}

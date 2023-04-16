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
        float xClampedDistance = std::max(cube.getMinVec().x, std::min(sphere.center.x, cube.getMaxVec().x));
        float yClampedDistance = std::max(cube.getMinVec().y, std::min(sphere.center.y, cube.getMaxVec().y));
        float zClampedDistance = std::max(cube.getMinVec().z, std::min(sphere.center.z, cube.getMaxVec().z));

        float distance = std::sqrt(
            (xClampedDistance - sphere.center.x) * (xClampedDistance - sphere.center.x) +
            (yClampedDistance - sphere.center.y) * (yClampedDistance - sphere.center.y) +
            (zClampedDistance - sphere.center.z) * (zClampedDistance - sphere.center.z)
        );
            // todo optimize sqrt
        return distance < (sphere.size.x * 0.5f);
    }
}

glm::vec3 Collisioner::getCenterToCenterDistance(Collisioner col) {
    glm::vec3 colCenter = col.getCenter();

    float x = this->center.x - colCenter.x;
    float y = this->center.y - colCenter.y;
    float z = this->center.z - colCenter.z;
    return glm::vec3(x, y, z);
}


glm::vec3 Collisioner::getCollisionNormal(Collisioner col) {
    if (!this->isColliding(col)) 
        return glm::vec3();

    else if (this->boxType == BoundingBoxType::CUBE && col.boxType == BoundingBoxType::CUBE) {
        // TODO
    }
    else if (this->boxType == BoundingBoxType::SPHERE && col.boxType == BoundingBoxType::SPHERE) {
        //TODO
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

        glm::vec3 deltaD = this->getCenterToCenterDistance(col);
        // glm::vec3 inset = glm::abs(deltaD) - (sphere.size * 0.5f);
        // if (deltaD.x < 0) inset.x *= -1;
        // if (deltaD.y < 0) inset.y *= -1; 
        // if (deltaD.z < 0) inset.z *= -1; 
        return deltaD;
    }
}

Collisioner::BoundingBoxType Collisioner::getType() {
    return this->boxType;
}

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
    float centerToCenterDistance = glm::distance(this->center, col.getCenter());
    glm::vec3 closestPointClamped = glm::clamp(this->center, col.getMinVec(), col.getMaxVec());
    float closestDistance = glm::distance(this->center, closestPointClamped);

    glm::vec3 direction = glm::normalize(closestPointClamped - this->center);
    float translationDistance = closestDistance - (this->size.x * 0.5f);

    glm::vec3 translationVector = direction * translationDistance;
    return translationVector;
    // glm::vec3 out_translation_vector = glm::vec3(0.0f);
    // glm::vec3 sphere_end_position = this->center + sphere_velocity * dt;
    // glm::vec3 closestPointClamped = glm::clamp(this->center, col.getMinVec(), col.getMaxVec());
    // glm::vec3 direction = glm::normalize(closestPointClamped - this->center);
    // float distance = glm::length(direction);
    // if (distance < (this->size.x*0.5f)) 
    //     out_translation_vector = direction * ((this->size.x*0.5f) - distance) / distance;

    // glm::vec3 new_sphere_position = this->center + out_translation_vector;
    // glm::vec3 closest_point = glm::clamp(new_sphere_position, col.getCenter() - glm::vec3(col.size / 2.0f), col.getCenter() + glm::vec3(col.size / 2.0f));
    // direction = new_sphere_position - closest_point;
    // distance = glm::length(direction);
    // if (distance < (this->size.x*0.5f)) {
    //     out_translation_vector = direction * ((this->size.x*0.5f) - distance) / distance;
    //     new_sphere_position += out_translation_vector;
    //     glm::vec3 normal = glm::normalize(out_translation_vector);
    //     glm::vec3 new_sphere_velocity = glm::reflect(sphere_velocity, normal);
    //     std::cout << "new post: " << glm::to_string(new_sphere_position) << " out " << glm::to_string(new_sphere_velocity) << std::endl;
    //     new_sphere_velocity -= glm::dot(sphere_velocity, normal) * normal;
    //     if (glm::any(glm::isnan(new_sphere_velocity))) {
    //         new_sphere_velocity = glm::vec3(0.0f);
    //     }
    //     return std::pair<glm::vec3, glm::vec3>(new_sphere_position, new_sphere_velocity);
    // }
}

Collisioner::BoundingBoxType Collisioner::getType() {
    return this->boxType;
}

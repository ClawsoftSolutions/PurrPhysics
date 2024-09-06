#include "PurrPhysics/Rigidbody.hpp"
#include "PurrPhysics/TransformData.hpp"

RigidBodyComponent::RigidBodyComponent(float mass, const glm::vec3& position, const glm::vec3& halfSize)
    : mass(mass), position(position), halfSize(halfSize), velocity(0.0f), force(0.0f) {
    transformData = TransformData();
}

void RigidBodyComponent::applyForce(const glm::vec3& force) {
    this->force += force;
}

void RigidBodyComponent::integrateForces(float deltaTime) {
    if (mass > 0.0f) {
        velocity += force * (deltaTime / mass);
    }
    clearForces();
}

void RigidBodyComponent::integrate(float deltaTime) {
    position += velocity * deltaTime;
    for (auto& point : points) {
        point.position += velocity * deltaTime;
    }
    transformData.setPosition(position);
}

void RigidBodyComponent::clearForces() {
    force = glm::vec3(0.0f);
}

float RigidBodyComponent::getMass() const {
    return mass;
}

const glm::vec3& RigidBodyComponent::getPosition() const {
    return position;
}

const glm::vec3& RigidBodyComponent::getHalfSize() const {
    return halfSize;
}

const glm::vec3& RigidBodyComponent::getVelocity() const {
    return velocity;
}

void RigidBodyComponent::setMass(float mass) {
    this->mass = mass;
}

void RigidBodyComponent::setPosition(const glm::vec3& position) {
    this->position = position;
    transformData.setPosition(position);
}

void RigidBodyComponent::setVelocity(const glm::vec3& velocity) {
    this->velocity = velocity;
}

void RigidBodyComponent::addPoint(const glm::vec3& position) {
    points.emplace_back(position);
}

const std::vector<Point>& RigidBodyComponent::getPoints() const {
    return points;
}

const TransformData& RigidBodyComponent::getTransformData() const {
    return transformData;
}
#include "PurrPhysics/RigidBody.hpp"

RigidBody::RigidBody(float mass, const glm::vec3& position, glm::vec3 halfSize)
    : mass(mass), position(position), velocity(0.0f), acceleration(0.0f), forceAccumulator(0.0f),
      orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), angularVelocity(0.0f), torqueAccumulator(0.0f), halfSize(halfSize) {
    inverseMass = (mass != 0.0f) ? 1.0f / mass : 0.0f;
}

void RigidBody::applyForce(const glm::vec3& force) {
    forceAccumulator += force;
}

void RigidBody::applyForceToCenter(const glm::vec3& force) {
    applyForce(force);
}

void RigidBody::applyTorque(const glm::vec3& torque) {
    torqueAccumulator += torque;
}

void RigidBody::integrateForces(float deltaTime) {
    if (inverseMass == 0.0f) return;
    acceleration = forceAccumulator * inverseMass;
    velocity += acceleration * deltaTime;

    glm::vec3 angularAcceleration = torqueAccumulator * inverseMass;
    angularVelocity += angularAcceleration * deltaTime;

    clearAccumulators();
}

void RigidBody::integrate(float deltaTime) {
    if (inverseMass == 0.0f) return;
    position += velocity * deltaTime;

    glm::quat deltaOrientation = glm::quat(0.0f, angularVelocity * deltaTime);
    orientation = glm::normalize(orientation + 0.5f * deltaOrientation * orientation);

    clearAccumulators();
}

void RigidBody::clearAccumulators() {
    forceAccumulator = glm::vec3(0.0f);
    torqueAccumulator = glm::vec3(0.0f);
}

glm::vec3 RigidBody::getMin() const { return position - halfSize; }
glm::vec3 RigidBody::getMax() const { return position + halfSize; }

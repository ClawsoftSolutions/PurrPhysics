#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class RigidBody {
public:
    float mass;
    float inverseMass;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 forceAccumulator;
    glm::quat orientation;
    glm::vec3 angularVelocity;
    glm::vec3 torqueAccumulator;
    glm::vec3 halfSize;

    RigidBody(float mass, const glm::vec3& position, glm::vec3 halfSize);
    
    void applyForce(const glm::vec3& force);
    void applyForceToCenter(const glm::vec3& force);
    void applyTorque(const glm::vec3& torque);

    void integrateForces(float deltaTime);
    void integrate(float deltaTime);
    void clearAccumulators();

    float getMass() { return mass; }
    
    glm::vec3 getMin() const;
    glm::vec3 getMax() const;

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getHalfSize() const { return halfSize; }
};

#endif

#include "PurrPhysics/Collision.hpp"
#include <algorithm>

CollisionManifold checkCollision(const RigidBody& a, const RigidBody& b) {
    CollisionManifold result;
    result.isColliding = true;

    glm::vec3 aMin = a.getMin();
    glm::vec3 aMax = a.getMax();
    glm::vec3 bMin = b.getMin();
    glm::vec3 bMax = b.getMax();
    for (int i = 0; i < 3; ++i) {
        if (aMax[i] < bMin[i] || aMin[i] > bMax[i]) {
            result.isColliding = false;
            return result;
        }
    }
    glm::vec3 penetration;
    for (int i = 0; i < 3; ++i) {
        float overlap1 = aMax[i] - bMin[i];
        float overlap2 = bMax[i] - aMin[i];
        penetration[i] = std::min(overlap1, overlap2);
    }

    result.penetrationDepth = penetration[0];
    result.normal = glm::vec3(1, 0, 0);
    for (int i = 1; i < 3; ++i) {
        if (penetration[i] < result.penetrationDepth) {
            result.penetrationDepth = penetration[i];
            result.normal = glm::vec3(0, 0, 0);
            result.normal[i] = 1;
        }
    }

    glm::vec3 relativePos = b.position - a.position;
    if (glm::dot(result.normal, relativePos) < 0) {
        result.normal = -result.normal;
    }

    return result;
}

void resolveCollision(RigidBody& a, RigidBody& b, const CollisionManifold& manifold) {
    if (!manifold.isColliding) return;

    float totalMass = a.mass + b.mass;
    float aRatio = a.mass / totalMass;
    float bRatio = b.mass / totalMass;

    glm::vec3 correction = manifold.normal * manifold.penetrationDepth;
    a.position -= correction * bRatio;
    b.position += correction * aRatio;

    glm::vec3 relativeVelocity = b.velocity - a.velocity;
    float velocityAlongNormal = glm::dot(relativeVelocity, manifold.normal);

    if (velocityAlongNormal > 0) return;

    float restitution = 0.5f;
    float impulseMagnitude = -(1 + restitution) * velocityAlongNormal / (aRatio + bRatio);

    glm::vec3 impulse = impulseMagnitude * manifold.normal;
    a.velocity -= impulse * aRatio;
    b.velocity += impulse * bRatio;
}

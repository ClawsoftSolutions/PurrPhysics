#include "PurrPhysics/Collision.hpp"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

CollisionManifold checkCollision(const RigidBodyComponent& a, const RigidBodyComponent& b) {
    CollisionManifold result;
    result.isColliding = true;

    glm::vec3 aMin = a.getPosition() - a.getHalfSize();
    glm::vec3 aMax = a.getPosition() + a.getHalfSize();
    glm::vec3 bMin = b.getPosition() - b.getHalfSize();
    glm::vec3 bMax = b.getPosition() + b.getHalfSize();

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

    glm::vec3 relativePos = b.getPosition() - a.getPosition();
    if (glm::dot(result.normal, relativePos) < 0) {
        result.normal = -result.normal;
    }

    return result;
}

CollisionManifold checkGroundCollision(const RigidBodyComponent& body, float GROUND_Y) {
    CollisionManifold result;
    result.isColliding = false;

    glm::vec3 position = body.getPosition();
    glm::vec3 halfSize = body.getHalfSize();

    float bottomY = position.y + halfSize.y;
    if (bottomY >= GROUND_Y) {
        result.isColliding = true;
        result.normal = glm::vec3(0, -1, 0);
        result.penetrationDepth = bottomY - GROUND_Y;
    }

    return result;
}

void resolveCollision(RigidBodyComponent& a, RigidBodyComponent& b, const CollisionManifold& manifold) {
    if (!manifold.isColliding) return;

    float totalMass = a.getMass() + b.getMass();
    float aRatio = a.getMass() / totalMass;
    float bRatio = b.getMass() / totalMass;

    glm::vec3 correction = manifold.normal * manifold.penetrationDepth;
    a.setPosition(a.getPosition() - correction * bRatio);
    b.setPosition(b.getPosition() + correction * aRatio);

    glm::vec3 relativeVelocity = b.getVelocity() - a.getVelocity();
    float velocityAlongNormal = glm::dot(relativeVelocity, manifold.normal);

    if (velocityAlongNormal > 0) return;

    float restitution = 0.5f;
    float impulseMagnitude = -(1 + restitution) * velocityAlongNormal / (aRatio + bRatio);

    glm::vec3 impulse = impulseMagnitude * manifold.normal;
    a.setVelocity(a.getVelocity() - impulse * aRatio);
    b.setVelocity(b.getVelocity() + impulse * bRatio);
}

void resolveGroundCollision(RigidBodyComponent& body, const CollisionManifold& manifold) {
    if (!manifold.isColliding) return;

    glm::vec3 correction = manifold.normal * manifold.penetrationDepth;
    body.setPosition(body.getPosition() - correction);
    glm::vec3 velocity = body.getVelocity();
    velocity.y = -velocity.y * 0.5f;
    body.setVelocity(velocity);
}
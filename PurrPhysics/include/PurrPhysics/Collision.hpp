#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "RigidBody.hpp"

struct CollisionManifold {
    bool isColliding;
    glm::vec3 normal;
    float penetrationDepth;
};

CollisionManifold checkCollision(const RigidBodyComponent& a, const RigidBodyComponent& b);
void resolveCollision(RigidBodyComponent& a, RigidBodyComponent& b, const CollisionManifold& manifold);

void resolveGroundCollision(RigidBodyComponent& body, const CollisionManifold& manifold);
CollisionManifold checkGroundCollision(const RigidBodyComponent& body, float GROUND_Y);

#endif

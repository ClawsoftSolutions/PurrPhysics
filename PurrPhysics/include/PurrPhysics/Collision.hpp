#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "RigidBody.hpp"

struct CollisionManifold {
    bool isColliding;
    glm::vec3 normal;
    float penetrationDepth;
};

CollisionManifold checkCollision(const RigidBody& a, const RigidBody& b);
void resolveCollision(RigidBody& a, RigidBody& b, const CollisionManifold& manifold);

#endif

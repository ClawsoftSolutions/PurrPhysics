#ifndef PURRPHYSICS_HPP
#define PURRPHYSICS_HPP

#include "PurrPhysics/Collision.hpp"
#include "PurrPhysics/Rigidbody.hpp"
#include "PurrPhysics/Force.hpp"
#include "PurrPhysics/Forces/GravityForce.hpp"
#include "TransformData.hpp"
#include <vector>
#include <glm/glm.hpp>
struct TransformData;

class purrPhysics {
public:
    purrPhysics();

    void addRigidBody(RigidBodyComponent& body);
    void removeRigidBody(RigidBodyComponent& body);
    void updatePhysics(float deltaTime);

private:
    std::vector<RigidBodyComponent*> rigidBodies;
};

#endif // PURRPHYSICS_HPP

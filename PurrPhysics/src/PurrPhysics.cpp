#include "PurrPhysics/PurrPhysics.hpp"


#include "PurrPhysics/TransformData.hpp"
#include <algorithm>


void purrPhysics::addRigidBody(RigidBodyComponent& body) {
    rigidBodies.push_back(&body);
}

void purrPhysics::removeRigidBody(RigidBodyComponent& body) {
    auto it = std::find(rigidBodies.begin(), rigidBodies.end(), &body);
    if (it != rigidBodies.end()) {
        rigidBodies.erase(it);
    }
}

void purrPhysics::updatePhysics(float deltaTime) {
    for (auto body : rigidBodies) {
        body->integrateForces(deltaTime);
        body->integrate(deltaTime);
    }

}
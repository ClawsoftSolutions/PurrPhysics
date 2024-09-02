#include "PurrPhysics/PurrPhysics.hpp"
#include "PurrPhysics/Collision.hpp"

void applyForces(std::vector<RigidBody>& bodies, const std::vector<const Force*>& forces) {
    for (RigidBody& body : bodies) {
        for (const Force* force : forces) {
            force->apply(body);
        }
    }
}

void updatePhysics(std::vector<RigidBody>& bodies, const std::vector<const Force*>& forces, float deltaTime) {
    applyForces(bodies, forces);

    for (RigidBody& body : bodies) {
        body.integrateForces(deltaTime);
        body.integrate(deltaTime);
    
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                CollisionManifold manifold = checkCollision(bodies[i], bodies[j]);
                resolveCollision(bodies[i], bodies[j], manifold);
            }
        }
        for (RigidBody& body : bodies) {
            body.clearAccumulators();
        }
    }
}
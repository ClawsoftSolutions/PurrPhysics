#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include "RigidBody.hpp"
#include "Force.hpp"
#include "./Forces/GravityForce.hpp"
#include <vector>

void applyForces(std::vector<RigidBody>& bodies, const std::vector<const Force*>& forces);
void updatePhysics(std::vector<RigidBody>& bodies, const std::vector<const Force*>& forces, float deltaTime);

#endif

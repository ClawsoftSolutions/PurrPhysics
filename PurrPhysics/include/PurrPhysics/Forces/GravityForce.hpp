#ifndef GRAVITY_FORCE_HPP
#define GRAVITY_FORCE_HPP

#include "../Force.hpp"
#include "../RigidBody.hpp"
#include <glm/vec3.hpp>

class GravityForce : public Force {
public:
    explicit GravityForce(const glm::vec3& gravity) : gravity(gravity) {}

    void apply(RigidBody& body) const override {
        glm::vec3 force = gravity * body.getMass();
        body.applyForce(force);
    }

private:
    glm::vec3 gravity;
};

#endif // GRAVITY_FORCE_HPP

#ifndef GRAVITY_FORCE_HPP
#define GRAVITY_FORCE_HPP

#include "../Force.hpp"
#include <glm/vec3.hpp>

template<typename T>
class GravityForce : public Force<T> {
public:
    explicit GravityForce(const glm::vec3& gravity) : gravity(gravity) {}

    void apply(T& body) const override;

private:
    glm::vec3 gravity;
};

template<typename T>
void GravityForce<T>::apply(T& body) const {
    body.applyForce(gravity * body.getMass());
}

#endif // GRAVITY_FORCE_HPP

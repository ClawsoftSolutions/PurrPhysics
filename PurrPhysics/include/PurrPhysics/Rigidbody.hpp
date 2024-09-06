#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include "TransformData.hpp"

struct Point {
    glm::vec3 position;

    Point(const glm::vec3& pos) : position(pos) {}
};

class RigidBodyComponent {
public:
    RigidBodyComponent(float mass, const glm::vec3& position, const glm::vec3& halfSize);

    void applyForce(const glm::vec3& force);
    void integrateForces(float deltaTime);
    void integrate(float deltaTime);
    void clearForces();

    float getMass() const;
    const glm::vec3& getPosition() const;
    const glm::vec3& getHalfSize() const;
    const glm::vec3& getVelocity() const;

    void setMass(float mass);
    void setPosition(const glm::vec3& position);
    void setVelocity(const glm::vec3& velocity);

    void addPoint(const glm::vec3& position);
    const std::vector<Point>& getPoints() const;

    const TransformData& getTransformData() const;
    void setTransformData(const TransformData& transformData);

private:
    float mass;
    glm::vec3 position;
    glm::vec3 halfSize;
    glm::vec3 velocity;
    glm::vec3 force;
    std::vector<Point> points;
    TransformData transformData;
};

#endif // RIGIDBODYCOMPONENT_HPP

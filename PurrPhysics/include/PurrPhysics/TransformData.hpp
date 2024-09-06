#ifndef TRANSFORMDATA_HPP
#define TRANSFORMDATA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformData {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    TransformData()
        : position(glm::vec3(0.0f)), 
          rotation(glm::quat()), 
          scale(glm::vec3(1.0f)) {}

    template <typename Transform>
    TransformData(const Transform& transform)
        : position(transform.getPosition()), 
          rotation(transform.getRotation()), 
          scale(transform.getScale()) {}

    void setPosition(const glm::vec3& newPosition) { position = newPosition; }
    void setRotation(const glm::quat& newRotation) { rotation = newRotation; }
    void setScale(const glm::vec3& newScale) { scale = newScale; }

    glm::vec3 getPosition() const { return position; }
    glm::quat getRotation() const { return rotation; }
    glm::vec3 getScale() const { return scale; }
    
};

#endif // TRANSFORMDATA_HPP

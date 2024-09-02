#ifndef FORCE_HPP
#define FORCE_HPP

#include "RigidBody.hpp"

class Force {
public:
    virtual ~Force() {}
    virtual void apply(RigidBody& body) const = 0;
};


#endif

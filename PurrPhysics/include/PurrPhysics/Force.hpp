#ifndef FORCE_HPP
#define FORCE_HPP

template<typename T>
class Force {
public:
    virtual void apply(T& body) const = 0;
    virtual ~Force() = default;
};

#endif // FORCE_HPP

#ifndef PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#define PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#include "RigidBody.hpp"


class MarioRigidBody : public spic::RigidBody {
public:

    MarioRigidBody();
    void AddForce(const Point& forceDirection) override;

private:
    Point _velocity;
    const float _friction = 0.016;
    const float _maxHorizontalSpeed = 2;
};


#endif //PLATFORMER_ENGINE_MARIORIGIDBODY_HPP

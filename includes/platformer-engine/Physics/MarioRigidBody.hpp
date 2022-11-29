#ifndef PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#define PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#include "RigidBody.hpp"


class MarioRigidBody : public spic::RigidBody {
public:

    MarioRigidBody();
    void AddForce(const Point& forceDirection) override;

private:
    float _horizontalSpeed{0};
    float _verticalSpeed{0};
    int _jumpTimer{0};
    Point _velocity;
    const float MAX_VERTICAL_SPEED = 8;
    const float JUMP_SPEED = -4;
    const float MARIO_ACCELERATION = 0.25f;
    const float MARIO_WALK_SPEED = 2;
    const int MARIO_JUMP_TIMER = 8;
};


#endif //PLATFORMER_ENGINE_MARIORIGIDBODY_HPP

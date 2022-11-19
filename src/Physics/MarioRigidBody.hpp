#ifndef PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#define PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#include "RigidBody.hpp"


class MarioRigidBody : public spic::RigidBody {
public:
    void AddForce(const Point& forceDirection) override;
    float GetHorizontalSpeed() const;
    float GetVerticalSpeed() const;

private:
    float _horizontal_speed = 0;
    float _vertical_speed = 0;
    int _jump_timer = 0;
    const float _MAX_VERTICAL_SPEED = 8;
    const float _JUMP_SPEED = -4;
    const float _MARIO_ACCELERATION = 0.25f;
    const float _MARIO_WALK_SPEED = 2;
    const int _MARIO_JUMP_TIMER = 8;
    const float _GRAVITY = 0.25F;



};


#endif //PLATFORMER_ENGINE_MARIORIGIDBODY_HPP

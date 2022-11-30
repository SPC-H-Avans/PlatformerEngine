#ifndef PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP
#define PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP
#include "RigidBody.hpp"


class PlayerRigidBody : public spic::RigidBody {
public:

    PlayerRigidBody();
    void AddForce(const Point& forceDirection) override;

    float XVelocity() { return _horizontalSpeed; }

    float YVelocity() { return _verticalSpeed; }

private:
    float _horizontalSpeed{0};
    float _verticalSpeed{0};
    int _jumpTimer{0};
    const float PLAYER_MAX_VERTICAL_SPEED = 8;
    const float PLAYER_JUMP_SPEED = -4;
    const float PLAYER_ACCELERATION = 0.25f;
    const float PLAYER_WALK_SPEED = 2;
    const int PLAYER_JUMP_TIMER = 8;
};


#endif //PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP

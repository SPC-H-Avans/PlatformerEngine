#ifndef PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#define PLATFORMER_ENGINE_MARIORIGIDBODY_HPP
#include "RigidBody.hpp"


class MarioRigidBody : public spic::RigidBody {
public: //todo make private with public getters and setters
    float horizontal_speed = 0;
    float vertical_speed = 0;
    int jump_timer = 0;
    const float MAX_VERTICAL_SPEED = 8;
    const float JUMP_SPEED = -4;
    const float MARIO_ACCELERATION = 0.25f;
    const float MARIO_WALK_SPEED = 2;
    const int MARIO_JUMP_TIMER = 8;
    float GetGravity();

};


#endif //PLATFORMER_ENGINE_MARIORIGIDBODY_HPP

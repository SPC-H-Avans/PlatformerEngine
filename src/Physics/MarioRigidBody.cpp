#include "MarioRigidBody.hpp"
#include "Point.hpp"
#include <algorithm>

void MarioRigidBody::AddForce(const spic::Point& forceDirection) {
    //if(forceDirection.x == 0 && forceDirection.y == 0) return; // No force from any side

    if(forceDirection.x < 0) { // Move left
        _horizontal_speed = std::max(_horizontal_speed - _MARIO_ACCELERATION, -_MARIO_WALK_SPEED);
    }
    else if(forceDirection.x > 0) { // Move right
        _horizontal_speed = std::min(_horizontal_speed + _MARIO_ACCELERATION, _MARIO_WALK_SPEED);
    }

    if(_horizontal_speed < 0) {
        _horizontal_speed -= _MARIO_ACCELERATION;
    }
    else if(_horizontal_speed > 0) {
        _horizontal_speed += _MARIO_ACCELERATION;
    }

    if(forceDirection.y > 0) { // Jump
        //todo: Make sure Mario can only jump when on an object
        _vertical_speed = _JUMP_SPEED;
        _jump_timer = _MARIO_JUMP_TIMER;
    }
    else if(_jump_timer > 0) { // High jump
        _vertical_speed = _JUMP_SPEED;
        _jump_timer -= 1;
    }
    else {
        _vertical_speed = std::min(_GRAVITY + _vertical_speed, _MAX_VERTICAL_SPEED);
    }

    _vertical_speed += _GRAVITY;
}

float MarioRigidBody::GetHorizontalSpeed() const {
    return _horizontal_speed;
}

float MarioRigidBody::GetVerticalSpeed() const {
    return _vertical_speed;
}



#include "Physics/MarioRigidBody.hpp"
#include "Point.hpp"
#include <algorithm>
#include "Physics/Collision.hpp"

void MarioRigidBody::AddForce(const spic::Point& forceDirection) {
    //if(forceDirection.x == 0 && forceDirection.y == 0) return; // No force from any side

    if(forceDirection.x < 0 && CanMoveTo(CollisionPoint::Left)) { // Move left
        _horizontal_speed = std::max(_horizontal_speed - _MARIO_ACCELERATION, -_MARIO_WALK_SPEED);
    }
    else if(forceDirection.x > 0 && CanMoveTo(CollisionPoint::Right)) { // Move right
        _horizontal_speed = std::min(_horizontal_speed + _MARIO_ACCELERATION, _MARIO_WALK_SPEED);
    }

//    if(_horizontal_speed < 0 && CanMoveTo(CollisionPoint::Left)) {
//        _horizontal_speed -= _MARIO_ACCELERATION;
//    }
//    else if(_horizontal_speed > 0 && CanMoveTo(CollisionPoint::Right)) {
//        _horizontal_speed += _MARIO_ACCELERATION;
//    }

    if(forceDirection.y > 0
        && CanMoveTo(CollisionPoint::Top)
        && !CanMoveTo(CollisionPoint::Bottom)) { // Jump when on top of an object
        _vertical_speed = _JUMP_SPEED;
        _jump_timer = _MARIO_JUMP_TIMER;
    }
    else if(_jump_timer > 0 && CanMoveTo(CollisionPoint::Top)) { // High jump
        _vertical_speed = _JUMP_SPEED;
        _jump_timer -= 1;
    }
    else {
        _vertical_speed = std::min(_GRAVITY + _vertical_speed, _MAX_VERTICAL_SPEED);
    }

    _vertical_speed += _GRAVITY;
    if(_vertical_speed > 0 && !CanMoveTo(CollisionPoint::Bottom)) {
        // Mario is standing on top of an object, so shouldn't fall down
        _vertical_speed = 0;
    }
}

float MarioRigidBody::GetHorizontalSpeed() const {
    return _horizontal_speed;
}

float MarioRigidBody::GetVerticalSpeed() const {
    return _vertical_speed;
}



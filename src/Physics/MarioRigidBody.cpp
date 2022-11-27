#include "Physics/MarioRigidBody.hpp"
#include "Point.hpp"
#include <algorithm>
#include "Physics/Collision.hpp"
#include "GameObject.hpp"

void MarioRigidBody::AddForce(const spic::Point& forceDirection) {

    if(forceDirection.x < 0 && CanMoveTo(CollisionPoint::Left)) { // Move left
        _horizontal_speed = std::max(_horizontal_speed - _MARIO_ACCELERATION, -_MARIO_WALK_SPEED);
    }
    else if(forceDirection.x > 0 && CanMoveTo(CollisionPoint::Right)) { // Move right
        _horizontal_speed = std::min(_horizontal_speed + _MARIO_ACCELERATION, _MARIO_WALK_SPEED);
    }

    if(_horizontal_speed < 0 && forceDirection.x >= 0) { // Slow down mario when gliding to the left
        _horizontal_speed += _MARIO_ACCELERATION / 7;
    }
    else if(_horizontal_speed > 0 && forceDirection.x <= 0) { // Slow down mario when gliding to the right
        _horizontal_speed -= _MARIO_ACCELERATION / 7;
    }

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
        _vertical_speed = 0;
    }

    if(_horizontal_speed > 0 && !CanMoveTo(CollisionPoint::Right)) {
        _horizontal_speed = 0;
    }

    if(_horizontal_speed < 0 && !CanMoveTo(CollisionPoint::Left)) {
        _horizontal_speed = 0;
    }

    if(_vertical_speed < 0 && !CanMoveTo(CollisionPoint::Top)) {
        _vertical_speed = 0;
    }

    std::shared_ptr<GameObject> gob { GetGameObject().lock() };
    if (gob) {
        auto transform = gob->GetTransform();
        transform.position.x += _horizontal_speed;
        transform.position.y += _vertical_speed;
        gob->SetTransform(transform);
    } else { // GameObject was already deleted
        gob.reset();
    }
}

float MarioRigidBody::GetHorizontalSpeed() const {
    return _horizontal_speed;
}

float MarioRigidBody::GetVerticalSpeed() const {
    return _vertical_speed;
}



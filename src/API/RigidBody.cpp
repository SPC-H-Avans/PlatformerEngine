#include "RigidBody.hpp"
#include "Exceptions/IllegalCollisionBehaviourException.hpp"
#include "GameObject.hpp"

void spic::RigidBody::AddForce(const spic::Point &force) {
    auto x_acceleration = force.x / _mass;
    _velocity.x += x_acceleration;

    if (_velocity.x > 0) {
        _velocity.x -= _friction;
        _velocity.x = std::min(static_cast<float>(_velocity.x), _maxHorizontalSpeed);
    } else if (_velocity.x < 0) {
        _velocity.x += _friction;
        _velocity.x = std::max(static_cast<float>(_velocity.x), -_maxHorizontalSpeed);
    }

    if (force.y > 0
        && !CanMoveTo(CollisionPoint::Bottom)) { // Jump when on top of an object
        auto y_acceleration = force.y / _mass;
        _velocity.y -= y_acceleration;
    }

    _velocity.y += _gravityScale * _mass;

    if (_velocity.y > 0 && !CanMoveTo(CollisionPoint::Bottom)) { _velocity.y = 0; }
    if (_velocity.x > 0 && !CanMoveTo(CollisionPoint::Right)) { _velocity.x = 0; }
    if (_velocity.x < 0 && !CanMoveTo(CollisionPoint::Left)) { _velocity.x = 0; }
    if (_velocity.y < 0 && !CanMoveTo(CollisionPoint::Top)) { _velocity.y = 0; }

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        transform.position.x += _velocity.x;
        transform.position.y += _velocity.y;
        gameObject->SetTransform(transform);
    } else { // GameObject was already deleted
        gameObject.reset();
    }
}

bool spic::RigidBody::CanMoveTo(CollisionPoint point) {
    if(_moveRestrictions.contains(point)) {
        return _moveRestrictions[point] == 0;
    }
    return true;
}

void spic::RigidBody::AllowMoveTo(CollisionPoint point) {
    if(_moveRestrictions[point] <= 0) { // Numbers below zero are illegal
        throw IllegalCollisionBehaviourException(_bodyType, point);
    }
    _moveRestrictions[point] -= 1;
}

void spic::RigidBody::DenyMoveTo(CollisionPoint point) {
    _moveRestrictions[point] += 1;
}

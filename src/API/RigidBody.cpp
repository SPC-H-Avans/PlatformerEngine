#include "RigidBody.hpp"
#include "Exceptions/IllegalCollisionBehaviourException.hpp"
#include "GameObject.hpp"

void spic::RigidBody::AddForce(const spic::Point &force) {

    // Normalize heading using the force. Inverse force.y because a force up means a negative y-location
    SetHeading(Point::PointNormalize({force.x, -1 * force.y}));

    auto acceleration = force / _mass;
    _velocity.x += acceleration.x;

    _velocity.x = std::min(_velocity.x, _maxSpeed.x);
    _velocity.x += -1 * _friction * _heading.x;

//    if (_velocity.x > 0) {
//        _velocity.x -= _friction;
//        _velocity.x = std::min(_velocity.x, _maxSpeed.x);
//    } else if (_velocity.x < 0) {
//        _velocity.x += _friction;
//        _velocity.x = std::max(_velocity.x, -_maxSpeed.x);
//    }

    if (force.y > 0 &&
        (!CanMoveTo(CollisionPoint::Bottom)
         || _gravityScale == 0)) { // Jump when on top of an object or if object has no gravity

        _velocity.y += acceleration.y;
    }

    _velocity.y -= _gravityScale * _mass;
    if(_velocity.y < 0) {
        _velocity.y *= -1; // Ensure that y-velocity is always a positive number
        _heading.y *= -1; // Invert heading direction
    }

    if (_heading.y > 0 && !CanMoveTo(CollisionPoint::Bottom)) { _velocity.y = 0; }
    if (_heading.x > 0 && !CanMoveTo(CollisionPoint::Right)) { _velocity.x = 0; }
    if (_heading.x < 0 && !CanMoveTo(CollisionPoint::Left)) { _velocity.x = 0; }
    if (_heading.y < 0 && !CanMoveTo(CollisionPoint::Top)) { _velocity.y = 0; }

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        transform.position.x += _velocity.x * _heading.x;
        transform.position.y += _velocity.y * _heading.y;
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

RigidBody::RigidBody(float friction)
        : _bodyType(BodyType::staticBody), _mass(0), _gravityScale(0), _friction(friction) {


}

void RigidBody::SetHeading(Point new_heading)
{
    assert( (new_heading.LengthSq() - 1.0) < 0.00001);

    _heading = new_heading;

    //the side vector must always be perpendicular to the heading
//    _side = m_vHeading.Perp();
}

auto RigidBody::GetMaxSpeed() const -> Point {
    return _maxSpeed;
}

auto RigidBody::GetVelocity() const -> Point {
    return _velocity;
}

auto RigidBody::GetHeading() const -> Point {
    return _heading;
}

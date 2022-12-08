#include "RigidBody.hpp"
#include "Exceptions/IllegalCollisionBehaviourException.hpp"
#include "GameObject.hpp"
#include "BoxCollider.hpp"

void spic::RigidBody::AddForce(const spic::Point &force) {

    auto x_acceleration = force.x / _mass;
    _velocity.x += x_acceleration;

    if (_gravityScale == 0 || (force.y < 0 &&
                               !CanMoveTo(CollisionPoint::Bottom))) { // Jump when on top of an object or if object has no gravity
        auto y_acceleration = force.y / _mass;
        _velocity.y += y_acceleration;
        if(_velocity.y < -1 * _maxSpeed.y) {_velocity.y = -1*_maxSpeed.y;}
    }

    if (_velocity.y > 0 && !CanMoveTo(CollisionPoint::Bottom)) { _velocity.y = 0; }
    if (_velocity.x > 0 && !CanMoveTo(CollisionPoint::Right)) { _velocity.x = 0; }
    if (_velocity.x < 0 && !CanMoveTo(CollisionPoint::Left)) { _velocity.x = 0; }
    if (_velocity.y < 0 && !CanMoveTo(CollisionPoint::Top)) { _velocity.y = 0; }

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        auto oldPos = transform.position;
        transform.position += _velocity;
        gameObject->SetTransform(transform);
    } else { // GameObject was already deleted
        gameObject.reset();
    }

    //update the heading if the vehicle has a non zero velocity
    if (_velocity.LengthSq() > 0.00000001)
    {
        _heading = Point::PointNormalize(_velocity);

        //m_vSide = m_vHeading.Perp();
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

void RigidBody::SetVelocity(Point velocity) {
    _velocity = velocity;
}

auto RigidBody::GetGravityScale() const -> float {
    return _gravityScale;
}

auto RigidBody::GetMass() const -> float {
    return _mass;
}

auto RigidBody::GetFriction() const -> float {
    return _friction;
}


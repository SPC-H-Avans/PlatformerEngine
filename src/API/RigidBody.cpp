#include "RigidBody.hpp"
#include "Exceptions/IllegalCollisionBehaviourException.hpp"
#include "GameObject.hpp"
#include "BoxCollider.hpp"

void spic::RigidBody::AddForce(const spic::Point &force, double speedMultiplier) {
    if (_mass == 0) return;
    auto x_acceleration = force.x / _mass;
    _velocity.x += x_acceleration;

    if (_velocity.x > 0) {
        _velocity.x = std::min(_velocity.x, _maxSpeed.x);
    } else if (_velocity.x < 0) {
        _velocity.x = std::max(_velocity.x, -_maxSpeed.x);
    }

    auto y_acceleration = force.y / _mass;
    _velocity.y += y_acceleration;
    if (_velocity.y < -1 * _maxSpeed.y) { _velocity.y = -1 * _maxSpeed.y; }

    _velocity = _velocity * speedMultiplier;
}

auto spic::RigidBody::CanMoveTo(CollisionPoint point) -> bool {
    if (_moveRestrictions.contains(point)) {
        return _moveRestrictions[point] == 0;
    }
    return true;
}

void spic::RigidBody::AllowMoveTo(CollisionPoint point) {
    if (_moveRestrictions[point] <= 0) { // Numbers below zero are illegal
        return;
    }
    _moveRestrictions[point] -= 1;
}

void spic::RigidBody::DenyMoveTo(CollisionPoint point) {
    _moveRestrictions[point] += 1;
}

RigidBody::RigidBody(const PhysicsTemplate &physicsTemplate)
        : _bodyType(BodyType::staticBody), _mass(physicsTemplate.GetMass()),
          _gravityScale(physicsTemplate.GetGravityScale()), _friction(physicsTemplate.GetFriction()) {
    _maxSpeed = physicsTemplate.GetMaxSpeed();
}

void RigidBody::SetHeading() {
    //update the heading if the vehicle has a non zero velocity
    if (_velocity.LengthSq() > 0.00000001) {
        _heading = Point::PointNormalize(_velocity);
    }
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

void RigidBody::SetMass(float mass) {
    _mass = mass;
}

void RigidBody::SetGravityScale(float gravityScale) {
    _gravityScale = gravityScale;
}

RigidBody::RigidBody() : RigidBody(PhysicsTemplate()) {

}

void RigidBody::SetMaxSpeed(Point maxSpeed) {
    _maxSpeed = maxSpeed;
}

void RigidBody::SetFriction(float friction) {
    _friction = friction;
}


BOOST_CLASS_EXPORT_IMPLEMENT(RigidBody);

#include "RigidBody.hpp"

void spic::RigidBody::AddForce(const spic::Point &forceDirection) {

}

bool spic::RigidBody::CanMoveTo(CollisionPoint point) {
    if(_canMoveTo.count(point)) {
        return _canMoveTo[point];
    }
    return true;
}

void spic::RigidBody::AllowMoveTo(CollisionPoint point) {
    _canMoveTo[point] = true;
}

void spic::RigidBody::DenyMoveTo(CollisionPoint point) {
    _canMoveTo[point] = false;
}
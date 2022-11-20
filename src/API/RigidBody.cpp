#include "RigidBody.hpp"
#include "Exceptions/IllegalCollisionBehaviourException.hpp"

void spic::RigidBody::AddForce(const spic::Point &forceDirection) {

}

bool spic::RigidBody::CanMoveTo(CollisionPoint point) {
    if(_moveRestrictions.count(point)) {
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
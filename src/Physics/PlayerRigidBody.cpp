#include "Physics/PlayerRigidBody.hpp"
#include "GameObject.hpp"


PlayerRigidBody::PlayerRigidBody() : spic::RigidBody(0.045) {
    _gravityScale = 0.055;
    _mass = 8;
    auto maxSpeed = Point();
    maxSpeed.x = 2;
    maxSpeed.y = 20;
    _maxSpeed = maxSpeed;
}
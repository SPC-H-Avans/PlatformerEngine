#include "Physics/PlayerRigidBody.hpp"
#include "GameObject.hpp"


PlayerRigidBody::PlayerRigidBody() : spic::RigidBody(0.060) {
    _gravityScale = 0.055;
    _mass = 8;
    auto maxSpeed = Point {2.0, 20.0};
    _maxSpeed = maxSpeed;
}
BOOST_CLASS_EXPORT(PlayerRigidBody);
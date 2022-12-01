#include "Physics/PlayerRigidBody.hpp"
#include "Point.hpp"
#include <algorithm>
#include "Physics/Collision.hpp"
#include "GameObject.hpp"


PlayerRigidBody::PlayerRigidBody() () {
    _gravityScale = 0.025;
    _mass = 10;
}



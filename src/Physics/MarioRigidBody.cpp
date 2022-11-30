#include "Physics/MarioRigidBody.hpp"
#include "Point.hpp"
#include <algorithm>
#include "Physics/Collision.hpp"
#include "GameObject.hpp"


MarioRigidBody::MarioRigidBody() {
    _gravityScale = 0.025;
    _mass = 10;
}



#include "Physics/PlayerRigidBody.hpp"
#include "Point.hpp"
#include <algorithm>
#include "Physics/Collision.hpp"
#include "GameObject.hpp"

void PlayerRigidBody::AddForce(const spic::Point& forceDirection) {

    if(forceDirection.x < 0 && CanMoveTo(CollisionPoint::Left)) { // Move left
        _horizontalSpeed = std::max(_horizontalSpeed - PLAYER_ACCELERATION, -PLAYER_WALK_SPEED);
    }
    else if(forceDirection.x > 0 && CanMoveTo(CollisionPoint::Right)) { // Move right
        _horizontalSpeed = std::min(_horizontalSpeed + PLAYER_ACCELERATION, PLAYER_WALK_SPEED);
    }

    if(_horizontalSpeed < 0 && forceDirection.x >= 0) { // Slow down the player when gliding to the left
        _horizontalSpeed += PLAYER_ACCELERATION / 7;
    }
    else if(_horizontalSpeed > 0 && forceDirection.x <= 0) { // Slow down the player when gliding to the right
        _horizontalSpeed -= PLAYER_ACCELERATION / 7;
    }

    if(forceDirection.y > 0
       && CanMoveTo(CollisionPoint::Top)
       && !CanMoveTo(CollisionPoint::Bottom)) { // Jump when on top of an object
        _verticalSpeed = PLAYER_JUMP_SPEED;
        _jumpTimer = PLAYER_JUMP_TIMER;
    }
    else if(_jumpTimer > 0 && CanMoveTo(CollisionPoint::Top)) { // High jump
        _verticalSpeed = PLAYER_JUMP_SPEED;
        _jumpTimer -= 1;
    }
    else {
        _verticalSpeed = std::min(_gravityScale + _verticalSpeed, PLAYER_MAX_VERTICAL_SPEED);
    }

    _verticalSpeed += _gravityScale;
    if(_verticalSpeed > 0 && !CanMoveTo(CollisionPoint::Bottom)) {
        _verticalSpeed = 0;
    }

    if(_horizontalSpeed > 0 && !CanMoveTo(CollisionPoint::Right)) {
        _horizontalSpeed = 0;
    }

    if(_horizontalSpeed < 0 && !CanMoveTo(CollisionPoint::Left)) {
        _horizontalSpeed = 0;
    }

    if(_verticalSpeed < 0 && !CanMoveTo(CollisionPoint::Top)) {
        _verticalSpeed = 0;
    }

    std::shared_ptr<GameObject> gameObject { GetGameObject().lock() };
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        transform.position.x += _horizontalSpeed;
        transform.position.y += _verticalSpeed;
        gameObject->SetTransform(transform);
    } else { // GameObject was already deleted
        gameObject.reset();
    }
}

PlayerRigidBody::PlayerRigidBody() {
    _gravityScale = 0.25F;
}



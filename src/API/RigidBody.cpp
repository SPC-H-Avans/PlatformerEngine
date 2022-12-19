#include "RigidBody.hpp"
#include "Exceptions/IllegalCollisionBehaviourException.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"

void spic::RigidBody::AddForce(const spic::Point &force, double speedMultiplier) {
    auto x_acceleration = force.x / _mass;
    _velocity.x += x_acceleration;

    if (_velocity.x > 0) {
        _velocity.x -= _friction;
        _velocity.x = std::min(_velocity.x, _maxSpeed.x * speedMultiplier);
    } else if (_velocity.x < 0) {
        _velocity.x += _friction;
        _velocity.x = std::max(_velocity.x, -_maxSpeed.x * speedMultiplier);
    }

    if (force.y > 0
        && !CanMoveTo(CollisionPoint::Bottom)) { // Jump when on top of an object
        auto y_acceleration = force.y / _mass;
        _velocity.y -= y_acceleration;
    }

    _velocity.y += _gravityScale * _mass;

    if (_velocity.y > 0 && !CanMoveTo(CollisionPoint::Bottom)) { _velocity.y = 0; }
    if (_velocity.x > 0 && !CanMoveTo(CollisionPoint::Right)) { _velocity.x = 0; }
    if (_velocity.x < 0 && !CanMoveTo(CollisionPoint::Left)) { _velocity.x = 0; }
    if (_velocity.y < 0 && !CanMoveTo(CollisionPoint::Top)) { _velocity.y = 0; }

    std::shared_ptr<GameObject> gameObject{GetGameObject().lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        transform.position.x += _velocity.x;
        transform.position.y += _velocity.y;
        gameObject->SetTransform(transform);

        try {
            auto &engine = platformer_engine::Engine::GetInstance();
            auto localClientId = engine.GetLocalClientId();
            if (gameObject != nullptr && localClientId == gameObject->GetOwnerId()) {
                switch (engine.GetNetworkingStatus()) {
                    case platformer_engine::MultiplayerClient:
                        engine.GetClientNetworkManager().UpdateNetworkedGameObjectTransform(transform,
                                                                                            gameObject->GetName());
                        break;
                    case platformer_engine::MultiplayerServer:
                        engine.GetServerNetworkManager().UpdateNetworkedGameObjectTransform(transform,
                                                                                            gameObject->GetName());
                        break;
                    case platformer_engine::Singleplayer:
                        break;
                }
            }
        } catch (std::exception &e) {
            //Just ignore the exception, we will try resending the transform later
        }
    } else { // GameObject was already deleted
        gameObject.reset();
    }
}

bool spic::RigidBody::CanMoveTo(CollisionPoint point) {
    if (_moveRestrictions.contains(point)) {
        return _moveRestrictions[point] == 0;
    }
    return true;
}

void spic::RigidBody::AllowMoveTo(CollisionPoint point) {
    if (_moveRestrictions[point] <= 0) { // Numbers below zero are illegal
        throw IllegalCollisionBehaviourException(_bodyType, point);
    }
    _moveRestrictions[point] -= 1;
}

void spic::RigidBody::DenyMoveTo(CollisionPoint point) {
    _moveRestrictions[point] += 1;
}

auto RigidBody::GetMaxSpeed() const -> Point {
    return _maxSpeed;
}

auto RigidBody::GetVelocity() const -> Point {
    return _velocity;
}

RigidBody::RigidBody(float friction)
        : _bodyType(BodyType::staticBody), _mass(0), _gravityScale(0), _friction(friction) {
}

RigidBody::RigidBody() : _friction(0) {

}


BOOST_CLASS_EXPORT(RigidBody);
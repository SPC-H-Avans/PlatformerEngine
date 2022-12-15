#include "Physics/MoveSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"
#include <memory>


void MoveSystem::Update() {
    auto gameObjects = GameObject::FindObjectsOfType<GameObject>();

    for(auto& obj : gameObjects) {
        if(obj != nullptr && obj->GetOwnerId() == _clientId) { //If owned by client
            auto rigidBody = std::static_pointer_cast<RigidBody>(obj->GetComponent<RigidBody>());
            if(rigidBody != nullptr && rigidBody->BodyType() == BodyType::dynamicBody) {

                Point totalForce = {0,0};

                // Gravity force
                totalForce += CalculateGravityForce(rigidBody);

                // Friction force
                totalForce += CalculateFrictionForce(rigidBody);

                // Force driven Entity force
                totalForce += CalculateFDEForce(rigidBody, obj->GetTransform().position);

                // Apply all forces
                rigidBody->AddForce(totalForce);

                // Limit the velocity to prevent Collisions
                rigidBody->SetVelocity(GetLimitedVelocityForCollisions(rigidBody));

                // Set the transform for the GameObject
                auto transform = obj->GetTransform();
                transform.position += velocity;
                obj->SetTransform(transform);

                rigidBody->SetHeading();
            }
        }
    }
}

auto MoveSystem::CalculateGravityForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point {
    auto yGravity = rigidBody->GetGravityScale() * rigidBody->GetMass() * rigidBody->GetMass();
    return {0, yGravity};
}

auto MoveSystem::CalculateFrictionForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point {
    auto absXVelocity = abs(rigidBody->GetVelocity().x);
    if(absXVelocity > 0) {
        auto velocityDecrease = 1.0;
        if(absXVelocity < 1) {
            velocityDecrease = absXVelocity;
        }
        return {rigidBody->GetFriction() * -1 * rigidBody->GetHeading().x * rigidBody->GetMass() * velocityDecrease, 0};
    }
    return {0,0};
}

auto MoveSystem::CalculateFDEForce(const std::shared_ptr<RigidBody>& rigidBody, Point position) -> Point {
    auto forceDrivenEntityBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(rigidBody);
    if(forceDrivenEntityBody != nullptr) {
        auto following = forceDrivenEntityBody->GetFollowing().lock();
        if(following) {
            if(following->GetTransform().position.Distance(position) < forceDrivenEntityBody->GetFollowRange()) {
                forceDrivenEntityBody->FollowOn();
            } else {
                forceDrivenEntityBody->WanderOn();
            }
        } else {
            forceDrivenEntityBody->WanderOn();
            following.reset();
        }
        auto FDEForce = forceDrivenEntityBody->CalcSteeringForce();
        return FDEForce;
    }
    return {0,0};
}

auto GetLimitedVelocityForCollisions(const std::shared_ptr<RigidBody>& rigidBody) {
    auto velocity = rigidBody->GetVelocity();

    if (velocity.y > 0 && !rigidBody->CanMoveTo(CollisionPoint::Bottom)
        || velocity.y < 0 && !rigidBody->CanMoveTo(CollisionPoint::Top)) {
        velocity.y = 0;
    }
    if (velocity.x > 0 && !rigidBody->CanMoveTo(CollisionPoint::Right)
        || velocity.x < 0 && !rigidBody->CanMoveTo(CollisionPoint::Left)) {
        velocity.x = 0;
    }

    return velocity;
}

MoveSystem::MoveSystem(int localClientId) : _clientId(localClientId) {}

#include "Physics/MoveSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "Physics/ForceDrivenEntity.hpp"
#include "Engine/Engine.hpp"
#include <memory>


void MoveSystem::Update(double speedMultiplier) {
    auto gameObjects = GameObject::FindObjectsOfType<GameObject>();
    auto &engine = platformer_engine::Engine::GetInstance();
    const auto localClientId = engine.GetLocalClientId();

    for(auto& obj : gameObjects) {
        if(obj != nullptr && obj->GetOwnerId() == localClientId) { //If owned by client
            auto rigidBody = std::static_pointer_cast<RigidBody>(obj->GetComponent<RigidBody>());
            if(rigidBody != nullptr && rigidBody->BodyType() == BodyType::dynamicBody) {

                Point totalForce = {0,0};

                // Gravity force
                totalForce += CalculateGravityForce(rigidBody);

                // Friction force
                totalForce += CalculateFrictionForce(rigidBody);

                // Force driven Entity force
                totalForce += CalculateFDEForce(obj);

                // Apply all forces
                rigidBody->AddForce(totalForce, speedMultiplier);

                // Limit the velocity to prevent Collisions
                rigidBody->SetVelocity(GetLimitedVelocityForCollisions(rigidBody));

                // Set the transform for the GameObject
                auto transform = obj->GetTransform();
                transform.position += rigidBody->GetVelocity();
                obj->SetTransform(transform);

                rigidBody->SetHeading();

                try {
                    switch (engine.GetNetworkingStatus()) {
                        case platformer_engine::MultiplayerClient:
                            engine.GetClientNetworkManager().UpdateNetworkedGameObjectTransform(transform,
                                                                                                obj->GetName());
                            break;
                        case platformer_engine::MultiplayerServer:
                            engine.GetServerNetworkManager().UpdateNetworkedGameObjectTransform(transform,
                                                                                                obj->GetName());
                            break;
                        case platformer_engine::Singleplayer:
                            break;
                    }
                } catch (std::exception &e) {
                    //Just ignore the exception, we will try resending the transform later
                }
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

auto MoveSystem::CalculateFDEForce(const std::shared_ptr<GameObject>& gameObject) -> Point {
    auto forceDrivenEntity = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(gameObject->GetComponent<platformer_engine::ForceDrivenEntity>());
    if(forceDrivenEntity != nullptr) {
        auto FDEForce = forceDrivenEntity->CalcSteeringForce();
        return FDEForce;
    }
    return {0,0};
}

auto MoveSystem::GetLimitedVelocityForCollisions(const std::shared_ptr<RigidBody>& rigidBody) -> Point {
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

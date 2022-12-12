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
                auto gravity = rigidBody->GetGravityScale() * rigidBody->GetMass() * rigidBody->GetMass();
                totalForce += {0, gravity};

                // Friction force
                if(rigidBody->GetVelocity().x != 0) {
                    totalForce += {rigidBody->GetFriction() * -1 * rigidBody->GetHeading().x * rigidBody->GetMass(), 0};
                }


                auto forceDrivenEntityBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(rigidBody);
                if(forceDrivenEntityBody != nullptr) {
                    auto following = forceDrivenEntityBody->GetFollowing().lock();
                    if(following) {
                        if(following->GetTransform().position.Distance(obj->GetTransform().position) < forceDrivenEntityBody->GetFollowRange()) {
                            forceDrivenEntityBody->FollowOn();
                        } else {
                            forceDrivenEntityBody->WanderOn();
                        }
                    } else {
                        following.reset();
                    }
                    auto FDEForce = forceDrivenEntityBody->CalcSteeringForce();
                    totalForce += FDEForce;
                }

                rigidBody->AddForce(totalForce);
                auto velocity = rigidBody->GetVelocity();

                if (velocity.y > 0 && !rigidBody->CanMoveTo(CollisionPoint::Bottom)
                    || velocity.y < 0 && !rigidBody->CanMoveTo(CollisionPoint::Top)) {
                    velocity.y = 0;
                }
                if (velocity.x > 0 && !rigidBody->CanMoveTo(CollisionPoint::Right)
                    || velocity.x < 0 && !rigidBody->CanMoveTo(CollisionPoint::Left)) {
                    velocity.x = 0;
                }

                rigidBody->SetVelocity(velocity);
                auto transform = obj->GetTransform();
                transform.position += velocity;
                obj->SetTransform(transform);

                rigidBody->SetHeading();
            }
        }
    }

}


MoveSystem::MoveSystem(int localClientId) : _clientId(localClientId) {}

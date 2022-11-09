#include "PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include <algorithm>

using namespace spic;

//TODO check speed of this.

void PhysicsSystem::Update() {
    CheckCollisions();
}

bool PhysicsSystem::CheckCollisions() {
    std::vector<std::shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();
    std::vector<std::shared_ptr<GameObject>> collidableObjects;
    std::remove_copy_if(gameObjects.begin(), gameObjects.end(), collidableObjects.begin(), [&](std::shared_ptr<GameObject> g) { return g->GetComponent<Collider>() != nullptr; }); //Only GameObjects with collider

    for(auto& initiator : collidableObjects) {
        std::shared_ptr<RigidBody> body = std::static_pointer_cast<RigidBody>(initiator->GetComponent<RigidBody>());
        std::shared_ptr<BoxCollider> aCol = std::static_pointer_cast<BoxCollider>(initiator->GetComponent<BoxCollider>());

        if(body != nullptr && aCol != nullptr && body->BodyType() == BodyType::dynamicBody) { //Checks from dynamicBody perspective
            //Find all collisions
            for(auto& receiver : collidableObjects) { //Currently only boxCollision
                std::shared_ptr<BoxCollider> bCol = std::static_pointer_cast<BoxCollider>(receiver->GetComponent<BoxCollider>());
                std::shared_ptr<RigidBody> recBody = std::static_pointer_cast<RigidBody>(receiver->GetComponent<RigidBody>());



                if(CheckBoxCollision(initiator->GetTransform().position, *aCol, receiver->GetTransform().position, *bCol)) { //If collision
                    if(collisions.count(aCol) > 0) {
                        if (std::find(collisions[aCol].begin(), collisions[aCol].end(), bCol) != collisions[aCol].end()) {
                            RemainCollision(initiator, aCol, receiver, bCol);
                        } else {
                            CreateCollision(initiator, aCol, receiver, bCol);
                        }
                    }


                    std::static_pointer_cast<BehaviourScript>(initiator->GetComponent<BehaviourScript>())->OnTriggerEnter2D(*bCol);
                    std::static_pointer_cast<BehaviourScript>(receiver->GetComponent<BehaviourScript>())->OnTriggerEnter2D(*aCol);
                } else {
                    if (std::find(collisions[aCol].begin(), collisions[aCol].end(), bCol) != collisions[aCol].end()) {
                        EndCollision(initiator, aCol, receiver, bCol);
                    }
                }
            }
        }
    }
}

void PhysicsSystem::CreateCollision(std::shared_ptr<GameObject> initiator, std::shared_ptr<Collider> init_collider,
                                    std::shared_ptr<GameObject> receiver, std::shared_ptr<Collider> rec_collider) {

    if(collisions.count(init_collider) > 0) {
        collisions[init_collider].emplace_back(rec_collider);
    } else {
        collisions[init_collider] = {rec_collider};
    }

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(*rec_collider);
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(*init_collider);
}

void PhysicsSystem::RemainCollision(const std::shared_ptr<GameObject>& initiator, const std::shared_ptr<Collider>& init_collider,
                                    const std::shared_ptr<GameObject>& receiver, const std::shared_ptr<Collider>& rec_collider) {

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(*rec_collider);
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(*init_collider);
}

void PhysicsSystem::EndCollision(std::shared_ptr<GameObject> initiator, std::shared_ptr<Collider> init_collider,
                                 std::shared_ptr<GameObject> receiver, std::shared_ptr<Collider> rec_collider) {
    //Remove from list
    if(collisions.count(init_collider) > 0) {
        auto col = std::find(collisions[init_collider].begin(), collisions[init_collider].end(), rec_collider);
        collisions[init_collider].erase(col);
    }

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(*rec_collider);
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(*init_collider);

    //Call Behaviourscripts
}

bool PhysicsSystem::CheckBoxCollision(Point& aPos, const BoxCollider& aCol, Point& bPos, const BoxCollider& bCol) {
    bool x_overlaps = (aPos.x < bPos.x + bCol.Width()) && (aPos.x + aCol.Width() > bPos.x);
    bool y_overlaps = (aPos.y < bPos.y + bCol.Height()) && (aPos.y + aCol.Height() > bPos.y);
    return (x_overlaps && y_overlaps);
}
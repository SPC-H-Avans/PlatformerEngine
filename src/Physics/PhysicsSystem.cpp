#include "PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include <algorithm>

using namespace spic;

//TODO check different bodytypes
//TODO fix different Triggers
//TODO check speed of this.

bool PhysicsSystem::CheckCollisions() {
    std::vector<std::shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();
    std::vector<std::shared_ptr<GameObject>> collidableObjects;
    std::remove_copy_if(gameObjects.begin(), gameObjects.end(), collidableObjects.begin(), [&](std::shared_ptr<GameObject> g) { return g->GetComponent<Collider>() != nullptr; }); //Only GameObjects with collider

    for(auto& initiator : collidableObjects) {
        std::shared_ptr<RigidBody> body = std::static_pointer_cast<RigidBody>(initiator->GetComponent<RigidBody>());
        std::shared_ptr<BoxCollider> aCol = std::static_pointer_cast<BoxCollider>(initiator->GetComponent<BoxCollider>());

        if(body != nullptr && aCol != nullptr) {
            //Find all collisions
            for(auto& receiver : collidableObjects) {
                //Currently only boxCollision
                std::shared_ptr<BoxCollider> bCol = std::static_pointer_cast<BoxCollider>(receiver->GetComponent<BoxCollider>());

                if(CheckBoxCollision(initiator->GetTransform().position, *aCol, receiver->GetTransform().position, *bCol)) {
                    std::static_pointer_cast<BehaviourScript>(initiator->GetComponent<BehaviourScript>())->OnTriggerEnter2D(*bCol);
                    std::static_pointer_cast<BehaviourScript>(receiver->GetComponent<BehaviourScript>())->OnTriggerEnter2D(*aCol);
                }
            }
        }
    }
}

bool PhysicsSystem::CheckBoxCollision(Point& aPos, const BoxCollider& aCol, Point& bPos, const BoxCollider& bCol) {
    bool x_overlaps = (aPos.x < bPos.x + bCol.Width()) && (aPos.x + aCol.Width() > bPos.x);
    bool y_overlaps = (aPos.y < bPos.y + bCol.Height()) && (aPos.y + aCol.Height() > bPos.y);
    return (x_overlaps && y_overlaps);
}
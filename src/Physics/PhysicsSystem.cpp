#include "Physics/PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include <algorithm>

using spic::GameObject;
using spic::RigidBody;
using spic::BoxCollider;
using spic::Collider;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

//TODO test collision check method
//TODO check speed of this.

void PhysicsSystem::Update() {
    CheckCollisions();
}

auto GetBoxColliders() -> vector<shared_ptr<GameObject>> {
    vector<shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();
    vector<shared_ptr<GameObject>> result;
    for(const auto& obj : gameObjects) {
        if(obj != nullptr) {
            auto val = obj->GetComponent<BoxCollider>();
            if(val != nullptr) {
                result.emplace_back(obj);
            }
        }
    }
    return result;
}

void PhysicsSystem::CheckCollisions() {
    //Get all gameobjects that have boxcolliders
    auto collidableObjects = GetBoxColliders();

    for(auto& initiator : collidableObjects) {
        shared_ptr<RigidBody> body = std::static_pointer_cast<RigidBody>(initiator->GetComponent<RigidBody>());
        shared_ptr<BoxCollider> aCol = std::static_pointer_cast<BoxCollider>(initiator->GetComponent<BoxCollider>());

        if(body != nullptr && aCol != nullptr && body->BodyType() == BodyType::dynamicBody) { //Checks from dynamicBody perspective
            //Find all collisions
            for(auto& receiver : collidableObjects) { //Currently only boxCollision
                if(receiver != initiator) {
                    shared_ptr<BoxCollider> bCol = std::static_pointer_cast<BoxCollider>(receiver->GetComponent<BoxCollider>());
                    shared_ptr<RigidBody> recBody = std::static_pointer_cast<RigidBody>(receiver->GetComponent<RigidBody>());

                    unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> collision = CheckBoxCollision(initiator->GetTransform().position, *aCol, receiver->GetTransform().position, *bCol);
                    if(collision != nullptr) { //If collision
                        if(_collisions.count(aCol) > 0) {
                            if (find(_collisions[aCol].begin(), _collisions[aCol].end(), bCol) != _collisions[aCol].end()) {
                                RemainCollision(initiator, aCol, receiver, bCol);
                            } else {
                                CreateCollision(initiator, aCol, receiver, bCol, *collision);
                            }
                        } else {
                            CreateCollision(initiator, aCol, receiver, bCol, *collision);
                        }
                    } else {
                        if (find(_collisions[aCol].begin(), _collisions[aCol].end(), bCol) != _collisions[aCol].end()) {
                            EndCollision(initiator, aCol, receiver, bCol);
                        }
                    }
                }
            }
        }
    }
    }

void PhysicsSystem::CreateCollision(const shared_ptr<GameObject>& initiator, const shared_ptr<Collider>& init_collider,
                                    const shared_ptr<GameObject>& receiver, const shared_ptr<Collider>& rec_collider,
                                    std::tuple<CollisionPoint, CollisionPoint> direction) {

    if(_collisions.count(init_collider) > 0) {
        _collisions[init_collider].emplace_back(rec_collider);
    } else {
        _collisions[init_collider] = {rec_collider};
    }

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(Collision (*rec_collider, std::get<0>(direction)));
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(Collision (*init_collider, std::get<1>(direction)));
}

void PhysicsSystem::RemainCollision(const shared_ptr<GameObject>& initiator, const shared_ptr<Collider>& init_collider,
                                    const shared_ptr<GameObject>& receiver, const shared_ptr<Collider>& rec_collider) {

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(Collision (*rec_collider));
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(Collision (*init_collider));
}

void PhysicsSystem::EndCollision(const shared_ptr<GameObject>& initiator, const shared_ptr<Collider>& init_collider,
                                 const shared_ptr<GameObject>& receiver, const shared_ptr<Collider>& rec_collider) {
    //Remove from list
    if(_collisions.count(init_collider) > 0) {
        auto col = find(_collisions[init_collider].begin(), _collisions[init_collider].end(), rec_collider);
        _collisions[init_collider].erase(col);
    }

    //Call Behaviour scripts
    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(Collision (*rec_collider));
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(Collision (*init_collider));
}

auto PhysicsSystem::CheckBoxCollision(Point aPos, const BoxCollider& aCol, Point bPos, const BoxCollider& bCol) -> std::unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> {
    bool x_overlap = (aPos.x <= bPos.x + bCol.Width()) && (aPos.x + aCol.Width() >= bPos.x);
    bool y_overlap = (aPos.y <= bPos.y + bCol.Height()) && (aPos.y + aCol.Height() >= bPos.y);


    if(x_overlap && y_overlap) {
        //This does not work if object is inside the other, only overlap
        double a_bottom = aPos.y + aCol.Height();
        double b_bottom = bPos.y + bCol.Height();
        double a_right = aPos.x + aCol.Width();
        double b_right = bPos.x + bCol.Width();

        //Distance between bottom b and top a
        double bottom_col = b_bottom - aPos.y;
        //Distance between bottom a and top b
        double top_col = a_bottom - bPos.y;
        //Distance between right a and left b
        double left_col = a_right - bPos.x;
        //Distance between left a and right b
        double right_col = b_right - aPos.x;

        if (top_col < bottom_col && top_col < left_col && top_col < right_col ){//Bottom collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Bottom, CollisionPoint::Top));
        }
        if (bottom_col < top_col && bottom_col < left_col && bottom_col < right_col){ //Top collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Top, CollisionPoint::Bottom));
        }
        if (left_col < right_col && left_col < top_col && left_col < bottom_col) { //Left collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Left, CollisionPoint::Right));
        }
        if (right_col < left_col && right_col < top_col && right_col < bottom_col ) { //Right collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Right, CollisionPoint::Left));
        }

        return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Uncertain, CollisionPoint::Uncertain));
    }
    return nullptr; //No Collision
}
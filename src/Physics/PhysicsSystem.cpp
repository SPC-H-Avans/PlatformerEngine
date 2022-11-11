#include "PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include "Collision.hpp"
#include <algorithm>

using namespace spic;
using namespace std;

//TODO check speed of this.

void PhysicsSystem::Update() {
    CheckCollisions();
}

void PhysicsSystem::CheckCollisions() {
    vector<shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();
    vector<shared_ptr<GameObject>> collidableObjects;
    remove_copy_if(gameObjects.begin(), gameObjects.end(), collidableObjects.begin(), [&](shared_ptr<GameObject> g) { return g->GetComponent<Collider>() != nullptr; }); //Only GameObjects with collider

    for(auto& initiator : collidableObjects) {
        shared_ptr<RigidBody> body = static_pointer_cast<RigidBody>(initiator->GetComponent<RigidBody>());
        shared_ptr<BoxCollider> aCol = static_pointer_cast<BoxCollider>(initiator->GetComponent<BoxCollider>());

        if(body != nullptr && aCol != nullptr && body->BodyType() == BodyType::dynamicBody) { //Checks from dynamicBody perspective
            //Find all collisions
            for(auto& receiver : collidableObjects) { //Currently only boxCollision
                shared_ptr<BoxCollider> bCol = static_pointer_cast<BoxCollider>(receiver->GetComponent<BoxCollider>());
                shared_ptr<RigidBody> recBody = static_pointer_cast<RigidBody>(receiver->GetComponent<RigidBody>());

                unique_ptr<tuple<CollisionPoint, CollisionPoint>> collision = CheckBoxCollision(initiator->GetTransform().position, *aCol, receiver->GetTransform().position, *bCol);
                if(collision != nullptr) { //If collision
                    if(_collisions.count(aCol) > 0) {
                        if (find(_collisions[aCol].begin(), _collisions[aCol].end(), bCol) != _collisions[aCol].end()) {
                            RemainCollision(initiator, aCol, receiver, bCol);
                        } else {
                            CreateCollision(initiator, aCol, receiver, bCol, *collision);
                        }
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

void PhysicsSystem::CreateCollision(shared_ptr<GameObject> initiator, shared_ptr<Collider> init_collider,
                                    shared_ptr<GameObject> receiver, shared_ptr<Collider> rec_collider,
                                    std::tuple<CollisionPoint, CollisionPoint> direction) {

    if(_collisions.count(init_collider) > 0) {
        _collisions[init_collider].emplace_back(rec_collider);
    } else {
        _collisions[init_collider] = {rec_collider};
    }

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(Collision (*rec_collider, get<0>(direction)));
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(Collision (*init_collider, get<1>(direction)));
}

void PhysicsSystem::RemainCollision(const shared_ptr<GameObject>& initiator, const shared_ptr<Collider>& init_collider,
                                    const shared_ptr<GameObject>& receiver, const shared_ptr<Collider>& rec_collider) {

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(Collision (*rec_collider));
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(Collision (*init_collider));
}

void PhysicsSystem::EndCollision(shared_ptr<GameObject> initiator, shared_ptr<Collider> init_collider,
                                 shared_ptr<GameObject> receiver, shared_ptr<Collider> rec_collider) {
    //Remove from list
    if(_collisions.count(init_collider) > 0) {
        auto col = find(_collisions[init_collider].begin(), _collisions[init_collider].end(), rec_collider);
        _collisions[init_collider].erase(col);
    }

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(Collision (*rec_collider));
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(Collision (*init_collider));

    //Call Behaviour scripts
}

auto PhysicsSystem::CheckBoxCollision(Point& aPos, const BoxCollider& aCol, Point& bPos, const BoxCollider& bCol) -> std::unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> {
    //This does not work if object is inside the other, only overlap

    double a_bottom = aPos.y + aCol.Height();
    double b_bottom = bPos.y + bCol.Height();
    double a_right = aPos.x + aCol.Width();
    double b_right = bPos.x + bCol.Height();

    double bottom_col = b_bottom - aPos.y;
    double top_col = a_bottom - bPos.y;
    double left_col = a_right - bPos.x;
    double right_col = b_right - aPos.x;

    if (top_col < bottom_col && top_col < left_col && top_col < right_col )
    {
        //Top collision
        return make_unique<std::tuple<CollisionPoint, CollisionPoint>>(make_tuple(CollisionPoint::Top, CollisionPoint::Bottom));
    }
    if (bottom_col < top_col && bottom_col < left_col && bottom_col < right_col)
    {
        //bottom collision
        return make_unique<std::tuple<CollisionPoint, CollisionPoint>>(make_tuple(CollisionPoint::Bottom, CollisionPoint::Top));
    }
    if (left_col < right_col && left_col < top_col && left_col < bottom_col)
    {
        //Left collision
        return make_unique<std::tuple<CollisionPoint, CollisionPoint>>(make_tuple(CollisionPoint::Left, CollisionPoint::Right));
    }
    if (right_col < left_col && right_col < top_col && right_col < bottom_col )
    {
        //Right collision
        return make_unique<std::tuple<CollisionPoint, CollisionPoint>>(make_tuple(CollisionPoint::Right, CollisionPoint::Left));
    }

    //Without direction
    /*bool x_overlaps = (aPos.x < bPos.x + bCol.Width()) && (aPos.x + aCol.Width() > bPos.x);
    bool y_overlaps = (aPos.y < bPos.y + bCol.Height()) && (aPos.y + aCol.Height() > bPos.y);

    if(x_overlaps && y_overlaps) {

    }*/

    return nullptr;
}
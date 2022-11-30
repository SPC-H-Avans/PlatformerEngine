#include "Physics/PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include "Physics/MarioRigidBody.hpp"
//#include "Input.hpp"
#include <algorithm>

using spic::GameObject;
using spic::RigidBody;
using spic::BoxCollider;
using spic::Collider;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

PhysicsSystem::PhysicsSystem(int localClientId) : _clientId(localClientId) {}

void PhysicsSystem::Update() {
    MoveObjects();
    CheckCollisions();
}

void PhysicsSystem::MoveObjects() {

    //Get all GameObjects
    vector<shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();

    //Loop through the GameObjects and find ones with MarioRigidBody
    for(auto& gameObject : gameObjects) {
        shared_ptr<MarioRigidBody> mario = std::dynamic_pointer_cast<MarioRigidBody>(gameObject->GetComponent<RigidBody>());

        if(mario != nullptr) {
            // We found mario!
            // TODO @JESSE: Move this to a more logical location.
            auto point = Point();

//            if (spic::Input::GetKey(KeyCode::LEFT_ARROW)) {
//                point.x--;
//            }
//            if (spic::Input::GetKey(KeyCode::RIGHT_ARROW)) {
//                point.x++;
//            }
//            if (spic::Input::GetKey(KeyCode::UP_ARROW)) {
//                point.y+= 50;
//            }

            mario->AddForce(point);
        }
    }

}

//Get all objects with BoxColliders owned by the current client.
auto GetBoxCollidersFromClient(int ownerId) -> vector<shared_ptr<GameObject>> {
    auto gameObjects = vector<shared_ptr<GameObject>>();
    gameObjects = GameObject::FindObjectsOfType<GameObject>();
    auto result = vector<shared_ptr<GameObject>>();
    for(const auto& obj : gameObjects) {
        if(obj != nullptr && obj->GetOwnerId() == ownerId) { //If owned by client
            auto val = obj->GetComponent<BoxCollider>();
            if(val != nullptr) { //If has boxcollider
                result.emplace_back(obj);
            }
        }
    }
    return result;
}

void PhysicsSystem::CheckCollisions() {
    //Get all gameobjects that have boxcolliders
    auto collidableObjects = GetBoxCollidersFromClient(_clientId);

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
                    auto collisionsWithBCol = aCol->GetCollisionsWith(*bCol);
                    if(collision != nullptr) { //If collision
                        if(!aCol->GetCollisions().empty() && !collisionsWithBCol.empty()) {
                            auto collisionId = collisionsWithBCol.front().GetId();
                            // Remain Collision
                            RemainCollision(initiator, aCol, receiver, bCol, *collision, collisionId);
                        } else {
                            // Create collision
                            CreateCollision(initiator, aCol, receiver, bCol, *collision);
                        }
                    } else {
                        if(!collisionsWithBCol.empty()) {
                            auto collisionId = collisionsWithBCol.front().GetId();
                            EndCollision(initiator, aCol, receiver, bCol, collisionId);
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

    // Create two Collision objects with the same ID
    auto collisionInit = Collision(rec_collider, std::get<0>(direction), _collisionCnt);
    auto collisionRec = Collision(init_collider, std::get<1>(direction), _collisionCnt++);
    init_collider->AddCollision(collisionInit);
    rec_collider->AddCollision(collisionRec);

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(collisionInit);
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(collisionRec);
}

void PhysicsSystem::RemainCollision(const shared_ptr<GameObject>& initiator, const shared_ptr<Collider>& init_collider,
                                    const shared_ptr<GameObject>& receiver, const shared_ptr<Collider>& rec_collider,
                                    std::tuple<CollisionPoint, CollisionPoint> direction,
                                    const int collisionId) {

    auto init_collision = init_collider->GetCollisionById(collisionId);
    init_collision.Contact(std::get<0>(direction));
    auto rec_collision = rec_collider->GetCollisionById(collisionId);
    rec_collision.Contact(std::get<1>(direction));

    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(init_collision);
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(rec_collision);
}

void PhysicsSystem::EndCollision(const shared_ptr<GameObject>& initiator, const shared_ptr<Collider>& init_collider,
                                 const shared_ptr<GameObject>& receiver, const shared_ptr<Collider>& rec_collider,
                                 const int collisionId) {

    auto init_collision = init_collider->GetCollisionById(collisionId);
    auto rec_collision = rec_collider->GetCollisionById(collisionId);
    init_collider->RemoveCollision(collisionId);
    rec_collider->RemoveCollision(collisionId);

    //Call Behaviour scripts
    for(auto& script : initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(init_collision);
    for(auto& script : receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(rec_collision);
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

        if (top_col <= bottom_col && top_col <= left_col && top_col <= right_col ){//Bottom collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Bottom, CollisionPoint::Top));
        }
        if (bottom_col <= top_col && bottom_col <= left_col && bottom_col <= right_col){ //Top collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Top, CollisionPoint::Bottom));
        }
        if (left_col <= right_col && left_col <= top_col && left_col <= bottom_col) { //Right collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Right, CollisionPoint::Left));
        }
        if (right_col <= left_col && right_col <= top_col && right_col <= bottom_col ) { //Left collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Left, CollisionPoint::Right));
        }

        return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(std::make_tuple(CollisionPoint::Uncertain, CollisionPoint::Uncertain));
    }
    return nullptr; //No Collision
}

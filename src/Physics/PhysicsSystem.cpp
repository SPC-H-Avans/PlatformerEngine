#include "Physics/PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include "Physics/PlayerRigidBody.hpp"
//#include "Input.hpp"
#include <algorithm>
#include <map>
#include <boost/functional/hash.hpp>


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
    // TODO
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

typedef std::unordered_map<std::pair<int, int>, std::vector<shared_ptr<GameObject>>, boost::hash<std::pair<int, int>>> SpatialMap;
const int mapCellSize = 16; //TODO move??

//Function for adding to map
void AddToMap(Point point, shared_ptr<GameObject>& obj, SpatialMap& map) {
    //TODO Make 16 not a magic number?
    auto key = std::make_pair(floor(point.x / mapCellSize), floor(point.y / mapCellSize));
    if(map.contains(key)) {
        map[key].push_back(obj);
    } else {
        map[key] = std::vector {obj};
    }
}

//Function for checking each corner
void RegisterInSpatial(shared_ptr<GameObject>& obj, BoxCollider& objCollider, SpatialMap& map) {
    Point min = obj->GetTransform().position;
    //Get every corner
    Point max { min.x + objCollider.Width(), min.y + objCollider.Height() };

    //TopLeft
    AddToMap(min, obj, map);
    //TopRight
    AddToMap({max.x, min.y}, obj, map);
    //BottomLeft
    AddToMap({min.x, max.y}, obj, map);
    //BottomRight
    AddToMap(max, obj, map);
}

std::pair<SpatialMap, vector<shared_ptr<GameObject>>> SetupSpatialMap(int ownerId) {
    vector<shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();
    vector<shared_ptr<GameObject>> dynamicBodies;
    SpatialMap spatialMap;

    for(auto& obj : gameObjects) {
        if(obj != nullptr && obj->GetOwnerId() == ownerId) { //If owned by client
            auto boxCollider = std::static_pointer_cast<BoxCollider>(obj->GetComponent<BoxCollider>());
            if(boxCollider != nullptr) { //If boxcollider
                RegisterInSpatial(obj, *boxCollider, spatialMap);
                
                auto rigidBody = std::static_pointer_cast<RigidBody>(obj->GetComponent<RigidBody>());
                if(rigidBody != nullptr && rigidBody->BodyType() == BodyType::dynamicBody) {
                    dynamicBodies.push_back(obj);
                }
            }
        }
    }

    //TODO is this an intensive copy? probably, ownership? MOVE??
    return std::make_pair(spatialMap, dynamicBodies);
}

vector<shared_ptr<GameObject>> GetFromMap(Point point, SpatialMap& map) {
    auto key = std::make_pair(floor(point.x / mapCellSize), floor(point.y / mapCellSize));
    if(map.contains(key)) {
        return map[key];
        //TODO is this an intensive copy? probably, ownership? MOVE??
    }
    return {};
}

vector<shared_ptr<GameObject>> GetNearbyObjects(GameObject& obj, BoxCollider& objCollider, SpatialMap& map) {
    vector<shared_ptr<GameObject>> result;
    //Retrieve from spatial;
    Point min = obj.GetTransform().position;
    Point max { min.x + objCollider.Width(), min.y + objCollider.Height() };

    //TopLeft
    auto tl = GetFromMap(min, map);
    result.insert(result.end(), tl.begin(), tl.end());
    //TopRight
    auto tr = GetFromMap({max.x, min.y}, map);
    result.insert(result.end(), tr.begin(), tr.end());
    //BottomLeft
    auto bl = GetFromMap({min.x, max.y}, map);
    result.insert(result.end(), bl.begin(), bl.end());
    //BottomRight
    auto br = GetFromMap(max, map);
    result.insert(result.end(), br.begin(), br.end());

    //TODO is this an intensive copy? probably, ownership? MOVE??
    return result;
}

void PhysicsSystem::CheckCollisions() {
    //TODO SPATIAL HASHMAP
    auto result = SetupSpatialMap(_clientId);
    auto spatialMap = result.first;
    auto dynamicObjects = result.second;

    for(auto& objA : dynamicObjects) {
        shared_ptr<BoxCollider> aCol = std::static_pointer_cast<BoxCollider>(objA->GetComponent<BoxCollider>());
        if(aCol == nullptr) {
            for(auto& objB : GetNearbyObjects(*objA, *aCol, spatialMap)) {
                shared_ptr<BoxCollider> bCol = std::static_pointer_cast<BoxCollider>(objB->GetComponent<BoxCollider>());

                unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> collision = CheckBoxCollision(objA->GetTransform().position, *aCol, objB->GetTransform().position, *bCol);
                auto collisionsWithBCol = aCol->GetCollisionsWith(*bCol);
                if(collision != nullptr) { //If collision
                    if(!aCol->GetCollisions().empty() && !collisionsWithBCol.empty()) {
                        auto collisionId = collisionsWithBCol.front().GetId();
                        // Remain Collision
                        RemainCollision(objA, aCol, objB, bCol, *collision, collisionId);
                    } else {
                        // Create collision
                        CreateCollision(objA, aCol, objB, bCol, *collision);
                    }
                } else {
                    if(!collisionsWithBCol.empty()) {
                        auto collisionId = collisionsWithBCol.front().GetId();
                        EndCollision(objA, aCol, objB, bCol, collisionId);
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

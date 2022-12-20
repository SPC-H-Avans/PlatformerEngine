#include "Physics/PhysicsSystem.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Transform.hpp"
#include "BehaviourScript.hpp"
#include <algorithm>
#include <unordered_map>
#include <boost/functional/hash.hpp>


using spic::GameObject;
using spic::RigidBody;
using spic::BoxCollider;
using spic::Collider;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

PhysicsSystem::PhysicsSystem(int localClientId) : _clientId(localClientId) {}

void PhysicsSystem::Update(double speedMultiplier) {
    MoveObjects(speedMultiplier);
    CheckCollisions();
}

void PhysicsSystem::MoveObjects(double speedMultiplier) {
    // TODO
}

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

typedef std::unordered_map<std::pair<int, int>, std::vector<shared_ptr<GameObject>>, pair_hash> SpatialMap;
const int MAP_CELL_SIZE = 16;

//Function for adding to map
void AddToMap(Point point, shared_ptr<GameObject> &obj, SpatialMap &map) {
    auto key = std::make_pair(floor(point.x / MAP_CELL_SIZE), floor(point.y / MAP_CELL_SIZE));
    if (map.contains(key)) {
        map[key].push_back(obj);
    } else {
        map[key] = std::vector{obj};
    }
}

//Function for checking each corner
void RegisterInSpatial(shared_ptr<GameObject> &obj, BoxCollider &objCollider, SpatialMap &map) {
    const Point min = obj->GetTransform().position;
    //Get every corner
    const Point max{min.x + objCollider.Width(), min.y + objCollider.Height()};

    //TopLeft
    AddToMap(min, obj, map);
    //TopRight
    AddToMap({max.x, min.y}, obj, map);
    //BottomLeft
    AddToMap({min.x, max.y}, obj, map);
    //BottomRight
    AddToMap(max, obj, map);
}

void SetupSpatialMap(int ownerId, SpatialMap &spatialMap, vector<shared_ptr<GameObject>> &objectsToCheck) {
    vector<shared_ptr<GameObject>> gameObjects = GameObject::FindObjectsOfType<GameObject>();

    for (auto &obj: gameObjects) {
        if (obj != nullptr /* && obj->GetOwnerId() == ownerId*/) { //If owned by client
            auto boxCollider = std::static_pointer_cast<BoxCollider>(obj->GetComponent<BoxCollider>());
            if (boxCollider != nullptr) { //If boxcollider
                RegisterInSpatial(obj, *boxCollider, spatialMap);

                auto rigidBody = std::static_pointer_cast<RigidBody>(obj->GetComponent<RigidBody>());
                if (rigidBody != nullptr && rigidBody->BodyType() == BodyType::dynamicBody) {
                    objectsToCheck.push_back(obj);
                }
            }
        }
    }
}

void GetFromMap(vector<shared_ptr<GameObject>> &out, Point point, SpatialMap &map) {
    auto key = std::make_pair(floor(point.x / MAP_CELL_SIZE), floor(point.y / MAP_CELL_SIZE));
    if (map.contains(key)) {
        for (auto &obj: map[key]) {
            if (std::find_if(out.begin(), out.end(), [obj](const shared_ptr<GameObject> &outObj) {
                return obj->GetName() == outObj->GetName();
            }) == out.end()) {
                out.push_back(obj);
            }
        }
    }
}

vector<shared_ptr<GameObject>> GetNearbyObjects(GameObject &obj, BoxCollider &objCollider, SpatialMap &map) {
    vector<shared_ptr<GameObject>> result;
    Point min = obj.GetTransform().position;
    Point max{min.x + objCollider.Width(), min.y + objCollider.Height()};

    //TopLeft
    GetFromMap(result, min, map);
    //TopRight
    GetFromMap(result, {max.x, min.y}, map);
    //BottomLeft
    GetFromMap(result, {min.x, max.y}, map);
    //BottomRight
    GetFromMap(result, max, map);

    return std::move(result);
}

void PopCollisionFromList(std::vector<std::shared_ptr<Collision>> &list, int collisionId) {
    list.erase(std::remove_if(list.begin(), list.end(),
                              [collisionId](const std::shared_ptr<Collision> &collision) {
                                  return collision->GetId() == collisionId;
                              }),
               list.end());
}

void PhysicsSystem::CheckCollisions() {
    SpatialMap spatialMap;
    vector<shared_ptr<GameObject>> dynamicObjects;
    SetupSpatialMap(_clientId, spatialMap, dynamicObjects);

    for (auto &objA: dynamicObjects) {
        const shared_ptr<BoxCollider> aCol = std::static_pointer_cast<BoxCollider>(objA->GetComponent<BoxCollider>());
        if (aCol != nullptr) {
            auto aCollisions = aCol->GetCollisions(); //Copy

            for (auto &objB: GetNearbyObjects(*objA, *aCol, spatialMap)) {
                if (objA != objB) {
                    const shared_ptr<BoxCollider> bCol = std::static_pointer_cast<BoxCollider>(
                            objB->GetComponent<BoxCollider>());

                    const unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> collision = CheckBoxCollision(
                            objA->GetTransform().position, *aCol, objB->GetTransform().position, *bCol);
                    auto collisionsWithBCol = aCol->GetCollisionsWith(*bCol);
                    if (collision != nullptr) { //If collision
                        if (!aCol->GetCollisions().empty() && !collisionsWithBCol.empty()) {
                            auto collisionId = collisionsWithBCol.front().GetId();
                            // Remain Collision
                            RemainCollision(objA, aCol, objB, bCol, *collision, collisionId);
                            PopCollisionFromList(aCollisions, collisionId);
                        } else {
                            // Create collision
                            CreateCollision(objA, aCol, objB, bCol, *collision);
                        }
                    }
                }
            }

            for (auto &oldCollision: aCollisions) {
                auto bCol = oldCollision->GetCollider();
                auto objB = bCol->GetGameObject().lock();
                EndCollision(objA, aCol, objB, bCol, oldCollision->GetId());
            }
        }
    }
}

void PhysicsSystem::CreateCollision(const shared_ptr<GameObject> &initiator, const shared_ptr<Collider> &init_collider,
                                    const shared_ptr<GameObject> &receiver, const shared_ptr<Collider> &rec_collider,
                                    std::tuple<CollisionPoint, CollisionPoint> direction) {

    // Create two Collision objects with the same ID
    auto collisionInit = Collision(rec_collider, std::get<0>(direction), _collisionCnt);
    auto collisionRec = Collision(init_collider, std::get<1>(direction), _collisionCnt++);
    init_collider->AddCollision(collisionInit);
    rec_collider->AddCollision(collisionRec);

    for (auto &script: initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(collisionInit);
    for (auto &script: receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerEnter2D(collisionRec);
}

void PhysicsSystem::RemainCollision(const shared_ptr<GameObject> &initiator, const shared_ptr<Collider> &init_collider,
                                    const shared_ptr<GameObject> &receiver, const shared_ptr<Collider> &rec_collider,
                                    std::tuple<CollisionPoint, CollisionPoint> direction,
                                    const int collisionId) {

    auto init_collision = init_collider->GetCollisionById(collisionId);
    init_collision.Contact(std::get<0>(direction));
    auto rec_collision = rec_collider->GetCollisionById(collisionId);
    rec_collision.Contact(std::get<1>(direction));

    for (auto &script: initiator->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(init_collision);
    for (auto &script: receiver->GetComponents<BehaviourScript>())
        std::static_pointer_cast<BehaviourScript>(script)->OnTriggerStay2D(rec_collision);
}

void PhysicsSystem::EndCollision(const shared_ptr<GameObject> &initiator, const shared_ptr<Collider> &init_collider,
                                 const shared_ptr<GameObject> &receiver, const shared_ptr<Collider> &rec_collider,
                                 const int collisionId) {
    std::optional<Collision> init_collision = std::nullopt;
    std::optional<Collision> rec_collision = std::nullopt;
    if (init_collider != nullptr ) {
        init_collision = init_collider->GetCollisionById(collisionId);
        init_collider->RemoveCollision(collisionId);
    }
    if (rec_collider != nullptr ) {
        rec_collision = rec_collider->GetCollisionById(collisionId);
        rec_collider->RemoveCollision(collisionId);
    }

    //Call Behaviour scripts
    if (initiator != nullptr && init_collision.has_value()) {
        for (auto &script: initiator->GetComponents<BehaviourScript>())
            std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(init_collision.value());
    }
    if (receiver != nullptr && rec_collision.has_value()) {
        for (auto &script: receiver->GetComponents<BehaviourScript>())
            std::static_pointer_cast<BehaviourScript>(script)->OnTriggerExit2D(rec_collision.value());
    }
        
}

auto PhysicsSystem::CheckBoxCollision(Point aPos, const BoxCollider &aCol, Point bPos,
                                      const BoxCollider &bCol) -> std::unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> {
    bool x_overlap = (aPos.x <= bPos.x + bCol.Width()) && (aPos.x + aCol.Width() >= bPos.x);
    bool y_overlap = (aPos.y <= bPos.y + bCol.Height()) && (aPos.y + aCol.Height() >= bPos.y);

    if (x_overlap && y_overlap) {
        //This does not work if object is inside the other, only overlap
        const double a_bottom = aPos.y + aCol.Height();
        const double b_bottom = bPos.y + bCol.Height();
        const double a_right = aPos.x + aCol.Width();
        const double b_right = bPos.x + bCol.Width();

        //Distance between bottom b and top a
        const double bottom_col = b_bottom - aPos.y;
        //Distance between bottom a and top b
        const double top_col = a_bottom - bPos.y;
        //Distance between right a and left b
        const double left_col = a_right - bPos.x;
        //Distance between left a and right b
        const double right_col = b_right - aPos.x;

        if (top_col <= bottom_col && top_col <= left_col && top_col <= right_col) {//Bottom collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(
                    std::make_tuple(CollisionPoint::Bottom, CollisionPoint::Top));
        }
        if (bottom_col <= top_col && bottom_col <= left_col && bottom_col <= right_col) { //Top collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(
                    std::make_tuple(CollisionPoint::Top, CollisionPoint::Bottom));
        }
        if (left_col <= right_col && left_col <= top_col && left_col <= bottom_col) { //Right collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(
                    std::make_tuple(CollisionPoint::Right, CollisionPoint::Left));
        }
        if (right_col <= left_col && right_col <= top_col && right_col <= bottom_col) { //Left collision
            return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(
                    std::make_tuple(CollisionPoint::Left, CollisionPoint::Right));
        }

        return std::make_unique<std::tuple<CollisionPoint, CollisionPoint>>(
                std::make_tuple(CollisionPoint::Uncertain, CollisionPoint::Uncertain));
    }
    return nullptr; //No Collision
}

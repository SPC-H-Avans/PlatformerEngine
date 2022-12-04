#include "Behaviour/ForceDrivenEntityBehaviours.hpp"

#include <utility>
#include "Point.hpp"
#include "RigidBody.hpp"

using spic::Point;
using platformer_engine::ForceDrivenEntityBehaviours;

auto ForceDrivenEntityBehaviours::Seek(Point &targetPos) -> Point {
    std::shared_ptr<GameObject> gameObject{_gameObject.lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
        Point DesiredVelocity = spic::Point::PointNormalize(targetPos - transform.position)
                                * body->GetMaxSpeed();
        return (DesiredVelocity - body->GetVelocity());
    }
    // GameObject was already deleted
    gameObject.reset();
    return {};
}

auto ForceDrivenEntityBehaviours::Flee(Point &targetPos) -> Point {
    std::shared_ptr<GameObject> gameObject{_gameObject.lock()};
    if (gameObject) {
        auto transform = gameObject->GetTransform();
        auto body = std::dynamic_pointer_cast<RigidBody>(gameObject->GetComponent<RigidBody>());
        auto DesiredVelocity = spic::Point::PointNormalize(transform.position - targetPos)
                               * body->GetMaxSpeed();
        return (DesiredVelocity - body->GetVelocity());
        return (DesiredVelocity - body->GetVelocity());
    }
    // GameObject was already deleted
    gameObject.reset();
    return {};
}

Point ForceDrivenEntityBehaviours::Arrive(Point &point) {
    return spic::Point();
}

Point ForceDrivenEntityBehaviours::Calculate() {
}

Point ForceDrivenEntityBehaviours::ForwardComponent() {
    return spic::Point();
}

Point ForceDrivenEntityBehaviours::SideComponent() {
    return spic::Point();
}

void ForceDrivenEntityBehaviours::SetPath() {

}

void ForceDrivenEntityBehaviours::SetTarget(Point point) {

}

void ForceDrivenEntityBehaviours::SetTargetAgent1(std::shared_ptr<GameObject> targetAgent) {

}

void ForceDrivenEntityBehaviours::SetTargetAgent2(std::shared_ptr<GameObject> targetAgent) {

}

void ForceDrivenEntityBehaviours::SeekOn() {

}

void ForceDrivenEntityBehaviours::FleeOn() {

}

void ForceDrivenEntityBehaviours::ArriveOn() {

}

void ForceDrivenEntityBehaviours::SeekOff() {

}

void ForceDrivenEntityBehaviours::FleeOff() {

}

void ForceDrivenEntityBehaviours::ArriveOff() {

}

platformer_engine::ForceDrivenEntityBehaviours::ForceDrivenEntityBehaviours(std::weak_ptr<GameObject> gameObject) : _gameObject(std::move(gameObject)) {

}

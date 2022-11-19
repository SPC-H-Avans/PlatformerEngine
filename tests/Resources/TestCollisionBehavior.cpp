#include "TestCollisionBehavior.hpp"

void TestCollisionBehavior::OnTriggerEnter2D(const Collision collision) {
    _triggers[Trigger::Enter] = std::pair<Collider, CollisionPoint>(collision.GetCollider(), collision.Contact());
}

void TestCollisionBehavior::OnTriggerExit2D(const Collision collision) {
    _triggers[Trigger::Exit] = std::pair<Collider, CollisionPoint>(collision.GetCollider(), collision.Contact());
}

void TestCollisionBehavior::OnTriggerStay2D(const Collision collision) {
    _triggers[Trigger::Stay] = std::pair<Collider, CollisionPoint>(collision.GetCollider(), collision.Contact());
}

std::pair<Collider, CollisionPoint> TestCollisionBehavior::GetTriggerFor(Trigger trigger) {
    return _triggers[trigger];
}

uint64_t TestCollisionBehavior::GetTriggerCount() {
    return _triggers.size();
}

bool TestCollisionBehavior::HasTriggered(Trigger trigger) {
    return _triggers.count(trigger) > 0;
}

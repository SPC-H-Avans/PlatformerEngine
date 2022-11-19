#include "TestCollisionBehaviour.hpp"

void TestCollisionBehaviour::OnTriggerEnter2D(const Collision collision) {
    _triggers[Trigger::Enter] = std::pair<Collider, CollisionPoint>(collision.GetCollider(), collision.Contact());
}

void TestCollisionBehaviour::OnTriggerExit2D(const Collision collision) {
    _triggers[Trigger::Exit] = std::pair<Collider, CollisionPoint>(collision.GetCollider(), collision.Contact());
}

void TestCollisionBehaviour::OnTriggerStay2D(const Collision collision) {
    _triggers[Trigger::Stay] = std::pair<Collider, CollisionPoint>(collision.GetCollider(), collision.Contact());
}

std::pair<Collider, CollisionPoint> TestCollisionBehaviour::GetTriggerFor(Trigger trigger) {
    return _triggers[trigger];
}

uint64_t TestCollisionBehaviour::GetTriggerCount() {
    return _triggers.size();
}

bool TestCollisionBehaviour::HasTriggered(Trigger trigger) {
    return _triggers.count(trigger) > 0;
}

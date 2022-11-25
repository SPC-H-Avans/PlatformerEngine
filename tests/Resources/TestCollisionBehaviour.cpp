#include "TestCollisionBehaviour.hpp"

void TestCollisionBehaviour::OnTriggerEnter2D(const Collision collision) {
    _triggers[Trigger::Enter][collision.Contact()] += 1;
    _triggerCount++;
}

void TestCollisionBehaviour::OnTriggerExit2D(const Collision collision) {
    _triggers[Trigger::Exit][collision.Contact()] += 1;
    _triggerCount++;
}

void TestCollisionBehaviour::OnTriggerStay2D(const Collision collision) {
    _triggers[Trigger::Stay][collision.Contact()] += 1;
    _triggerCount++;
}

int TestCollisionBehaviour::GetCollisionPointCountFor(Trigger trigger, CollisionPoint point) {
    return _triggers[trigger][point];
}

int TestCollisionBehaviour::GetTriggerCount() {
    return _triggerCount;
}

void TestCollisionBehaviour::Reset() {
    _triggerCount = 0;
    _triggers = std::map<Trigger, std::map<CollisionPoint, int>>();
}

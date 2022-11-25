#include "TestCollisionBehaviour.hpp"

void TestCollisionBehaviour::OnTriggerEnter2D(const Collision collision) {
    _triggers[Trigger::Enter][collision.Contacts()] += 1;
    _triggerCount++;
}

void TestCollisionBehaviour::OnTriggerExit2D(const Collision collision) {
    _triggers[Trigger::Exit][collision.Contacts()] += 1;
    _triggerCount++;
}

void TestCollisionBehaviour::OnTriggerStay2D(const Collision collision) {
    _triggers[Trigger::Stay][collision.Contacts()] += 1;
    _triggerCount++;
}

int TestCollisionBehaviour::GetCollisionPointCountFor(Trigger trigger, std::vector<CollisionPoint> point) {
    return _triggers[trigger][point];
}

int TestCollisionBehaviour::GetTriggerCount() {
    return _triggerCount;
}

void TestCollisionBehaviour::Reset() {
    _triggerCount = 0;
    _triggers = std::map<Trigger, std::map<std::vector<CollisionPoint>, int>>();
}

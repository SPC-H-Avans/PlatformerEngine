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

void TestCollisionBehaviour::OnUpdate(double  /*speedMultiplier*/) {
    _updateTriggers++;
}

int TestCollisionBehaviour::GetUpdateTriggers() const {
    return _updateTriggers;
}

void TestCollisionBehaviour::OnStart() {
    BehaviourScript::OnStart();
}

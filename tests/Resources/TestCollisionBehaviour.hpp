#ifndef PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include <map>

enum Trigger {
    Enter,
    Exit,
    Stay
};

class TestCollisionBehaviour : public BehaviourScript {
public:
//    void OnStart() override;
//    void OnUpdate() override;
    void OnTriggerEnter2D(Collision collision) override;
    void OnTriggerExit2D(Collision collision) override;
    void OnTriggerStay2D(Collision collision) override;

    std::pair<Collider, CollisionPoint> GetTriggerFor(Trigger trigger);
    uint64_t GetTriggerCount();

    bool HasTriggered(Trigger trigger);

private:
    std::map<Trigger, std::pair<Collider, CollisionPoint>> _triggers;
};


#endif //PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOUR_HPP

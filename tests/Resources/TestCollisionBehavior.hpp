#ifndef PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOR_HPP
#define PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOR_HPP

#include "BehaviourScript.hpp"
#include <map>

enum Trigger {
    Enter,
    Exit,
    Stay
};

class TestCollisionBehavior : public BehaviourScript {
public:
//    void OnStart() override;
//    void OnUpdate() override;
    void OnTriggerEnter2D(Collision collision) override;
    void OnTriggerExit2D(Collision collision) override;
    void OnTriggerStay2D(Collision collision) override;

    std::pair<Collider, CollisionPoint> GetTriggerFor(Trigger trigger);
    uint64_t GetTriggerCount();

private:
    std::map<Trigger, std::pair<Collider, CollisionPoint>> _triggers;
};


#endif //PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOR_HPP

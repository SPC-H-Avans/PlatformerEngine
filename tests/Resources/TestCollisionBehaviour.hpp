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

    int GetCollisionPointCountFor(Trigger trigger, CollisionPoint point);
    int GetTriggerCount();
    void Reset();

private:
    std::map<Trigger, std::map<CollisionPoint, int>> _triggers;
    int _triggerCount = 0;

};


#endif //PLATFORMER_ENGINE_TESTCOLLISIONBEHAVIOUR_HPP

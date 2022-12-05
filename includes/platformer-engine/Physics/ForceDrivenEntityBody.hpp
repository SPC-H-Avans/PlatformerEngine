#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "Behaviour/ForceDrivenEntityBehaviours.hpp"

class ForceDrivenEntityBody : RigidBody {

public:
    ForceDrivenEntityBody(float friction);
    void Update(double time_elapsed);
    void Follow(const std::shared_ptr<GameObject>& gameObject);

private:
    //the steering behavior class
    std::unique_ptr<platformer_engine::ForceDrivenEntityBehaviours> _behaviours;
    std::weak_ptr<GameObject> _following;

};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

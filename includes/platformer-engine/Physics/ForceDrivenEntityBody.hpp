#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

#include "RigidBody.hpp"
#include "Behaviour/ForceDrivenEntityBehaviours.hpp"

class ForceDrivenEntityBody : RigidBody {

public:
    void Update(double time_elapsed);

private:
    //the steering behavior class
    platformer_engine::ForceDrivenEntityBehaviours* _behaviours;


};


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBODY_HPP

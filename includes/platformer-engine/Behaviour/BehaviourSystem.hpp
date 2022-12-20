#ifndef PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP
#define PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP

#include "System/ISystem.hpp"

class BehaviourSystem : public ISystem {

public:
    /**
     * @brief Call OnStart() on all active BehaviourScripts
     */
    static void Start();

    /**
     * @brief Call OnUpdate() on all BehaviourScripts
     */
    void Update(double speedMultiplier);
};

#endif //PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP

#ifndef PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP
#define PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP

class BehaviourSystem {

public:
    /**
     * @brief Call OnUpdate() on all BehaviourScripts
     */
    static void Update(double deltaTime);
};
#endif //PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP

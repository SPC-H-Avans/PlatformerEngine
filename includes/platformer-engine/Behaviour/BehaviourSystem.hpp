#ifndef PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP
#define PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP

class BehaviourSystem {

public:
    /**
     * @brief Call OnStart() on all active BehaviourScripts
     */
    static void Start();

    /**
     * @brief Call OnUpdate() on all BehaviourScripts
     */
    static void Update();
};
#endif //PLATFORMER_ENGINE_BEHAVIOURSYSTEM_HPP

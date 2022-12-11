#ifndef PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP
#define PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP


#include <memory>
#include "EntityState.hpp"

class EntityStateMachine {
public:

    /**
     * @brief Constructor for the EntityStateMachine sets the current state to the initial state
     * @param initialState the initial EntityState
     */
    EntityStateMachine(EntityState& initialState);

    /**
    * @brief Updates the EntityState in the stateMachine
    * @param state the new EntityState
    */
    void SetState(EntityState& state);

    /**
    * @brief Calls the EntityState.execute function of the currently active state
    */
    void Update();

private:
    std::unique_ptr<EntityState> _currentState;
};


#endif //PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP

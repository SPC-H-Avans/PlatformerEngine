#ifndef PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP
#define PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP


#include <memory>
#include "RigidBody.hpp"
#include "EntityState.hpp"

class EntityStateMachine {
public:

    /**
     * @brief Constructor for the EntityStateMachine sets the current state to the initial state
     * @param initialState the initial EntityState
     */
    EntityStateMachine(EntityState& initialState, std::weak_ptr<RigidBody> entityBody);

    /**
    * @brief Updates the EntityState in the stateMachine
    * @param state the new EntityState
    */
    void SetState(EntityState& state);

    /**
    * @brief Calls the EntityState.CalculateForce function of the currently active state
    * @return 2D Vector point for the force calculated by the active state
    */
    auto CalculateForce() -> Point;

private:
    std::unique_ptr<EntityState> _currentState;
    std::weak_ptr<RigidBody> _entityBody;
};


#endif //PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP

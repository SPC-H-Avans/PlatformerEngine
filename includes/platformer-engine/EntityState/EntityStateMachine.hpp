#ifndef PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP
#define PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP


#include <memory>
#include "RigidBody.hpp"
#include "EntityState.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/unique_ptr.hpp>

class EntityStateMachine {
public:
    template<class Archive>
    void serialize(Archive &ar, unsigned int version) {
        ar & _currentState;
    }

    EntityStateMachine();

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
    * @brief Gets the current state
    * @return The current state as an EntityState reference
    */
    auto GetCurrentState() -> EntityState&;

    /**
    * @brief Calls the EntityState.CalculateForce function of the currently active state
    * @return 2D Vector point for the force calculated by the active state
    */
    auto CalculateForce(std::shared_ptr<RigidBody> rigidBody) -> Point;

private:
    std::unique_ptr<EntityState> _currentState;
};


#endif //PLATFORMER_ENGINE_ENTITYSTATEMACHINE_HPP

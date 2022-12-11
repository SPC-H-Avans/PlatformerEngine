#include "EntityState/EntityStateMachine.hpp"
#include "EntityState/EntityState.hpp"

EntityStateMachine::EntityStateMachine(EntityState &initialState, RigidBody& entityBody)
        : _entityBody(std::make_shared<RigidBody>(entityBody)), _currentState(initialState.Clone()) {
}

void EntityStateMachine::SetState(EntityState &state) {
    _currentState = std::move(state.Clone());
}

auto EntityStateMachine::CalculateForce() -> Point
{
    return _currentState->CalculateForce(_entityBody);
}


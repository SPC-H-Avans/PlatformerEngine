#include "EntityState/EntityStateMachine.hpp"
#include "EntityState/EntityState.hpp"

EntityStateMachine::EntityStateMachine(EntityState &initialState, RigidBody& entityBody) : _entityBody(std::make_shared<RigidBody>(entityBody)) {
    SetState(initialState);
}

void EntityStateMachine::SetState(EntityState &state) {
    auto newState = std::unique_ptr<EntityState>(&state, std::default_delete<EntityState>());
    newState.swap(_currentState);
}

auto EntityStateMachine::CalculateForce() -> Point
{
    return _currentState->CalculateForce(_entityBody);
}


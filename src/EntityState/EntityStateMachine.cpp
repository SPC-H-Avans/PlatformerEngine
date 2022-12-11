#include "EntityState/EntityStateMachine.hpp"

EntityStateMachine::EntityStateMachine(EntityState &initialState) {
    SetState(initialState);
}

void EntityStateMachine::SetState(EntityState &state) {
    auto newState = std::unique_ptr<EntityState>(&state, std::default_delete<EntityState>());
    newState.swap(_currentState);
}

void EntityStateMachine::Update()
{
    _currentState->execute(*this);
}

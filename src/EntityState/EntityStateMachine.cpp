#include "EntityState/EntityStateMachine.hpp"
#include "EntityState/EntityState.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"

EntityStateMachine::EntityStateMachine(EntityState &initialState)
        : _currentState(initialState.Clone()) {
}

void EntityStateMachine::SetState(EntityState &state) {
    _currentState = std::move(state.Clone());
}

auto EntityStateMachine::CalculateForce(std::shared_ptr<RigidBody> rigidBody) -> Point
{
    return _currentState->CalculateForce(rigidBody);
}

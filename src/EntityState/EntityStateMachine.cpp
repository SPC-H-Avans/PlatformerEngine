#include "EntityState/EntityStateMachine.hpp"
#include "EntityState/EntityState.hpp"

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

EntityStateMachine::EntityStateMachine() {


}

auto EntityStateMachine::GetCurrentState() -> EntityState & {
    return *_currentState;
}

BOOST_CLASS_EXPORT(EntityStateMachine);
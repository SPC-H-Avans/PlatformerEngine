#include "EntityState/EntityWanderState.hpp"
#include <memory>

auto EntityWanderState::CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point {
    return {0,0};
}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

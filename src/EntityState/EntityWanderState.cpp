#include "EntityState/EntityWanderState.hpp"
#include <memory>

auto EntityWanderState::CalculateForce(std::weak_ptr<RigidBody> &entityBody) -> spic::Point {
    return {0,0};
}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

EntityWanderState::EntityWanderState() = default;

EntityWanderState::~EntityWanderState() = default;

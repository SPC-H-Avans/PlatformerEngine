#include "EntityState/EntityWanderState.hpp"

auto EntityWanderState::CalculateForce(std::weak_ptr<RigidBody> &entityBody) -> spic::Point {
    return {0,0};
}

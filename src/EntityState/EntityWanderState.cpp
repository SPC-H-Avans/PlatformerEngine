#include "EntityState/EntityWanderState.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"
#include <memory>

auto EntityWanderState::CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point {
    auto entityBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(rigidBody);
    if(!entityBody) {
        return {0,0};
    }


}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

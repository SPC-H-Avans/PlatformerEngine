#include "EntityState/EntityWanderState.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"
#include <memory>

auto EntityWanderState::CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point {
    auto entityBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(rigidBody);
    if(!entityBody) {
        return {0,0};
    }
    Point heading = entityBody->GetHeading();
    Point velocity = entityBody->GetVelocity();
    Point totalForce {0,0};

    // Add wander force
    totalForce += heading * velocity;

    if(!entityBody->CanMoveTo(CollisionPoint::Right)) {
        totalForce.x *= -1;
    }

    if(entityBody->GetHeading().Equals({0,0})) {
        // Make sure the enemy is always heading somewhere
        totalForce += {1,-1};
    }

    entityBody->AddForce(totalForce);
}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

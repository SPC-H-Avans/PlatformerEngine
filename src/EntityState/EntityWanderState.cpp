#include "EntityState/EntityWanderState.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"
#include <memory>
#include <random>

auto EntityWanderState::CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point {
    auto entityBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(rigidBody);
    if(!entityBody) {
        return {0,0};
    }
    Point heading = entityBody->GetHeading();
    Point totalForce {0,0};

    // Make sure the enemy is always heading somewhere
    if(abs(entityBody->GetHeading().x) < 0.01  || abs(entityBody->GetHeading().y) < 0.01) {
        totalForce += {1,-1};
    }

    totalForce += heading * Point{1.5, 1.5};

    if(!entityBody->CanMoveTo(CollisionPoint::Right) || !entityBody->CanMoveTo(CollisionPoint::Left)) {
        totalForce.x *= -10;
    }
    if(!entityBody->CanMoveTo(CollisionPoint::Right) && !entityBody->CanMoveTo(CollisionPoint::Left)) {
        totalForce.y *= 100;
    }

    return totalForce;
}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

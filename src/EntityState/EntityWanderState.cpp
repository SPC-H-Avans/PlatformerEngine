#include "EntityState/EntityWanderState.hpp"
#include <memory>

auto EntityWanderState::CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point {
    if(!rigidBody) {
        return {0,0};
    }

    Point heading = rigidBody->GetHeading();
    Point totalForce {0,0};

    // Make sure the enemy is always heading somewhere
    if(abs(rigidBody->GetHeading().x) < 0.01  || abs(rigidBody->GetHeading().y) < 0.01) {
        totalForce += {1,-1};
    }

    totalForce += heading * Point{1.5, 1.5};

    if(!rigidBody->CanMoveTo(CollisionPoint::Right) || !rigidBody->CanMoveTo(CollisionPoint::Left)) {
        totalForce.x *= -10;
    }
    if(!rigidBody->CanMoveTo(CollisionPoint::Right) && !rigidBody->CanMoveTo(CollisionPoint::Left)) {
        totalForce.y *= 100;
    }

    return totalForce;
}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

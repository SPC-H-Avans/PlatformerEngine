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
    Point velocity = entityBody->GetVelocity();
    Point totalForce {0,0};

    // Make sure the enemy is always heading somewhere
    if(abs(entityBody->GetHeading().x) < 0.01  || abs(entityBody->GetHeading().y) < 0.01) {
        totalForce += {1,-1};
    }

    // Add a random wander force between 0 and 100, with the y being inverted for jumping
    std::random_device random;  // Seed for the random number generator
    std::mt19937 generator(random()); // Mersenne Twister 19937 generator
    std::uniform_int_distribution<> distribution(0, 100); // Uniform distribution from 0 to 100
    auto xForce = static_cast<double>(distribution(generator));
    auto yForce = -1 * static_cast<double>(distribution(generator));
    totalForce += heading * Point{xForce, yForce};

    if(!entityBody->CanMoveTo(CollisionPoint::Right) || !entityBody->CanMoveTo(CollisionPoint::Left)) {
        totalForce.x *= -1;
    }

    return totalForce;
}

auto EntityWanderState::Clone() const -> std::unique_ptr<EntityState> {
    return std::make_unique<EntityWanderState>(*this);
}

#ifndef PLATFORMER_ENGINE_FLYINGENEMYTEMPLATE_HPP
#define PLATFORMER_ENGINE_FLYINGENEMYTEMPLATE_HPP

#include "PhysicsTemplate.hpp"

class FlyingEnemyTemplate : public PhysicsTemplate {
public:
    FlyingEnemyTemplate() = default;

    [[nodiscard]] auto GetMass() const -> float override { return _mass; };
    [[nodiscard]] auto GetGravityScale() const -> float override { return _gravityScale; };
    [[nodiscard]] auto GetMaxSpeed() const -> spic::Point override { return _maxSpeed; };
    [[nodiscard]] auto GetFriction() const -> float override { return _friction; };

private:
    const float _mass = 15;
    const float _gravityScale = 0.005;
    const spic::Point _maxSpeed = spic::Point{1.5, 4};
    const float _friction = 0.045;
};

#endif //PLATFORMER_ENGINE_FLYINGENEMYTEMPLATE_HPP

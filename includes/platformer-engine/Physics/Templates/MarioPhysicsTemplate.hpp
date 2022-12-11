#ifndef PLATFORMER_ENGINE_MARIOPHYSICSTEMPLATE_HPP
#define PLATFORMER_ENGINE_MARIOPHYSICSTEMPLATE_HPP

#include "PhysicsTemplate.hpp"

class MarioPhysicsTemplate : public PhysicsTemplate {
public:
    MarioPhysicsTemplate() = default;

    [[nodiscard]] auto GetMass() const -> float override { return _mass; };
    [[nodiscard]] auto GetGravityScale() const -> float override { return _gravityScale; };
    [[nodiscard]] auto GetMaxSpeed() const -> spic::Point override { return _maxSpeed; };
    [[nodiscard]] auto GetFriction() const -> float override { return _friction; };

private:
    const float _mass = 8;
    const float _gravityScale = 0.055;
    const spic::Point _maxSpeed = spic::Point{2.0, 20.0};
    const float _friction = 0.060;
};

#endif //PLATFORMER_ENGINE_MARIOPHYSICSTEMPLATE_HPP

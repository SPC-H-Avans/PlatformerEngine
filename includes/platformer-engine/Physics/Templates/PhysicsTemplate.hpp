#ifndef PLATFORMER_ENGINE_PHYSICSTEMPLATE_HPP
#define PLATFORMER_ENGINE_PHYSICSTEMPLATE_HPP

#include "Point.hpp"

class PhysicsTemplate {
public:
    PhysicsTemplate(float mass, float gravityScale, spic::Point maxSpeed, float friction)
    : _mass(mass), _gravityScale(gravityScale), _maxSpeed(maxSpeed), _friction(friction) {}

    PhysicsTemplate() = default;

    [[nodiscard]] virtual auto GetMass() const -> float { return _mass; };
    [[nodiscard]] virtual auto GetGravityScale() const -> float { return _gravityScale; };
    [[nodiscard]] virtual auto GetMaxSpeed() const -> spic::Point { return _maxSpeed; };
    [[nodiscard]] virtual auto GetFriction() const -> float { return _friction; };

private:
    const float _mass = 15;
    const float _gravityScale = 0.005;
    const spic::Point _maxSpeed = spic::Point{2, 4};
    const float _friction = 0;

};


#endif //PLATFORMER_ENGINE_PHYSICSTEMPLATE_HPP

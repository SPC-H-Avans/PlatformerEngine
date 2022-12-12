#ifndef PLATFORMER_ENGINE_PHYSICSTEMPLATE_HPP
#define PLATFORMER_ENGINE_PHYSICSTEMPLATE_HPP

#include "Point.hpp"

class PhysicsTemplate {
public:

    /**
     * @brief Constructor that takes all values for the physics template
     * @param mass the mass for the object in Newton
     * @param gravityScale The gravityscale in m/s/s
     * @param maxSpeed A 2D Vector of the maximum speed in m/s
     * @param friction The amount of friction this object has
     */
    PhysicsTemplate(float mass, float gravityScale, spic::Point maxSpeed, float friction)
    : _mass(mass), _gravityScale(gravityScale), _maxSpeed(maxSpeed), _friction(friction) {}

    /**
     * @brief Default constructor, all values in the physics template are 0
     */
    PhysicsTemplate() = default;
    virtual ~PhysicsTemplate() = default;

    PhysicsTemplate(const PhysicsTemplate&) = default;
    auto operator=(const PhysicsTemplate&) -> PhysicsTemplate& = delete;

    PhysicsTemplate(PhysicsTemplate&&) = default;
    auto operator=(PhysicsTemplate&&) -> PhysicsTemplate& = delete;

    /**
     * @brief Getter for the Mass constant
     * @return The mass constant as a float
     */
    [[nodiscard]] virtual auto GetMass() const -> float { return _mass; };

    /**
     * @brief Getter for the GravityScale constant
     * @return The GravityScale constant as a float
     */
    [[nodiscard]] virtual auto GetGravityScale() const -> float { return _gravityScale; };

    /**
     * @brief Getter for the MaxSpeed constant
     * @return The MaxSpeed constant as a 2D vector Point
     */
    [[nodiscard]] virtual auto GetMaxSpeed() const -> spic::Point { return _maxSpeed; };

    /**
     * @brief Getter for the Friction constant
     * @return The Friction constant as a float
     */
    [[nodiscard]] virtual auto GetFriction() const -> float { return _friction; };

private:
    const float _mass = 0;
    const float _gravityScale = 0;
    const spic::Point _maxSpeed = spic::Point{0, 0};
    const float _friction = 0;

};


#endif //PLATFORMER_ENGINE_PHYSICSTEMPLATE_HPP

#ifndef PLATFORMER_ENGINE_ENTITYSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYSTATE_HPP

#include "Point.hpp"
#include <memory>
#include "RigidBody.hpp"

// Forward declaration of the state machine class
class EntityStateMachine;

// Abstract base class for states
class EntityState
{
public:
    EntityState() = default;
    virtual ~EntityState() = default;

    EntityState(const EntityState&) = default;
    auto operator=(const EntityState&) -> EntityState& = default;

    EntityState(EntityState&&) = default;
    auto operator=(EntityState&&) -> EntityState& = default;

    virtual auto CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point = 0;
    [[nodiscard]] virtual auto Clone() const -> std::unique_ptr<EntityState> = 0;
};


#endif //PLATFORMER_ENGINE_ENTITYSTATE_HPP

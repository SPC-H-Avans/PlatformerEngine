#ifndef PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

#include "EntityState.hpp"
#include "RigidBody.hpp"

class EntityWanderState : public EntityState {
public:
    EntityWanderState();
    auto CalculateForce(std::weak_ptr<RigidBody> &entityBody) -> spic::Point override;
    [[nodiscard]] auto Clone() const -> std::unique_ptr<EntityState> override;
    ~EntityWanderState() override;

    EntityWanderState(const EntityWanderState&) = default;
    auto operator=(const EntityWanderState&) -> EntityWanderState& = default;

    EntityWanderState(EntityWanderState&&) = default;
    auto operator=(EntityWanderState&&) -> EntityWanderState& = default;
};


#endif //PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

#ifndef PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

#include <memory>
#include "EntityState.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"
#include "Point.hpp"

class EntityPursuitState : public EntityState {
public:
    EntityPursuitState();
    auto CalculateForce(std::weak_ptr<RigidBody> &entityBody) -> spic::Point override;
    [[nodiscard]] auto Clone() const -> std::unique_ptr<EntityState> override;
    ~EntityPursuitState() override;

    EntityPursuitState(const EntityPursuitState&) = default;
    auto operator=(const EntityPursuitState&) -> EntityPursuitState& = default;

    EntityPursuitState(EntityPursuitState&&) = default;
    auto operator=(EntityPursuitState&&) -> EntityPursuitState& = default;
private:
    auto Seek(RigidBody &entityBody, Point targetPos) -> Point;
};

#endif //PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

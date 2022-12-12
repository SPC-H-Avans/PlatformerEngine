#ifndef PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

#include <memory>
#include "EntityState.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"

class EntityPursuitState : public EntityState {
public:
    auto CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point override;
    [[nodiscard]] auto Clone() const -> std::unique_ptr<EntityState> override;
private:
    auto Seek(const std::shared_ptr<GameObject> &gameObject, Point targetPos) -> Point;
};

#endif //PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

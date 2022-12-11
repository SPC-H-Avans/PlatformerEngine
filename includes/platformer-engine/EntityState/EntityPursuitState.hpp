#ifndef PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

#include <memory>
#include "EntityState.hpp"
#include "Point.hpp"
#include "RigidBody.hpp"
#include "Point.hpp"

class EntityPursuitState : public EntityState {
public:
    spic::Point CalculateForce(std::weak_ptr<RigidBody> &entityBody) override;

private:
    Point Seek(RigidBody &entityBody, Point targetPos);
};

#endif //PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

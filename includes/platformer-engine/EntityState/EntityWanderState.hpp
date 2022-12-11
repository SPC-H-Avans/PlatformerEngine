#ifndef PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

#include "EntityState.hpp"
#include "RigidBody.hpp"

class EntityWanderState : public EntityState {
    auto CalculateForce(std::weak_ptr<RigidBody> &entityBody) -> spic::Point override;
};


#endif //PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

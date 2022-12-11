#ifndef PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

#include "EntityState.hpp"

class EntityWanderState : EntityState {
    void execute(EntityStateMachine& stateMachine) override;
};


#endif //PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

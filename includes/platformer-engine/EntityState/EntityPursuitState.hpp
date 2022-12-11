#ifndef PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

#include "EntityState.hpp"

class EntityPursuitState : EntityState {
    void execute(EntityStateMachine& stateMachine) override;
};

#endif //PLATFORMER_ENGINE_ENTITYPURSUITSTATE_HPP

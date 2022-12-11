#ifndef PLATFORMER_ENGINE_ENTITYSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYSTATE_HPP

// Forward declaration of the state machine class
class EntityStateMachine;

// Abstract base class for states
class EntityState
{
public:
    virtual void execute(EntityStateMachine& stateMachine) = 0;
};


#endif //PLATFORMER_ENGINE_ENTITYSTATE_HPP

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
    virtual spic::Point CalculateForce(std::weak_ptr<RigidBody> &entityBody) = 0;

    virtual ~EntityState() = default;
};


#endif //PLATFORMER_ENGINE_ENTITYSTATE_HPP

#ifndef PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H
#define PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H

#include <stdexcept>
#include <string>
#include "RigidBody.hpp"

namespace spic {
    class IllegalCollisionBehaviourException : public std::logic_error
    {
    public:
        IllegalCollisionBehaviourException (const BodyType& bodyType, const CollisionPoint& collisionPoint)
                : std::logic_error{"A RigidBody tried to allow a non-restricted move (BodyType: "
                                   + std::to_string(static_cast<int>(bodyType))
                                   + ", CollisionPoint: "
                                   + std::to_string(static_cast<int>(collisionPoint))+ ")."
                                   + "\n Allowing this would set the moveRestriction to -1. Don't do that."} {}
    };
}
#endif //PLATFORMER_ENGINE_CAMERANOTINSCENEEXCEPTION_H

#ifndef PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP
#define PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP
#include "RigidBody.hpp"


class PlayerRigidBody : public spic::RigidBody {
public:

    PlayerRigidBody();

    /**
     * @brief returns the horizontal speed
     */
    float GetXVelocity() { return _velocity.x; }

    /**
     * @brief returns the vertical speed
     */
    float GetYVelocity() { return _velocity.y; }

};


#endif //PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP

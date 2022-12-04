#ifndef PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP
#define PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP

#include "RigidBody.hpp"


class PlayerRigidBody : public spic::RigidBody {
public:
    template<typename archive>
    void serialize(archive &ar, const unsigned /*version*/) {
        ar & boost::serialization::base_object<RigidBody, PlayerRigidBody>(*this);
        boost::serialization::void_cast_register<PlayerRigidBody, RigidBody>();
        ar & _horizontalSpeed;
        ar & _verticalSpeed;
        ar & _jumpTimer;
    }

    PlayerRigidBody();

    void AddForce(const Point &forceDirection) override;

    /**
     * @brief returns the horizontal speed
     */
    float GetXVelocity() { return _horizontalSpeed; }

    /**
     * @brief returns the vertical speed
     */
    float GetYVelocity() { return _verticalSpeed; }

private:
    float _horizontalSpeed{0};
    float _verticalSpeed{0};
    int _jumpTimer{0};
    const float PLAYER_MAX_VERTICAL_SPEED = 8;
    const float PLAYER_JUMP_SPEED = -4;
    const float PLAYER_ACCELERATION = 0.25f;
    const float PLAYER_WALK_SPEED = 2;
    const int PLAYER_JUMP_TIMER = 8;
};


#endif //PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP

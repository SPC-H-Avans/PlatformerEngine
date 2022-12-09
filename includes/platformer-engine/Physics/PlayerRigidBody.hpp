#ifndef PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP
#define PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP

#include "RigidBody.hpp"


class PlayerRigidBody : public spic::RigidBody {
public:
    template<typename archive>
    void serialize(archive &ar, const unsigned /*version*/) {
        ar & boost::serialization::base_object<RigidBody, PlayerRigidBody>(*this);
        boost::serialization::void_cast_register<PlayerRigidBody, RigidBody>();
    }

    PlayerRigidBody();
};


#endif //PLATFORMER_ENGINE_PLAYERRIGIDBODY_HPP

#ifndef PLATFORMER_ENGINE_MOVESYSTEM_HPP
#define PLATFORMER_ENGINE_MOVESYSTEM_HPP

#include "RigidBody.hpp"

class MoveSystem {
public:

    MoveSystem(int localClientId = 0);

    /**
    * @brief Move every active dynamic RigidBody according to their physics
    */
    void Update();

private:
    int _clientId = 0;
    static auto CalculateGravityForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
    static auto CalculateFrictionForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
    static auto CalculateFDEForce(const std::shared_ptr<GameObject>& gameObject) -> Point;
    static auto GetLimitedVelocityForCollisions(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
};


#endif //PLATFORMER_ENGINE_MOVESYSTEM_HPP

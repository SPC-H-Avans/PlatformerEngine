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
    auto CalculateGravityForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
    auto CalculateFrictionForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
    auto CalculateFDEForce(const std::shared_ptr<RigidBody>& rigidBody, Point position) -> Point;
    auto GetLimitedVelocityForCollisions(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
};


#endif //PLATFORMER_ENGINE_MOVESYSTEM_HPP

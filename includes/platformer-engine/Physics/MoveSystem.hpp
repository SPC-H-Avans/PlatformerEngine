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

    /**
    * @brief Calculate the gravity force for a RigidBody
     * @param rigidBody A shared pointer to the rigidbody
     * @return A 2D Vector Point for the gravity force
    */
    static auto CalculateGravityForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point;

    /**
    * @brief Calculate the friction force for a RigidBody
     * @param rigidBody A shared pointer to the rigidbody
     * @return A 2D Vector Point for the friction force
    */
    static auto CalculateFrictionForce(const std::shared_ptr<RigidBody>& rigidBody) -> Point;

    /**
    * @brief Calculate the gravity force for the ForceDrivenEntity Component, if the gameObject has one.
     * If the GameObject doesn't have a ForceDrivenEntityComponent, it returns Point{0,0}
     * @param gameObject A shared pointer to the gameObject
     * @return A 2D Vector Point for the ForceDrivenEntity force
    */
    static auto CalculateFDEForce(const std::shared_ptr<GameObject>& gameObject) -> Point;

    /**
    * @brief Limits the x and y velocity of a rigidBody to prevent it from falling through blocks.
     * @param rigidBody A shared pointer to the rigidbody
     * @return A 2D Vector Point representing the new limited velocity
    */
    static auto GetLimitedVelocityForCollisions(const std::shared_ptr<RigidBody>& rigidBody) -> Point;
};


#endif //PLATFORMER_ENGINE_MOVESYSTEM_HPP

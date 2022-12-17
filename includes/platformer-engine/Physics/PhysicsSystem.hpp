
#ifndef PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP
#define PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP

#include <memory>
#include <map>
#include <vector>
#include "Point.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include "Physics/Collision.hpp"

/**
 * @brief System that controls forces and collision on GameObjects. Currently collision only
 * supports BoxCollider and doesn't work if object is inside another object (works for overlap)
 */
class PhysicsSystem {
public:
    PhysicsSystem(int localClientId = 0);

    /**
     * @brief Updates the PhysicsSystem
     */
    void Update();

    /**
     * @brief Check the collisions for every active dynamic RigidBody.
     */
    void CheckCollisions();

private:
    /**
     * @brief Collision was not in motion yet. Collision is now added to the active collisions list and the OnTriggerEnter2D handlers have been invoked.
     */
    void CreateCollision(const std::shared_ptr<GameObject>& initiator, const std::shared_ptr<Collider>& init_collider,
                         const std::shared_ptr<GameObject>& receiver, const std::shared_ptr<Collider>& rec_collider
            ,std::tuple<CollisionPoint, CollisionPoint> direction);

    /**
     * @brief Collision is no longer in motion. Collision is now removed from the active collisions list and the OnTriggerExit2D handlers have been invoked.
     */
    void EndCollision(const std::shared_ptr<GameObject>& initiator, const std::shared_ptr<Collider>& init_collider,
                      const std::shared_ptr<GameObject>& receiver, const std::shared_ptr<Collider>& rec_collider,
                      int collisionId);

    /**
     * @brief Collision was already in motion yet. Collision the OnTriggerStay2D handlers have been invoked.
     */
    static void RemainCollision(const std::shared_ptr<GameObject>& initiator, const std::shared_ptr<Collider>& init_collider, const std::shared_ptr<GameObject>& receiver, const std::shared_ptr<Collider>& rec_collider,
                                std::tuple<CollisionPoint, CollisionPoint> direction, int collisionId);

    /**
     * @brief Checks for given objects if collision is active, also checks the side on which the collision occurs.
     * @param aPos current X,Y position of object A
     * @param aCol Collider of object A
     * @param bPos current X,Y position of object b
     * @param bCol Collider of object B
     * @return Tuple of CollisionPoints, first value is the side on which a has been hit, second value is the side on which b has been hit
     */
    static auto CheckBoxCollision(Point aPos, const BoxCollider& aCol, Point bPos, const BoxCollider& bCol) -> std::unique_ptr<std::tuple<CollisionPoint, CollisionPoint>>;

    int _collisionCnt = 0;
    int _clientId = 0;
};

#endif //PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP


#ifndef PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP
#define PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP

#include <memory>
#include <map>
#include <vector>
#include "Point.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include "Collision.hpp"

using namespace spic;

class PhysicsSystem {
public:
    void Update();

    bool CheckCollisions();
private:
    /**
     * @brief Collision was not in motion yet. Collision is now added to the active collisions list and the OnTriggerEnter2D handlers have been invoked;
     */
    void CreateCollision(std::shared_ptr<GameObject> initiator, std::shared_ptr<Collider> init_collider,
                         std::shared_ptr<GameObject> receiver, std::shared_ptr<Collider> rec_collider
                        ,std::tuple<CollisionPoint, CollisionPoint> direction);

    /**
     * @brief Collision is no longer in motion. Collision is now removed from the active collisions list and the OnTriggerExit2D handlers have been invoked;
     */
    void EndCollision(std::shared_ptr<GameObject> initiator, std::shared_ptr<Collider> init_collider, std::shared_ptr<GameObject> receiver, std::shared_ptr<Collider> rec_collider);

    /**
     * @brief Collision was already in motion yet. Collision the OnTriggerStay2D handlers have been invoked;
     */
    void RemainCollision(const std::shared_ptr<GameObject>& initiator, const std::shared_ptr<Collider>& init_collider, const std::shared_ptr<GameObject>& receiver, const std::shared_ptr<Collider>& rec_collider);

    std::unique_ptr<std::tuple<CollisionPoint, CollisionPoint>> CheckBoxCollision(Point& aPos, const BoxCollider& aCol, Point& bPos, const BoxCollider& bCol);
    std::map<std::shared_ptr<Collider>, std::vector<std::shared_ptr<Collider>>> _collisions;
};

#endif //PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP

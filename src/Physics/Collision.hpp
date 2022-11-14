
#ifndef PLATFORMER_ENGINE_COLLISION_HPP
#define PLATFORMER_ENGINE_COLLISION_HPP

#include <memory>
#include "Collider.hpp"
#include "Point.hpp"

 enum CollisionPoint {
    Left,
    Right,
    Top,
    Bottom,
    Uncertain
};

using namespace spic;

/**
 * @brief Collider wrapper passed to BehaviourScript triggers, adds additional information about a collision event.
 */
class Collision {
public:
    /**
     * @brief constructor for creating a collision
     * @param other collider that is colliding with this object's collider.
     * @param direction axis on which our collider has been hit.
     */
    Collision(Collider& other, CollisionPoint direction);

    /**
     * @brief constructor for creating a collision
     * @param other collider that is colliding with this object's collider.
     */
    explicit Collision(Collider& other);

    /**
     * @brief Setter for adding a collider to the collision object
     * @param other Collider that we are colliding with.
     */
    void Collider(const Collider& other);

    /**
     * @brief Getter for collider of the collision object
     * @return Collider that we are colliding with.
     */
    [[nodiscard]] auto Collider() const -> spic::Collider&;

    /**
     * @brief Setter for direction on the collision object
     * @param other direction from wich we have been hit
     */
    void Contact(CollisionPoint point);

    /**
     * @brief Getter for direction of the collision object
     * @return Direction from which we have been hit
     */
    [[nodiscard]] auto Contact() const -> CollisionPoint&;
private:
    spic::Collider& _other;
    std::unique_ptr<CollisionPoint> _contact;
};


#endif //PLATFORMER_ENGINE_COLLISION_HPP


#ifndef PLATFORMER_ENGINE_COLLISION_HPP
#define PLATFORMER_ENGINE_COLLISION_HPP

#include <memory>
#include "Point.hpp"
#include "Collider.hpp"


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
         * @param uid Unique identifier of the Collision
         */
        Collision(std::shared_ptr<Collider> other, std::vector<CollisionPoint> direction, int uid);

        /**
         * @brief constructor for creating a collision
         * @param other collider that is colliding with this object's collider.
         * @param uid Unique identifer for the Collision
         */
        explicit Collision(std::shared_ptr<Collider> other, int uid);

        /**
         * @brief Setter for adding a collider to the collision object
         * @param other Collider that we are colliding with.
         */
        void SetCollider(const std::shared_ptr<Collider>& other);

        /**
         * @brief Getter for collider of the collision object
         * @return Collider that we are colliding with.
         */
        [[nodiscard]] auto GetCollider() const -> std::shared_ptr<Collider>;

        /**
         * @brief Setter for direction on the collision object
         * @param other direction from wich we have been hit
         */
        void Contacts(const std::vector<CollisionPoint> &point);

        /**
         * @brief Getter for direction of the collision object
         * @return Direction from which we have been hit
         */
        [[nodiscard]] auto Contacts() const -> std::vector<CollisionPoint>;

        /**
         * @brief Getter for unique id
         * @return Unique id
         */
        [[nodiscard]] auto GetId() const -> int;

    private:
        std::shared_ptr<Collider> _other;
        std::vector<CollisionPoint> _contacts;
        int _id;

    };


#endif //PLATFORMER_ENGINE_COLLISION_HPP

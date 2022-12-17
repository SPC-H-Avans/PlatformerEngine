
#ifndef PLATFORMER_ENGINE_COLLISION_HPP
#define PLATFORMER_ENGINE_COLLISION_HPP

#include <memory>
#include "Point.hpp"
#include "Collider.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>


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
    template<class Archive>
    void serialize(Archive &ar, unsigned int version) {
        ar & _id;
    }
        /**
         * @brief constructor for creating a collision
         * @param self collider is the object's collider in the collision.
         * @param other collider that is colliding with this object's collider.
         * @param direction axis on which our collider has been hit.
         * @param uid Unique identifier of the Collision
         */
        Collision(std::shared_ptr<Collider> self, std::shared_ptr<Collider> other, CollisionPoint direction, int uid);

        /**
         * @brief constructor for creating a collision
         * @param self collider is the object's collider in the collision.
         * @param other collider that is colliding with this object's collider.
         * @param uid Unique identifer for the Collision
         */
        explicit Collision(std::shared_ptr<Collider> self, std::shared_ptr<Collider> other, int uid);

        /**
         * @brief Setter for adding the other collider to the collision object
         * @param other Collider that we are colliding with.
         */
        void SetOtherCollider(const std::shared_ptr<Collider>& other);


        /**
         * @brief Setter for adding the self collider to the collision object
         * @param other Collider that we are colliding with.
         */
        void SetSelfCollider(const std::shared_ptr<Collider>& self);

        /**
         * @brief Getter for collider of the other collision object
         * @return Collider that we are colliding with.
         */
        [[nodiscard]] auto GetOtherCollider() -> std::shared_ptr<Collider>;


        /**
         * @brief Getter for collider of the self collision object
         * @return Collider that we are colliding with.
         */
        [[nodiscard]] auto GetSelfCollider() const -> std::shared_ptr<Collider>;

    /**
     * @brief Setter for direction on the collision object
     * @param other direction from wich we have been hit
     */
    void Contact(CollisionPoint point);

    /**
     * @brief Getter for direction of the collision object
     * @return Direction from which we have been hit
     */
    [[nodiscard]] auto Contact() const -> CollisionPoint;

    /**
     * @brief Getter for unique id
     * @return Unique id
     */
    [[nodiscard]] auto GetId() const -> int;

private:
    std::shared_ptr<Collider> _other;
    std::shared_ptr<Collider> _self;
    CollisionPoint _contact;
    int _id;
};


#endif //PLATFORMER_ENGINE_COLLISION_HPP

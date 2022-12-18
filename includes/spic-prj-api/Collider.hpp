#ifndef COLLIDER2D_H_
#define COLLIDER2D_H_

#include "Component.hpp"
#include "Point.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "Networking/boost/portable_binary_iarchive.hpp"
#include "Networking/boost/portable_binary_oarchive.hpp"
#include <vector>

// Forward declaration of Collision
class Collision;

namespace spic {

    enum ColliderType {
        Body,
        LookAhead
    };

    /**
     * @brief The base class for all colliders.
     * @spicapi
     */
    class Collider : public Component {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<Component, Collider>(*this);
            boost::serialization::void_cast_register<Collider, Component>();
        }

        [[nodiscard]] auto GetCollisions() const -> const std::vector<std::shared_ptr<Collision>> &;

        auto GetCollisionsWith(const Collider &col) -> std::vector<Collision>;

        auto GetCollisionById(int uid) -> Collision &;

        void AddCollision(const Collision &col);

        void RemoveCollision(int uid);

        void SetPosition(Point position);
        [[nodiscard]] auto GetPosition() const -> Point;


        [[nodiscard]] auto GetColliderType() const -> ColliderType;
        void SetColliderType(ColliderType colliderType);

        [[nodiscard]] auto GetObstructsMovement() const -> bool { return _obstructsMovement; }

        void SetObstructsMovement(bool obstructsMovement) { _obstructsMovement = obstructsMovement; }

    private:
        std::vector<std::shared_ptr<Collision>> _collisions;
        Point _position;
        ColliderType _colliderType;
        bool _obstructsMovement = true;

    };

}  // namespace spic

BOOST_SERIALIZATION_ASSUME_ABSTRACT(spic::Collider);

#endif // COLLIDER2D_H_
